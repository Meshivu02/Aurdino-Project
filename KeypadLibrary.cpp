#include <Keypad.h>

const byte ROW_NUM = 4; //four rows
const byte COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
  }
}


/* In summary:

The code uses the Keypad library to interface with a 4x4 keypad.
The keypad layout and connection pins are defined.
The program continuously checks for a pressed key in the loop() function.
When a key is pressed, it prints the corresponding character to the Serial Monitor.
Feel free to ask if you have specific questions or if you'd like to make any modifications!
*/
