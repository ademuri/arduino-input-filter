#include "debounce-input.h"

DebounceInput::DebounceInput(uint32_t pin) : pin(pin) {}

bool DebounceInput::Rose() { return rose; }

bool DebounceInput::Fell() { return fell; }

bool DebounceInput::ReadFromSensor() { return digitalRead(pin); }

bool DebounceInput::DoRun() {
  rose = false;
  fell = false;

  if (millis() - state_started_at_millis >= kDebounceTimeMillis) {
    if (stable_state != current_state) {
      stable_state = current_state;
      last_successful_change_at_millis = millis();

      if (stable_state) {
        rose = true;
      } else {
        fell = true;
      }
    }
  }

  bool input_value = ReadFromSensor();
  if (input_value == current_state) {
    return stable_state;
  }

  if (millis() - last_successful_change_at_millis >= kDebounceTimeMillis) {
    if (stable_state != input_value) {
      if (input_value) {
        rose = true;
      } else {
        fell = true;
      }
    }

    stable_state = input_value;
    current_state = input_value;
    last_successful_change_at_millis = millis();
    state_started_at_millis = millis();
  }

  // Input != current_state
  state_started_at_millis = millis();
  current_state = input_value;
  return stable_state;
}

#ifndef ARDUINO
int DebounceInput::digitalRead(uint32_t pin) {
  (void)pin;
  return pin_value_;
}
#endif
