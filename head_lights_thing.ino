// This program gives control over a set of different behaviors
// for RGB led lights.
// ------------------------------------------------------------
// Controls:
// Fade -> Press button briefly once
// Blink -> Press and hold button for 0.5 seconds
// Shift -> Press and hold button for 2.0 seconds

#define debounce 20
#define holdTimeBlink  500
#define holdTimeShift 2000
#define buttonPin  2
#define ledPinRed  9
#define ledPinGreen  10
#define ledPinBlue 11
int buttonInput = 0;
int buttonBuff = 0;
long buttonDown;
long buttonUp;
bool ignoreRelease = false;

void setup() {

  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);

  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);

  analogWrite(ledPinRed, 0);
  analogWrite(ledPinGreen, 0);
  analogWrite(ledPinBlue, 0);
}

void loop() {

  buttonInput = digitalRead(buttonPin);
  analogWrite(ledPinRed, 255);
  analogWrite(ledPinGreen, 100);

  // Check if button is not pressed and record time if not pressed
  if (buttonInput == LOW && buttonBuff == HIGH && (millis() - buttonUp) < debounce) {
    buttonDown = millis();
  }

  // Check if button was released after being pressed and store time in state
  if (buttonInput == HIGH && buttonBuff == LOW && (millis() - buttonDown) > holdTimeBlink) {
    if (ignoreRelease == false)
      fade();
    else
      ignoreRelease = false;
    buttonUp = millis();
  }

  // Check if button time held is past that holdTimeBlink variable
  if (buttonInput == LOW && (millis() - buttonDown) > holdTimeBlink) {
    blinker();
    ignoreRelease = true;
    buttonDown = millis();
  }

  // Check if button time held is past the holdTimeShift variable
  if (buttonInput == LOW && (millis() - buttonDown) > holdTimeShift) {
    shift();
    ignoreRelease = true;
    buttonDown = millis();
  }

  buttonBuff = buttonInput;

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
  }

  // Turns Red down
  for (shiftValue = 255; shiftValue >= 0; shiftValue -= 1) {
    analogWrite(ledPinRed, shiftValue);
  }

  // Turns Blue up
  for (shiftValue = 0; shiftValue <= 255; shiftValue += 1) {
    analogWrite(ledPinBlue, shiftValue);
  }

  // Turns Green down
  for (shiftValue = 255; shiftValue >= 0; shiftValue -= 1) {
    analogWrite(ledPinGreen, shiftValue);
  }

  // Turns Red up
  for (shiftValue = 0; shiftValue <= 255; shiftValue += 1) {
    analogWrite(ledPinRed, shiftValue);
  }

  // Turns Blue down
  for (shiftValue = 255; shiftValue >= 0; shiftValue -= 1) {
    analogWrite(ledPinBlue, shiftValue);
  }
}

