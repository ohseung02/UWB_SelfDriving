#include <DW1000Jang.hpp>
#include <DW1000JangUtils.hpp>
#include <DW1000JangTime.hpp>
#include <DW1000JangConstants.hpp>

const uint8_t PIN_RST = 7; 
const uint8_t PIN_IRQ = 2; 
const uint8_t PIN_SS = 10; 

#define MAX_MESSAGE_LENGTH 128 // 최대 메세지 길이 + 헤더 길이

byte DATA = 0x01;
byte SHORT_SRC_AND_DEST = 0x88;
byte SEQ_NUMBER = 1;

byte receiver_address[] = {0x05, 0x00};

String input;
byte transmit_data[MAX_MESSAGE_LENGTH + 1]; 
byte receive_data[MAX_MESSAGE_LENGTH + 1];


device_configuration_t DEFAULT_CONFIG = {
    false, true, true, true, false,
    SFDMode::STANDARD_SFD,
    Channel::CHANNEL_5,
    DataRate::RATE_850KBPS,
    PulseFrequency::FREQ_64MHZ,
    PreambleLength::LEN_2048,
    PreambleCode::CODE_10
};

interrupt_configuration_t DEFAULT_INTERRUPT_CONFIG = {
    false, true, true, false, true
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


void setup() 
{
  Serial.begin(115200);
  Serial.println(F("### UWB Chat Program ###"));

  DW1000Jang::initialize(PIN_SS, PIN_IRQ, PIN_RST);
  DW1000Jang::applyConfiguration(DEFAULT_CONFIG);
  DW1000Jang::applyInterruptConfiguration(DEFAULT_INTERRUPT_CONFIG);
  DW1000Jang::enableFrameFiltering(FRAME_FILTER_CONFIG);

  DW1000Jang::setNetworkId(9);
  DW1000Jang::setDeviceAddress(3); // Set your device address here
  DW1000Jang::setAntennaDelay(16436);

  transmit_data[0] = DATA;
  transmit_data[1] = SHORT_SRC_AND_DEST;
  DW1000Jang::getNetworkId(&transmit_data[3]);
  memcpy(&transmit_data[5], receiver_address, 2);
  DW1000Jang::getNetworkId(&transmit_data[7]);
  DW1000Jang::getDeviceAddress(&transmit_data[9]);

  
  DW1000Jang::attachReceivedHandler(receive);
  Serial.println(F("Chat program started. Type messages and send."));
  DW1000Jang::startReceive();
}

void loop() 
{
  if (Serial.available() > 0) 
  {
    DW1000Jang::forceTRxOff();
    input = Serial.readStringUntil('\n');
    input.trim(); // 문자열 끝의 공백 또는 개행 문자 제거

    if (input.length() > 0 && input.length() <= MAX_MESSAGE_LENGTH) 
    {
      int headerLength = 12; // 헤더 길이
      int totalLength = headerLength + input.length(); // 총 데이터 길이

      transmit_data[2] = SEQ_NUMBER++;
      transmit_data[11] = (byte)totalLength;
      input.getBytes(&transmit_data[headerLength], input.length() + 1); 

      DW1000Jang::setTransmitData(transmit_data, totalLength);
      DW1000Jang::startTransmit();
      DW1000Jang::clearTransmitStatus();

      Serial.print("B: ");
      for (int i = headerLength; i < totalLength; i++) {
          Serial.print(char(transmit_data[i])); 
      }
      Serial.println();
    }
    DW1000Jang::startReceive();
  }
}

void receive() 
{
  DW1000Jang::getReceivedData(receive_data, MAX_MESSAGE_LENGTH + 1);
  Serial.print("A: ");
  for (int i = 12; i < receive_data[11] ; i++) {
    Serial.print(char(receive_data[i])); 
  }
  Serial.println();
  DW1000Jang::clearReceiveStatus();
  DW1000Jang::forceTRxOff();
  DW1000Jang::startReceive();
}