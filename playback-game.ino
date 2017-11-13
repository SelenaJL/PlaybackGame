/*
  Author: Selena Latchman
  Purpose: playback game to learn LED output, pushbutton input, and piezo speakers
  Date: November 11, 2017
*/

// pin hooked up to peizo:
const int piezoPin = 8;

// pins hooked up to leds:
const int redLedPin = 9;
const int yellowLedPin = 10;
const int greenLedPin = 11;

// pins hooked up to buttons:
const int redButtonPin = 5;
const int yellowButtonPin = 6;
const int greenButtonPin = 7;

// button states:
int redButtonState = 0;
int redButtonLastState = 0;
int yellowButtonState = 0;
int yellowButtonLastState = 0;
int greenButtonState = 0;
int greenButtonLastState = 0;

// variables to debounce buttons:
// using unsigned longs since the time (in milliseconds) will get too big for an integer
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 200;  // the debounce time; increase if the output flickers

int pattern[5] = {0, 0, 0, 0, 0};  // array to hold random numbers
int playback[5] = {0, 0, 0, 0, 0};  // array to hold playback attempt

// random number key:
const int red = 0;
const int yellow = 1;
const int green = 2;


void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to my playback game!");
  randomSeed(analogRead(0));

  // set leds and peizo as output
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);

  // set buttons as input
  pinMode(redButtonPin, INPUT);
  pinMode(yellowButtonPin, INPUT);
  pinMode(greenButtonPin, INPUT);
}


void loop() {
  // generate random pattern
  for (int pos = 0; pos < 5; pos++) {
    int randNum = random(3);
    pattern[pos] = randNum;
    Serial.print(randNum);
  }
  Serial.println();

  // play pattern on leds
  for (int pos = 0; pos < 5; pos++) {
    delay(250);
    if (pattern[pos] == red) {
      digitalWrite(redLedPin, HIGH);
      delay(1000);
      digitalWrite(redLedPin, LOW);
    } else if (pattern[pos] == yellow) {
      digitalWrite(yellowLedPin, HIGH);
      delay(1000);
      digitalWrite(yellowLedPin, LOW);
    } else if (pattern[pos] == green) {
      digitalWrite(greenLedPin, HIGH);
      delay(1000);
      digitalWrite(greenLedPin, LOW);
    }
  }

  // listen for button playback
  int count = 0;
  while (count < 5) {
    // read button states
    int redButtonState = digitalRead(redButtonPin);
    int yellowButtonState = digitalRead(yellowButtonPin);
    int greenButtonState = digitalRead(greenButtonPin);

    if ((millis() - lastDebounceTime) > debounceDelay) {
      // if the new button state is HIGH, add to playback array
      if (redButtonState == HIGH) {
        playback[count] = red;
        Serial.println("set red");
        count++;
        lastDebounceTime = millis();
      }
      if (yellowButtonState == HIGH) {
        playback[count] = yellow;
        Serial.println("set yellow");
        count++;
        lastDebounceTime = millis();
      }
      if (greenButtonState == HIGH) {
        playback[count] = green;
        Serial.println("set green");
        count++;
        lastDebounceTime = millis();
      }
    }
  }

  // check button playback
  bool success = true;
  for (int pos = 0; pos < 5; pos++) {
    if (playback[pos] != pattern[pos]) {
      success = false;
      break;
    }
  }

  // play sound based on correct/incorrect input
  // tone is independent to delays
  delay(500);
  if (success) {
    Serial.println("Right :)");
    tone(piezoPin, 100, 500);
  } else {
    Serial.println("Wrong :(");
    tone(piezoPin, 1000, 500);
  }
  delay(3000);
}
