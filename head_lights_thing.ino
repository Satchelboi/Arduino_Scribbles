// This program gives control over a set of different behaviors
// for RGB led lights.
// ------------------------------------------------------------
// Controls:
// Fade -> Press button briefly once
// Blink -> Press and hold button for 0.5 seconds
// Shift -> Press and hold button for 2.0 seconds

const int debounce = 20;
const int holdTimeBlink = 500;
const int holdTimeShift = 2000;
const int buttonPin = 19;
const int ledPinRed = 9;
const int ledPinGreen = 10;
const int ledPinBlue = 11;
int buttonInput = 0;
int buttonBuff = 0;
long buttonDown;
long buttonUp;
bool ignoreRelease = false;

void setup() {

  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, LOW);

  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);

  analogWrite(ledPinRed, 255);
  analogWrite(ledPinGreen, 100);
  analogWrite(ledPinBlue, 0);
}

void loop() {
  buttonDown = 0;
  buttonInput = LOW;
  analogWrite(ledPinRed, 255);
  analogWrite(ledPinGreen, 100);
  buttonInput = digitalRead(buttonPin);
  Serial.println("Loop just started");
  // Check if button is not pressed and record time if not pressed
  if (buttonInput == HIGH) {
    buttonDown = millis();
    Serial.println("Button Read");
  }

  // Check if button was released after being pressed and store time in state
  if (buttonDown > long(debounce) && buttonDown < long(holdTimeBlink)) {
    if (ignoreRelease == false) {
      Serial.println("Fade function called");
      fade();
    }
    else
      ignoreRelease = false;
    buttonUp = millis();
  }

  // Check if button time held is past that holdTimeBlink variable
  if (buttonDown > long(holdTimeBlink) && buttonDown < long(holdTimeShift)) {
    Serial.println("Blinker function called");
    blinker();
    ignoreRelease = true;
    buttonDown = millis();
  }

  // Check if button time held is past the holdTimeShift variable
  if (buttonDown > long(holdTimeShift)) {
    Serial.println("Shift function called");
    shift();
    ignoreRelease = true;
    buttonDown = millis();
  }

}

// Static color blinking
void blinker() {

  analogWrite(ledPinRed, 255);
  analogWrite(ledPinGreen, 120);
  delay(750);
  analogWrite(ledPinRed, 0);
  analogWrite(ledPinGreen, 0);
  delay(100);
}

// Fades color
void fade() {

  for (int fadeValue = 100; fadeValue <= 150; fadeValue += 1) {
    analogWrite(ledPinRed, 255);
    analogWrite(ledPinGreen, fadeValue);
  }
}

// Cycles through the rainbow, because why not
void shift() {

  int shiftValue;
  analogWrite(ledPinRed, 255);

  // Turns Green up
  for (shiftValue = 0; shiftValue <= 255; shiftValue += 1) {
    analogWrite(ledPinGreen, shiftValue);
    delay(8);
  }

  // Turns Red down
  for (shiftValue = 255; shiftValue >= 0; shiftValue -= 1) {
    analogWrite(ledPinRed, shiftValue);
    delay(8);
  }

  // Turns Blue up
  for (shiftValue = 0; shiftValue <= 255; shiftValue += 1) {
    analogWrite(ledPinBlue, shiftValue);
    delay(8);
  }

  // Turns Green down
  for (shiftValue = 255; shiftValue >= 0; shiftValue -= 1) {
    analogWrite(ledPinGreen, shiftValue);
    delay(8);
  }

  // Turns Red up
  for (shiftValue = 0; shiftValue <= 255; shiftValue += 1) {
    analogWrite(ledPinRed, shiftValue);
    delay(8);
  }

  // Turns Blue down
  for (shiftValue = 255; shiftValue >= 0; shiftValue -= 1) {
    analogWrite(ledPinBlue, shiftValue);
    delay(8);
  }
}
