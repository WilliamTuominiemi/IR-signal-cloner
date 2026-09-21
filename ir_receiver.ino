#include <IRremote.hpp>
#define IR_RECEIVE_PIN 7
#define IR_SEND_PIN 5
#define TRANSMIT_BUTTON_PIN 2
#define RECORD_BUTTON_PIN 3
#define RECORD_INDC_LED 12

int transmitButtonState = 0;
int recordButtonState = 0;

void setup()
{
  pinMode(TRANSMIT_BUTTON_PIN, INPUT);
  pinMode(RECORD_BUTTON_PIN, INPUT);
  pinMode(RECORD_INDC_LED, OUTPUT);

  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN);
}

void loop() {
  transmitButtonState = digitalRead(TRANSMIT_BUTTON_PIN);
  recordButtonState = digitalRead(RECORD_BUTTON_PIN);

  if (transmitButtonState == HIGH) {
    IrSender.sendNEC(0x01, 0x02, 1); 
  } 

  if (recordButtonState == HIGH) {
    digitalWrite(RECORD_INDC_LED, HIGH);
  } else {
    digitalWrite(RECORD_INDC_LED, LOW);
  }

  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      IrReceiver.printIRResultShort(&Serial);
      IrReceiver.printIRSendUsage(&Serial);
      IrReceiver.resume();
  }
}