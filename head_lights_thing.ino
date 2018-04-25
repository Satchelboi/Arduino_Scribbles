const int buttonPin = 2;
const int ledPinRed = 9;
const int ledPinBlue = 10;
const int ledPinGreen = 11;
int buttonInput = 0;
int buttonCount = 0;
int looper = 0;

void setup() {
  pinMode(buttonPin, INPUT);
}

void loop() {
  analogWrite(ledPinRed, 255);
  analogWrite(ledPinGreen, 120);
  analogWrite(ledPinBlue, 0);
  buttonInput = digitalRead(buttonPin);
  while (looper = 0)
  {
    buttonCount++;
    buttonInput = LOW;
    delay(250);
    buttonInput = digitalRead(buttonPin);
    if (buttonInput == HIGH)
    {
      looper = 0;
    }
    else
    {
      looper = 1;
    }
  }
  looper = 0;
  if (buttonCount == 1)
  {
    while (looper == 0)
    {
      for (int fadeValue = 0; fadeValue <= 255; fadeValue += 2)
      {
        analogWrite(ledPinRed, fadeValue);
        analogWrite(ledPinGreen, fadeValue / 2);
      }
      buttonInput = digitalRead(buttonPin);
      if (buttonInput == HIGH)
      {
        looper = 1;
      }
      else
      {
        looper = 0;
      }
    }
  }
  looper = 0;
  if (buttonCount == 2)
  {
    while (looper = 0)
    {
      analogWrite(ledPinRed, 255);
      analogWrite(ledPinGreen, 120);
      delay(250);
      analogWrite(ledPinRed, 0);
      analogWrite(ledPinGreen, 0);
      delay(100);
      buttonInput = digitalRead(buttonPin);
      if (buttonInput == HIGH)
      {
        looper = 1;
      }
      else
      {
        looper = 0;
      }
    }
  }
}
