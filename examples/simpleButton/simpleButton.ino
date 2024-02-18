/*
  Example usage of a single button, utilising short and long press.
  Pushbutton is connected between BTN_PIN and ground
*/

#include <inputs.h>

#define LED 13
#define BTN_PIN 8

Button btn1(BTN_PIN, LONGPRESS);  // default pinMode is set to INPUT_PULLUP


void setup() {
  pinMode(LED, OUTPUT);
  btn1.longPressDuration = 1000;  // if not set, default is 600ms
  btn1.setDebounceTime(50);  // should be kept minimal; if not set, default is 20ms
}


void loop() {
  int state = btn1.getState();  // getState() should be called once in a loop

  // short press is registered when button is pressed for less than longPressDuration, then released
  if (state == RELEASE) {  
    // blink once
    digitalWrite(LED, 1);
    delay(100);
    digitalWrite(LED, 0);
  }

  // long press is registered when button is pressed for more than longPressDuration, don't care about release
  if (state == SHORTPASS) {  
    // blink twice
    digitalWrite(LED, 1);
    delay(100);
    digitalWrite(LED, 0);
    delay(100);
    digitalWrite(LED, 1);
    delay(100);
    digitalWrite(LED, 0);

  }

}
