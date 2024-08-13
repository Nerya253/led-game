#define pinBuzzer 5

#define pinLed_G 6
#define pinLed_Y 9
#define pinLed_B 11
#define pinLed_R 10
                              
#define pinBtn_G 4
#define pinBtn_Y 2
#define pinBtn_B 3
#define pinBtn_R 12

#define NUM_OF_LEDS 4

int Leds[NUM_OF_LEDS] = {pinLed_G, pinLed_Y, pinLed_B, pinLed_R};
int Btns[NUM_OF_LEDS] = {pinBtn_G, pinBtn_Y, pinBtn_B, pinBtn_R};

#define WAITING_FOR_START 0
#define GAME_ACTIVE 1
#define GAME_SUCCESS 2
#define GAME_FAILURE 3
int state = WAITING_FOR_START;

bool ledStates[NUM_OF_LEDS];
bool buttonPressed[NUM_OF_LEDS];
bool allButtonsPressed[NUM_OF_LEDS];

void setup() {
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    pinMode(Leds[k], OUTPUT);
    pinMode(Btns[k], INPUT_PULLUP);
  }
  pinMode(pinBuzzer, OUTPUT);
  randomSeed(analogRead(A1));
}

void loop() {
  switch (state) {
    case WAITING_FOR_START:
      checkStartButton()ף
      break;

    case GAME_ACTIVE:

      break;

    case GAME_SUCCESS:

      break;

    case GAME_FAILURE:

      break;
  }
}

void checkStartButton() {
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    if (digitalRead(Btns[k]) == LOW) {

      return;
    }
  }
}

void startGame() {
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    digitalWrite(Leds[k], LOW);
    ledStates[k] = false;
    buttonPressed[k] = false;
    allButtonsPressed[k] = false;
  }

  int count = 0;
  
  while (count < 3) {
    int randomIndex = random(NUM_OF_LEDS);
    if (!ledStates[randomIndex]) {
      ledStates[randomIndex] = true;
      count++;
    }
  }

  for (int k = 0; k < NUM_OF_LEDS; k++) {
    if (ledStates[k]) {
      digitalWrite(Leds[k], HIGH);
    }
  }
  delay(1000);
}