#include <Servo.h>
#include <Keypad.h>

Servo lockServo;

const int passwordLength = 4;
char correctPassword[passwordLength] = {'1', '2', '3', '4'};
char enteredPassword[passwordLength];
int passwordIndex = 0;

const byte ROW_NUM = 4;
const byte COLUMN_NUM = 4;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
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

  if (key) {
    if (key == '#') {
      checkPassword();
    } else {
      enteredPassword[passwordIndex++] = key;
      Serial.print(key);
    }
  }
}

void checkPassword() {
  if (passwordIndex == passwordLength) {
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
}

void unlockDoor() {
  lockServo.write(90); // Unlock position
  delay(2000); // Keep unlocked for 2 seconds
  lockServo.write(0); // Lock position
}

void lockDoor() {
  lockServo.write(0); // Lock position
  delay(1000); // Keep locked for 1 second
}
