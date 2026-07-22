// have to use digital input pin!
// Im so sorry to whoever has to read this, but yes the if statements are necessary...
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
String password;
int counter = 0;
bool isPassword = false;

// Objects
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(115200);
  Serial.println("Will the lock get cracked, or will you? Choose wisely...");
  Serial.print("Enter new password (press # to confirm): ");
}

void loop() {
  char key = keypad.getKey();
  //Create password
  if (!isPassword) {

    if (key != NO_KEY) {
      if (password.length() < 4 && key != '#' && key != '*') {
        Serial.print(key);
        password += key;
      }

      if (key == '#' && password.length() == 4) {
        Serial.println();
        Serial.println("Password created!");
        Serial.print("Enter your password: ");
        isPassword = true;
      }
    }
  } 

  // input password
  else {
    if (key != NO_KEY) {
      if (inputPassword.length() < 4 && key != '#' && key != '*'){
        Serial.print(key);
        inputPassword += key;
      }

      // access granted/denied
      if (key == '#' && isPassword){
        if (inputPassword == password) {
          Serial.println();
          Serial.print("Access granted");
        } else {
          Serial.println();
          counter++;

          /// counts attempts type xi
          if (counter == 3) {
            Serial.print("Access denied");
          } else {
            inputPassword = "";
            Serial.println("Incorrect password. ");
            Serial.print(3 - counter);
            Serial.print(" attempts left, try again: ");
          }  
          }
      }
    }
}
}
