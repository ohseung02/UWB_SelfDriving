#include <DW1000Jang.hpp>

#define joy_center 512
int joystick = 8;
int sw = 3;

#if defined(ESP8266)
const uint8_t PIN_SS = 15;  // SPI select pin on ESP8266
#else
const uint8_t PIN_SS = 10;  // SPI select pin on AVR
#endif

// DEBUG packet sent status and count
volatile unsigned long delaySent = 0;
int16_t sentNum = 1; // todo check int type
byte DATA = 0x01;
byte SHORT_SRC_AND_DEST = 0x88;
byte SEQ_NUMBER = 1;

byte receiver_address[] = { 0x06, 0x00 };

device_configuration_t DEFAULT_CONFIG = {
    false,
    true,
    true,
    true,
    false,
    SFDMode::STANDARD_SFD,
    Channel::CHANNEL_7,
    DataRate::RATE_850KBPS,
    PulseFrequency::FREQ_16MHZ,
    PreambleLength::LEN_128,
    PreambleCode::CODE_3
};

int x_axis = A1;
int y_axis = A2;
int op_state =0;
int value_x = 0;
int value_y = 0;
int duty =0;
int dx=0; 
int dy=0;
int sw_state = 0;

void setup() {
  // Pin modes
  pinMode(x_axis, INPUT);
  pinMode(y_axis, INPUT);

  pinMode(joystick, INPUT_PULLUP);
  pinMode(sw, INPUT_PULLUP);
  
  Serial.begin(115200);
  Serial.println(F("### DW1000Jang-arduino-sender-test ###"));

  // Initialize DW1000 module
  DW1000Jang::initializeNoInterrupt(PIN_SS);
  DW1000Jang::applyConfiguration(DEFAULT_CONFIG);

  DW1000Jang::setDeviceAddress(5);
  DW1000Jang::setNetworkId(10);
  DW1000Jang::setAntennaDelay(16436);
  Serial.println(F("Committed configuration ..."));

  // Print device info
  char msg[128];
  DW1000Jang::getPrintableDeviceIdentifier(msg);
  Serial.print("Device ID: "); Serial.println(msg);
  DW1000Jang::getPrintableExtendedUniqueIdentifier(msg);
  Serial.print("Unique ID: "); Serial.println(msg);
  DW1000Jang::getPrintableNetworkIdAndShortAddress(msg);
  Serial.print("Network ID & Device Address: "); Serial.println(msg);
  DW1000Jang::getPrintableDeviceMode(msg);
  Serial.print("Device mode: "); Serial.println(msg);

  transmit();

}

void transmit() {
  value_x = analogRead(x_axis) + 40;  // 0~1023
  value_y = analogRead(y_axis) + 10;   // 0~1023
  dx = value_x- joy_center + 12;
  dy = value_y - joy_center -1;
  duty = max(abs(dx) * 0.15, abs(dy) * 0.15);

        // 움직임을 결정하는 함수
    if ( abs(dx) < 15 && abs(dy) < 15) // 정지
        op_state = 0;
    else if ( abs(dx) < 15 && dy > 15) // 전진
          op_state = 1;
    else if ( abs(dx) < 15 && dy <= -15) // 후진
        op_state = 2;
    else if ( dx <= -15 && abs(dy) < 15) // 오른쪽
        op_state = 3;
    else if ( dx >= 15 && abs(dy) < 15) // 왼쪽
        op_state = 4;
    else if ( dx <= -15 && dy >= 15) // 직우
        op_state = 5;
    else if ( dx >= 15  && dy >= 15) // 직좌
        op_state = 6;
    else if ( dx <= -15 && dy <= -15) // 후우
        op_state = 7;
    else if ( dx >= 15 && dy <= -15) // 후좌
        op_state = 8;

  byte Msg[] = { DATA, SHORT_SRC_AND_DEST, SEQ_NUMBER++, 0,0, 0,0, 0,0, 0,0, duty, op_state};
    DW1000Jang::getNetworkId(&Msg[3]);
    memcpy(&Msg[5], receiver_address, 2);
    DW1000Jang::getNetworkId(&Msg[7]);
    DW1000Jang::getDeviceAddress(&Msg[9]);

   Serial.println("************************************");
   Serial.print("Trasmitted packet ... #");
   Serial.println(sentNum);
   Serial.print("Transmitted data : ");
    
   Serial.print("Duty:");
   Serial.print(int(Msg[11]));
    Serial.print(" op_state:");
    Serial.print(int(Msg[12]));
    Serial.print(" dx:");
    Serial.print(dx);
    Serial.print(" dy:");
    Serial.println(dy);
    
    DW1000Jang::setTransmitData(Msg, sizeof(Msg));
    delay(50);
    DW1000Jang::startTransmit();

    while (!DW1000Jang::isTransmitDone())
    {
#if defined(ESP8266)
        yield();
#endif
    }
    sentNum++;
    DW1000Jang::clearTransmitStatus();
    Serial.println();
}

void brake(){
  char brake_duty =0;
  char brake_state =0;

  byte Msg[] = { DATA, SHORT_SRC_AND_DEST, SEQ_NUMBER++, 0,0, 0,0, 0,0, 0,0, brake_duty, brake_state}; 
    DW1000Jang::getNetworkId(&Msg[3]);
    memcpy(&Msg[5], receiver_address, 2);
    DW1000Jang::getNetworkId(&Msg[7]);
    DW1000Jang::getDeviceAddress(&Msg[9]);
    DW1000Jang::setTransmitData(Msg, sizeof(Msg));
    delay(100);
    DW1000Jang::startTransmit();
        while (!DW1000Jang::isTransmitDone())
    {
#if defined(ESP8266)
        yield();
#endif
    }
    sentNum++;
    DW1000Jang::clearTransmitStatus();
    Serial.println();
}


void loop() {
  // 스위치가 눌렸으면
  if (digitalRead(sw) == LOW) {
    Serial.println("=== Brake ===");
    brake();
  }
  else
  {
    transmit();
  }
  
  
}