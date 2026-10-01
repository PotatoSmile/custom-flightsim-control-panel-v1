#include <Joystick.h>
#include <Encoder.h>
Joystick_ Joystick;

const int TOTAL_COUNT = 2;
const int PINS[] = {6,8};

const int TOGGLE_COUNT = 0; // TEMP
const int TOGGLE[] = {6,8};
int LAST_TOGGLE[] = {HIGH, HIGH};

const int THREEWAY_COUNT = 0; // TEMP
const int THREEWAY_UP[] = {2,3};
const int THREEWAY_DOWN[] = {4,5};
int LAST_THREEWAY[] = {-1, -1};

const int ENCODER_COUNT = 2;
const int ENCODER_CLK[] = {2,3};
const int ENCODER_DT[] = {4,5};
int LAST_CLK[] = {0, 0};

unsigned long lastCheck1 = 0;
unsigned long lastCheck2 = 0;

void setup() {
  for (int i = 0; i < TOTAL_COUNT; i++) {
    pinMode(PINS[i], INPUT_PULLUP);
  }
  for (int i = 0; i < ENCODER_COUNT; i++) {
    pinMode(ENCODER_CLK[i], INPUT);
    pinMode(ENCODER_DT[i], INPUT);
  }
  for (int i = 0; i < ENCODER_COUNT; i++) {
    LAST_CLK[i] = digitalRead(ENCODER_CLK[i]);
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
          Serial.print(1);
          Serial.print(" TOGGLE: ");
          Serial.println(i);
        
        }
        else {
          Serial.print(0);
          Serial.print(" TOGGLE: ");
          Serial.println(i);
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
        Serial.print(now);
        Serial.print(" THREEWAY: ");
        Serial.println(i);

        LAST_THREEWAY[i] = now;
      }
    }
    lastCheck2 = millis();
  }

  // ENCODER Block
  for (int i = 0; i < ENCODER_COUNT; i++) {
    int CLK_NOW = digitalRead(ENCODER_CLK[i]);
    if (LAST_CLK[i] != CLK_NOW && CLK_NOW == LOW) {
      if (digitalRead(ENCODER_DT[i]) != CLK_NOW) {
        Serial.println("+");
      }
      else {
        Serial.println("-");
      }
    }
    LAST_CLK[i] = CLK_NOW;
  }
}