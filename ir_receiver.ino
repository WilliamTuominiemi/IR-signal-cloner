#include <IRremote.hpp>
#define IR_RECEIVE_PIN 7
#define IR_SEND_PIN 3

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN);
}

void loop() {
  IrSender.sendNEC(0x01, 0x02, 1); 
  delay(1000); 

  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      IrReceiver.printIRResultShort(&Serial);
      IrReceiver.printIRSendUsage(&Serial);
      IrReceiver.resume();
  }
}