#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"

class Button
{
  public:
    Button(int _buttonPin);
    
    void process();
    void pressButton(void (*f)());
    void releaseButton(void (*f)());
    void (*pressCallback)();
    void (*releaseCallback)();

    byte buttonPin;
    bool buttonState;
    bool lastButtonState;

  private:
};

#endif
