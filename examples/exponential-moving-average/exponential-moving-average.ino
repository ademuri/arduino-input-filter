#include "exponential-moving-average-input.h"

const uint8_t kInputPin = 0;
const uint8_t kLedPin = 13;
ExponentialMovingAverageInput<uint32_t> *input;

void setup() {
  pinMode(kInputPin, INPUT_PULLUP);
  input = new ExponentialMovingAverageInput<uint32_t>(kInputPin, 255);
  input->SetLogToSerial(true);

  pinMode(kLedPin, OUTPUT);
}

void loop() {
  input->Run();
  digitalWrite(kLedPin, input->GetFilteredValue() > 511);
  Serial.flush();
  delay(50);
}