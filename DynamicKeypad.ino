#include <Servo.h>
#include <Keypad.h>

Servo lockServo;

const int passwordLength = 4;
char correctPassword[passwordLength] = {'A', 'B', 'C', 'D'};  // Updated to use only alphabet keys
char enteredPassword[passwordLength];
int passwordIndex = 0;

const byte ROW_NUM = 4;
const byte COLUMN_NUM = 4;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L'},
  {'M', 'N', 'O', 'P'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6};
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup() {
  lockServo.attach(10);
  lockServo.write(0); // Initial position, locked
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();

  if (key && isAlphaNumeric(key)) {
    enteredPassword[passwordIndex++] = key;
    Serial.print(key);
  }

  if (passwordIndex == passwordLength) {
    checkPassword();
  }
}

void checkPassword() {
  bool correct = true;
  for (int i = 0; i < passwordLength; i++) {
    if (enteredPassword[i] != correctPassword[i]) {
      correct = false;
      break;
    }
  }

  if (correct) {
    Serial.println("\nPassword correct - Unlocking");
    unlockDoor();
  } else {
    Serial.println("\nIncorrect password - Locking");
    lockDoor();
  }

  passwordIndex = 0;
  memset(enteredPassword, 0, sizeof(enteredPassword));
}

void unlockDoor() {
  lockServo.write(90);
  delay(2000);
  lockServo.write(0);
}

void lockDoor() {
  lockServo.write(0);
  delay(1000);
}
/*
In this version, the keys array now only includes alphabet keys. 
  The check inside the loop() function ensures that only alphanumeric keys are considered for the entered password.
  The isAlphaNumeric() function is used to filter out non-alphanumeric keys.

  */
