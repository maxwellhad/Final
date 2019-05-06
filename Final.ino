#include "Button.h"

int led[4] = {34, 33, 31, 32};
boolean ledActive[4] = {HIGH, HIGH, HIGH, HIGH};
int btn1Pin = 36;
int btn2Pin = 35;
int btn3Pin = 29;
int btn4Pin = 30;
int btnReversePin = 25;
int stepTime;
int currentLed = 0;
boolean ledOn = HIGH;
int tempo = A8;
int sends[4] = {28, 27, 26, 37};
int stepp = 0;
boolean direct = LOW;
unsigned long lastStepTime = 0;

Button btn1(btn1Pin);
Button btn2(btn2Pin);
Button btn3(btn3Pin);
Button btn4(btn4Pin);
Button btnReverse(btnReversePin);


void setup()
{

  for (int i = 0; i < 4; i++)
  {
    pinMode(led[i], OUTPUT);
    pinMode(sends[i], OUTPUT);
  }
    

  pinMode(btn1Pin, INPUT);
  pinMode(btn2Pin, INPUT);
  pinMode(btn3Pin, INPUT);
  pinMode(btn4Pin, INPUT);
  pinMode(btnReversePin, INPUT);

  pinMode(tempo, INPUT);
  analogWriteResolution(12);

  btn1.pressButton(led1);
  btn2.pressButton(led2);
  btn3.pressButton(led3);
  btn4.pressButton(led4);
  btnReverse.pressButton(ledReverse);

  Serial.begin(9600);
}

void loop()
{
  btn1.process();
  btn2.process();
  btn3.process();
  btn4.process();
  btnReverse.process();
  
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
        btn1.process();
        btn2.process();
        btn3.process();
        btn4.process();
        btnReverse.process();
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
        btn1.process();
        btn2.process();
        btn3.process();
        btn4.process();
        btnReverse.process();
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

void led1()
{
  ledActive[0]=!ledActive[0];

}

void led2()
{
  ledActive[1]=!ledActive[1];


}

void led3()
{
  ledActive[2]=!ledActive[2];
}

void led4()
{
  ledActive[3]=!ledActive[3];

}

void ledReverse()
{
  direct=!direct;
}
