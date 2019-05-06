#include "Arduino.h"
#include "Button.h"

Button::Button(int _buttonPin)
{
  buttonPin = _buttonPin;

  pinMode(buttonPin, INPUT);
}

void Button::process()
{
  lastButtonState = buttonState;
  buttonState = digitalRead(buttonPin);

  if (lastButtonState == LOW && buttonState == HIGH) {
    pressCallback();
  }
  if (lastButtonState == HIGH && buttonState == LOW) {
//    releaseCallback();
  }
}

void Button::pressButton(void (*f)())    //button down
{
  pressCallback = *f;
}

void Button::releaseButton(void (*f)())  //button release
{
  releaseCallback = *f;
}
