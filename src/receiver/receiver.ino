int LEFT_BACK_PWM = 5;// motor 1 speed (0~255) -- LEFT FRONT WHEEL
int LEFT_BACK_DIR = 4;// motor 1 direction (0 or 1)
int RIGHT_BACK_PWM = 6;// motor 2 speed (0~255) -- RIGHT FRONT WHEEL
int RIGHT_BACK_DIR = A1;// motor 2 direction (0 or 1)
int LEFT_FRONT_PWM = 9;// motor 3 speed (0~255) -- RIGHT BACK WHEEL
int LEFT_FRONT_DIR = 8;// motor 3 direction (0 or 1)
int RIGHT_FRONT_PWM = 3;// motor 4 speed (0~255) -- LEFT BACK WHEEL
int RIGHT_FRONT_DIR = A2;// motor 4 direction (0 or 1)


int duty, op_state;
int sw1, sw2;

#include <DW1000Jang.hpp>

#if defined(ESP8266)
//const uint8_t PIN_RST = 5; // reset pin
//const uint8_t PIN_IRQ = 4; // irq pin
const uint8_t PIN_SS = 15; // spi select pin
#else
//const uint8_t PIN_RST = 7; // reset pin
//const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = 10; // spi select pin
#endif

int16_t numReceived = 0; // todo check int type
String message;

device_configuration_t DEFAULT_CONFIG = {
    false,
    true,
    true,
    true,
    false,
    SFDMode::STANDARD_SFD,
    Channel::CHANNEL_5,
    DataRate::RATE_850KBPS,
    PulseFrequency::FREQ_16MHZ,
    PreambleLength::LEN_128,
    PreambleCode::CODE_3
};

frame_filtering_configuration_t FRAME_FILTER_CONFIG = {
    false,
    false,
    true,
    false,
    false,
    false,
    false,
    false
};

void setup() {
  // DEBUG monitoring
  Serial.begin(115200);
  Serial.println(F("### DW1000Jang-arduino-receiver-test ###"));
  // initialize the driver
  DW1000Jang::initializeNoInterrupt(PIN_SS);
  Serial.println(F("DW1000Jang initialized ..."));

  DW1000Jang::applyConfiguration(DEFAULT_CONFIG);
  DW1000Jang::enableFrameFiltering(FRAME_FILTER_CONFIG);

  DW1000Jang::setDeviceAddress(7);
  DW1000Jang::setNetworkId(10);

  DW1000Jang::setAntennaDelay(16436);
  Serial.println(F("Committed configuration ..."));
  // DEBUG chip info and registers pretty printed
  char msg[128];
  DW1000Jang::getPrintableDeviceIdentifier(msg);
  Serial.print("Device ID: "); Serial.println(msg);
  DW1000Jang::getPrintableExtendedUniqueIdentifier(msg);
  Serial.print("Unique ID: "); Serial.println(msg);
  DW1000Jang::getPrintableNetworkIdAndShortAddress(msg);
  Serial.print("Network ID & Device Address: "); Serial.println(msg);
  DW1000Jang::getPrintableDeviceMode(msg);
  Serial.print("Device mode: "); Serial.println(msg);

  pinMode(LEFT_FRONT_DIR, OUTPUT);
  pinMode(RIGHT_FRONT_DIR, OUTPUT);
  pinMode(RIGHT_BACK_DIR, OUTPUT);
  pinMode(LEFT_BACK_DIR, OUTPUT);
  pinMode(LEFT_FRONT_PWM, OUTPUT);
  pinMode(RIGHT_FRONT_PWM, OUTPUT);
  pinMode(RIGHT_BACK_PWM, OUTPUT);
  pinMode(LEFT_BACK_PWM, OUTPUT);

}

