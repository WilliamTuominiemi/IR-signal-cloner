#include <IRremote.hpp>
#define IR_RECEIVE_PIN 7
#define IR_SEND_PIN 5
#define TRANSMIT_BUTTON_PIN 2
#define RECORD_BUTTON_PIN 3
#define RECORD_INDC_LED 12

int transmitButtonState = 0;
int recordButtonState = 0;

IRData captured_data;

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
    Serial.println("SENDING...");
    Serial.println(captured_data.decodedRawData, HEX);
    printIRResultShort(&Serial, &captured_data);

    IrSender.write(captured_data.protocol,
      captured_data.address,
      captured_data.command,
      0);
  } 

  if (recordButtonState == HIGH) {
    digitalWrite(RECORD_INDC_LED, HIGH);

    if (IrReceiver.decode()) {
      Serial.println("RECEIVING...");
      captured_data = IrReceiver.decodedIRData;
      Serial.println(captured_data.decodedRawData, HEX);
      IrReceiver.printIRResultShort(&Serial);
      IrReceiver.printIRSendUsage(&Serial);
      IrReceiver.resume();
    }
  } else {
    digitalWrite(RECORD_INDC_LED, LOW);
  }
}