#include <Joystick.h>
#include <Encoder.h>
Joystick_ Joystick;

const int TOTAL_COUNT = 14;
const int PINS[] = {6,7,8,9,10,11,12,A0,A1,A2,A3,A4,A5,MISO};

const int TOGGLE_COUNT = 8; // TEMP
const int TOGGLE[] = {6,7,8,9,10,11,12,A0};
int LAST_TOGGLE[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};

const int THREEWAY_COUNT = 3; // TEMP
const int THREEWAY_UP[] = {A1,A2,A3};
const int THREEWAY_DOWN[] = {A4,A5,MISO};
int LAST_THREEWAY[] = {-1, -1, -1};

Encoder encoderA(2, 4);   // CLK, DT
Encoder encoderB(3, 5);
long lastA = 0;
long lastB = 0;

unsigned long lastCheck1 = 0;
unsigned long lastCheck2 = 0;

void setup() {
  for (int i = 0; i < TOTAL_COUNT; i++) {
    pinMode(PINS[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
  Joystick.begin();
}

void loop() {
  // TOGGLE Switch Block
  if (millis() - lastCheck1 > 10) {
    for (int i = 0; i < TOGGLE_COUNT; i++) {
      int now = digitalRead(TOGGLE[i]);
      if (now != LAST_TOGGLE[i]) {
        if (now == HIGH) {
          Joystick.setButton(2*i, 1);
          delay(20);
          Joystick.setButton(2*i, 0);
        
        }
        else {
          Joystick.setButton(2*i+1, 1);
          delay(20);
          Joystick.setButton(2*i+1, 0);
        }
        LAST_TOGGLE[i] = now;
      }
    }
    lastCheck1 = millis();
  }


  // THREEWAY Switch Block
  if (millis() - lastCheck2 > 10) {
    for (int i = 0; i < THREEWAY_COUNT; i++) {
      int now;
      if (digitalRead(THREEWAY_UP[i]) == LOW)           now = 0;
      else if (digitalRead(THREEWAY_DOWN[i]) == LOW)    now = 2;
      else                                              now = 1;

      if (now != LAST_THREEWAY[i]) {
        Joystick.setButton(16+i*3+now, 1);
        delay(20);
        Joystick.setButton(16+i*3+now, 0);

        LAST_THREEWAY[i] = now;
      }
    }
    lastCheck2 = millis();
  }

  // ENCODER Block
  long nowA = encoderA.read() / 4;
  if (nowA > lastA) {
    Joystick.setButton(25, 1);
    delay(20);
    Joystick.setButton(25, 0);
  }
  if (nowA < lastA) {
    Joystick.setButton(26, 1);
    delay(20);
    Joystick.setButton(26, 0);
  }
  lastA = nowA;

  long nowB = encoderB.read() / 4;
  if (nowB > lastB) {
    Joystick.setButton(27, 1);
    delay(20);
    Joystick.setButton(27, 0);
  }
  if (nowB < lastB) {
    Joystick.setButton(28, 1);
    delay(20);
    Joystick.setButton(28, 0);
  }
  lastB = nowB;
}