void North(int duty)
{
  analogWrite(LEFT_FRONT_PWM, duty); 
  analogWrite(RIGHT_FRONT_PWM, duty);
  analogWrite(LEFT_BACK_PWM, duty);  
  analogWrite(RIGHT_BACK_PWM, duty); 

  digitalWrite(LEFT_FRONT_DIR, LOW);  
  digitalWrite(RIGHT_FRONT_DIR, LOW);
  digitalWrite(LEFT_BACK_DIR, LOW);
  digitalWrite(RIGHT_BACK_DIR, LOW);
}

void South(int duty)
{
  analogWrite(LEFT_FRONT_PWM, duty); 
  analogWrite(RIGHT_FRONT_PWM, duty);
  analogWrite(LEFT_BACK_PWM, duty); 
  analogWrite(RIGHT_BACK_PWM, duty); 

  digitalWrite(LEFT_FRONT_DIR, HIGH);
  digitalWrite(RIGHT_FRONT_DIR, HIGH);
  digitalWrite(RIGHT_BACK_DIR, HIGH);
  digitalWrite(LEFT_BACK_DIR, HIGH);
}

void West(int duty)// 좌측 앞바퀴, 우측 뒷바퀴 정방향, 우측 앞바퀴, 좌측 뒷바퀴 역방향
{
  analogWrite(RIGHT_FRONT_PWM, duty); 
  analogWrite(LEFT_FRONT_PWM, duty); 
  analogWrite(RIGHT_BACK_PWM, duty); 
  analogWrite(LEFT_BACK_PWM, duty); 


  digitalWrite(LEFT_FRONT_DIR, HIGH);
  digitalWrite(RIGHT_FRONT_DIR, LOW);
  digitalWrite(LEFT_BACK_DIR, LOW);
  digitalWrite(RIGHT_BACK_DIR, HIGH);
}

void East(int duty)// 좌측 앞바퀴, 우측 뒷바퀴 역방향, 우측 앞바퀴, 좌측 뒷바퀴 정방향
{
  analogWrite(RIGHT_FRONT_PWM, duty); 
  analogWrite(LEFT_FRONT_PWM, duty); 
  analogWrite(RIGHT_BACK_PWM, duty);  
  analogWrite(LEFT_BACK_PWM, duty);  
  
  digitalWrite(LEFT_FRONT_DIR, LOW);
  digitalWrite(RIGHT_FRONT_DIR, HIGH);
  digitalWrite(LEFT_BACK_DIR, HIGH);
  digitalWrite(RIGHT_BACK_DIR, LOW);
}

void Stop()
{
  analogWrite(RIGHT_FRONT_PWM, 0); 
  analogWrite(RIGHT_BACK_PWM, 0); 
  analogWrite(LEFT_BACK_PWM, 0); 
  analogWrite(LEFT_FRONT_PWM, 0); 
}

void TURN_LEFT(int duty)
{
  analogWrite(RIGHT_FRONT_PWM, duty);
  analogWrite(LEFT_FRONT_PWM, duty); 
  analogWrite(RIGHT_BACK_PWM, duty); 
  analogWrite(LEFT_BACK_PWM, duty); 
  
  digitalWrite(RIGHT_FRONT_DIR, HIGH); 
  digitalWrite(LEFT_FRONT_DIR, LOW);
  digitalWrite(RIGHT_BACK_DIR, HIGH);
  digitalWrite(LEFT_BACK_DIR, LOW);
}

void TURN_RIGHT(int duty)
{
  analogWrite(RIGHT_FRONT_PWM, duty);
  analogWrite(LEFT_FRONT_PWM, duty); 
  analogWrite(RIGHT_BACK_PWM, duty); 
  analogWrite(LEFT_BACK_PWM, duty); 
  
  digitalWrite(RIGHT_FRONT_DIR, LOW);
  digitalWrite(LEFT_FRONT_DIR, HIGH);
  digitalWrite(RIGHT_BACK_DIR, LOW);
  digitalWrite(LEFT_BACK_DIR, HIGH);
}

