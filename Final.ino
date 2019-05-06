#include "Button.h"

int led[4] = {34, 33, 31, 32};
boolean ledActive[4] = {HIGH, HIGH, HIGH, HIGH};
int btnUpPin = 36;
int btnDownPin = 35;
int btnLeftPin = 29;
int btnRightPin = 30;
int btnSelectPin = 25;
int stepTime;
int currentLed = 0;
boolean ledOn = HIGH;
int tempo = A8;
int sends[4] = {28, 27, 26, 37};
int stepp = 0;
boolean direct = LOW;
unsigned long lastStepTime = 0;

Button btnUp(btnUpPin);
Button btnDown(btnDownPin);
Button btnLeft(btnLeftPin);
Button btnRight(btnRightPin);
Button btnSelect(btnSelectPin);


void setup()
{

  for (int i = 0; i < 4; i++)
  {
    pinMode(led[i], OUTPUT);
    pinMode(sends[i], OUTPUT);
  }
    

  pinMode(btnUpPin, INPUT);
  pinMode(btnDownPin, INPUT);
  pinMode(btnLeftPin, INPUT);
  pinMode(btnRightPin, INPUT);
  pinMode(btnSelectPin, INPUT);

  pinMode(tempo, INPUT);
  analogWriteResolution(12);

  btnUp.pressButton(ledUp);
  btnDown.pressButton(ledDown);
  btnLeft.pressButton(ledLeft);
  btnRight.pressButton(ledRight);
  btnSelect.pressButton(ledSelect);

  Serial.begin(9600);
}

void loop()
{
  btnUp.process();
  btnDown.process();
  btnLeft.process();
  btnRight.process();
  btnSelect.process();
  
  stepTime=map(analogRead(tempo), 0, 1023, 20, 750);
  
  if (millis() > lastStepTime + stepTime)
  {
    digitalWrite(led[stepp], LOW);
    digitalWrite(sends[stepp], HIGH);
    
    if(direct == HIGH)
    {
      stepp++;
      if (stepp > 3 )
        stepp = 0;
      while (ledActive[stepp] == LOW)
      {
        btnUp.process();
        btnDown.process();
        btnLeft.process();
        btnRight.process();
        btnSelect.process();
        stepp++;
      if (stepp > 3 )
        stepp = 0;
      }
        digitalWrite(led[stepp], HIGH);
        digitalWrite(sends[stepp], LOW);
    }

    else
    {
      
      stepp--;
      if (stepp < 0)
        stepp = 3;
      while (ledActive[stepp] == LOW)
      {
        btnUp.process();
        btnDown.process();
        btnLeft.process();
        btnRight.process();
        btnSelect.process();
        stepp--;
      if (stepp < 0)
        stepp = 3;
      }
        digitalWrite(led[stepp], HIGH);
        digitalWrite(sends[stepp], LOW);
    }

    //resets the step length
    lastStepTime = millis();
  }

}

void ledUp()
{
  ledActive[0]=!ledActive[0];

}

void ledDown()
{
  ledActive[1]=!ledActive[1];


}

void ledLeft()
{
  ledActive[2]=!ledActive[2];
}

void ledRight()
{
  ledActive[3]=!ledActive[3];

}

void ledSelect()
{
  direct=!direct;
}
