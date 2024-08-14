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

bool firstButtonPressed = false;

unsigned long pressStartTime = 0;

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
      checkStartButton();
      break;

    case GAME_ACTIVE:
      checkButtons();
      break;

    case GAME_SUCCESS:
      Success();
      break;

    case GAME_FAILURE:
      Failure();
      break;
  }
}

void checkStartButton() {
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    if (digitalRead(Btns[k]) == LOW) {
      startGame();
      return;
    }
  }
}

void checkButtons() {
  bool allButtonsCorrect = true;

  for (int k = 0; k < NUM_OF_LEDS; k++) {
    bool currentPressed = digitalRead(Btns[k]) == LOW;

    if (currentPressed && !buttonPressed[k]) {
      buttonPressed[k] = true;
      allButtonsPressed[k] = true; 

      if (!ledStates[k]) {
        state = GAME_FAILURE;
        return;
      }
      if (!firstButtonPressed) {
        pressStartTime = millis();  
        firstButtonPressed = true;
      }
    } else if (!currentPressed && buttonPressed[k]) {
      buttonPressed[k] = false;
    }
  }

  if (firstButtonPressed) {
    unsigned long duration = millis() - pressStartTime;

    if (duration <= 1000) {
      for (int k = 0; k < NUM_OF_LEDS; k++) {
        if (ledStates[k] && !allButtonsPressed[k]) {
          allButtonsCorrect = false;
          break;
        }
      }

      if (allButtonsCorrect) {
        state = GAME_SUCCESS;
      }
    } else {
      state = GAME_FAILURE;
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

  for (int k = 0; k < NUM_OF_LEDS; k++) {
    if (ledStates[k]) {
      digitalWrite(Leds[k], LOW);
    }
  }

  delay(500); 

  tone(pinBuzzer, 1000, 200); 

  firstButtonPressed = false;

  state = GAME_ACTIVE;
}

void Success() {
  digitalWrite(pinLed_G, HIGH);
  tone(pinBuzzer, 2000, 500); 
  delay(1000);
  digitalWrite(pinLed_G, LOW);
  state = WAITING_FOR_START;
  resetGame();
}

void Failure() {
  digitalWrite(pinLed_R, HIGH);
  tone(pinBuzzer, 500, 500); 
  delay(1000);
  digitalWrite(pinLed_R, LOW);
  state = WAITING_FOR_START;
  resetGame();
}

void resetGame() {
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    digitalWrite(Leds[k], LOW);
  }
  delay(500); 
}