void TURN_FRONT_RIGHT(int duty)
{
  analogWrite(RIGHT_FRONT_PWM, duty-10);
  analogWrite(LEFT_FRONT_PWM, duty+20); 
  analogWrite(RIGHT_BACK_PWM, duty-10); 
  analogWrite(LEFT_BACK_PWM, duty+20); 
  
  digitalWrite(LEFT_FRONT_DIR, LOW);  
  digitalWrite(RIGHT_FRONT_DIR, LOW);
  digitalWrite(LEFT_BACK_DIR, LOW);
  digitalWrite(RIGHT_BACK_DIR, LOW);
}

void TURN_FRONT_LEFT(int duty)
{
  analogWrite(RIGHT_FRONT_PWM, duty+20);
  analogWrite(LEFT_FRONT_PWM, duty-10); 
  analogWrite(RIGHT_BACK_PWM, duty+20); 
  analogWrite(LEFT_BACK_PWM, duty-10); 
  
  digitalWrite(LEFT_FRONT_DIR, LOW);  
  digitalWrite(RIGHT_FRONT_DIR, LOW);
  digitalWrite(LEFT_BACK_DIR, LOW);
  digitalWrite(RIGHT_BACK_DIR, LOW);
}

void TURN_BEHIND_RIGHT(int duty)
{
  analogWrite(RIGHT_FRONT_PWM, duty-10);
  analogWrite(LEFT_FRONT_PWM, duty+20); 
  analogWrite(RIGHT_BACK_PWM, duty-10); 
  analogWrite(LEFT_BACK_PWM, duty+20); 
  
  digitalWrite(RIGHT_FRONT_DIR, LOW);
  digitalWrite(LEFT_FRONT_DIR, HIGH);
  digitalWrite(RIGHT_BACK_DIR, LOW);
  digitalWrite(LEFT_BACK_DIR, HIGH);
}

void TURN_BEHIND_LEFT(int duty)
{
  analogWrite(RIGHT_FRONT_PWM, duty+20);
  analogWrite(LEFT_FRONT_PWM, duty-10); 
  analogWrite(RIGHT_BACK_PWM, duty+20); 
  analogWrite(LEFT_BACK_PWM, duty-10); 
  
  digitalWrite(RIGHT_FRONT_DIR, HIGH);
  digitalWrite(LEFT_FRONT_DIR, LOW);
  digitalWrite(RIGHT_BACK_DIR, HIGH);
  digitalWrite(LEFT_BACK_DIR, LOW);
}

void loop() {
  DW1000Jang::startReceive();
  while(!DW1000Jang::isReceiveDone()) {
    #if defined(ESP8266)
    yield();
    #endif
  }
  DW1000Jang::clearReceiveStatus();
  numReceived++;
  // get data as string
  DW1000Jang::getReceivedData(message);

  Serial.println("************************************");
  Serial.print("Received message ... #"); Serial.println(numReceived);


  Serial.print("Receivied Data : "); 
  for(int i=11; i<13; i++){
    Serial.print(int(message[i]));
    Serial.print(" ");
  }
  duty=int(message[11]);
  op_state=int(message[12]);

  if (op_state == 9)
    TURN_LEFT(duty);
  if(op_state ==10)
    TURN_RIGHT(duty);

 if (op_state == 0 || (duty > 0 && duty < 80 && op_state >= 1 && op_state <= 8)) 
{
  if(op_state == 0)
    Stop();
  else if(op_state == 1)
    North(duty);
  else if(op_state == 2)
    South(duty);
  else if(op_state == 3)
    East(duty);
  else if(op_state == 4)
    West(duty);
  else if(op_state == 5)
    TURN_FRONT_RIGHT(duty);
  else if(op_state == 6)
    TURN_FRONT_LEFT(duty);
  else if(op_state == 7)
    TURN_BEHIND_RIGHT(duty);
  else if(op_state == 8)
    TURN_BEHIND_LEFT(duty);
}
  delay(50);
}