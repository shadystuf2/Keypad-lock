// have to use digital input pin!
#include <Keypad.h>

const uint8_t ROWS = 4;
const uint8_t COLS = 3;

// characters for each key
char keys[ROWS][COLS] = {
  { '1', '2', '3'},
  { '4', '5', '6'},
  { '7', '8', '9'},
  { '*', '0', '#'}
};

// pin setup
uint8_t colPins[COLS] = { 13, 12, 14};
uint8_t rowPins[ROWS] = { 4, 16, 17, 18};

// variables
String inputPassword;
String password = "1234";

// Objects
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(115200);
  Serial.print("Input password: ");
  
}

void loop() {
  char key = keypad.getKey();
// input password
  if (key != NO_KEY) {
    if (inputPassword.length() < 4){
      Serial.print(key);
      inputPassword += key;
    }

    // access
    if (key == '#'){
      if (inputPassword == password) {
        Serial.println();
        Serial.print("Access granted");
      } else {
        Serial.println();
        Serial.print("Access denied");
        }
    }
  }
} 
