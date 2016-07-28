int ledPin1 = 13;                 // LED connected to digital pin 13
int ledPin2 = 10;                 // LED connected to digital pin 10
int buttonPin = 2;
int button = 0;
int curMode = 0;

unsigned long blinkTimeLed1 = 0; // тут будет храниться время с начала включения светодиода 1.
unsigned long blinkTimeLed2 = 0; // тут будет храниться время с начала включения светодиода 2.

boolean swOn = false;

void setup()
{
  pinMode(ledPin1, OUTPUT);      // sets the digital pin as output
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  Serial.begin(9600);
}

void loop()
{
  runCurMode();
  changeModeIfNeeded();
  delay(10);
}

void runCurMode() {

  if (curMode == 1) { // режим 1.
    virtualWallMode(); // виртуальная стена.
  } else if (curMode == 2) { // режим 2.
    lighthouseMode(); // лайтхаус.
  } else {
    offMode(); // выключить все.
  }
}

void changeModeIfNeeded() {

  button = digitalRead(buttonPin);
  if ((button == LOW) && (curMode == 0) && (!swOn)) {
    offMode();
    curMode = 1;
    swOn = true;
    delay(100);
  } else  if ((button == LOW) && (curMode == 1) && (!swOn)) {
    offMode();
    curMode = 2;
    swOn = true;
    delay(100);
  } else  if ((button == LOW) && (curMode == 2) && (!swOn)) {
    curMode = 0;
    swOn = true;
    delay(100);
  } else  if ((button == HIGH) && (swOn)) {
    swOn = false;
    delay(100);
  }

}

void virtualWallMode() {
  runLedBlink(ledPin1);
}

void lighthouseMode() {
  runLedBlink(ledPin2);
}

void offMode() {
  ledOff(ledPin1);
  ledOff(ledPin2);
  blinkTimeLed1 = 0;
  blinkTimeLed1 = 0;
}

void runLedBlink(int ledPin) {

  unsigned long curTime;
  unsigned long* blinkTime;
  curTime = millis();

  if (ledPin == ledPin1) {
    blinkTime = blinkTimeLed1;
  } else {
    blinkTime = blinkTimeLed2;
  }

  if (blinkTime == 0) { // Если светодиод еще не горит, то включаем.
    ledOn(ledPin);
    blinkTime = curTime;
  }

  if (curTime - blinkTime <= 500) { // Если светодиод горит, то оставляем его включенным еще на пол секунды.
    ledOn(ledPin);
  }

  if (curTime - blinkTime > 500) { // Если прошло пол секунды то выключаем светодиод.
    ledOff(ledPin);
  }

  if (curTime - blinkTime > 5000) { // Если прошло 5 секунд, то сбрасываем.
    ledOff(ledPin);
    blinkTime = 0;
  }

}

void ledOn(int ledPin) {
  digitalWrite(ledPin, HIGH);
}

void ledOff(int ledPin) {
  digitalWrite(ledPin, LOW);
}

