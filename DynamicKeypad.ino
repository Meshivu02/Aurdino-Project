#include <Keypad.h>

const byte ROW_NUM = 4;
const byte COLUMN_NUM = 4;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6};    // Connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup() {
  Serial.begin(9600); // Initialize the serial communication

  // Setup the keypad with specified pin configurations
  keypad.setDebounceTime(10);
}

void loop() {
  char key = keypad.getKey(); // Read the key pressed on the keypad

  if (key) {
    Serial.println(key); // Print the pressed key to the Serial Monitor
  }
}
