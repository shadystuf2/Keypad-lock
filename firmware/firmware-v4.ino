#include <Keypad.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// variables
String inputPassword;
String password;
int counter = 0;
int xc = 0;
int xc2 = 45;
bool isPassword = false;

// Objects
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED FAILED");
    while(true); // just in case it doesnt print
  }
   
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Will the lock get;");
  display.println("cracked, or will you?");
  display.println("Choose wisely...");
  display.println();
  display.println("Enter new password");
  display.print("press # to confirm):");

  display.display();
}

void loop() {
  char key = keypad.getKey();
  //Create password
  if (!isPassword) {

    if (key != NO_KEY) {
      if (password.length() < 4 && key != '#' && key != '*') {
        display.setTextSize(1);
        display.setCursor(xc, 50);
        display.print(key);
        display.display();
        password += key;
        xc += 7;
      }

      if (key == '#' && password.length() == 4) {
        
        display.clearDisplay();
        display.setTextSize(3);
        display.setCursor(2, 20);
        display.println("SUCCESS");
        display.display();
        delay(3000);

        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(0, 0);
        display.print("Enter your password: ");
        display.print("(press # to send it) ");
        display.display();
        isPassword = true;
      }
    }
  } 

  // input password
  else {
    if (key != NO_KEY) {
      if (inputPassword.length() < 4 && key != '#' && key != '*'){
        display.setCursor(xc2, 50);
        display.print(key);
        display.display();
        inputPassword += key;
        xc2 += 7;
      }

      // access granted/denied
      if (key == '#'){
        if (inputPassword == password) {
          display.clearDisplay();
          display.setTextSize(3);
          display.setCursor(5, 10);
          display.println("ACCESS");
          display.println("GRANTED");
          display.display();
        } else {
          display.clearDisplay();
          counter++;
          xc2 = 45;

          /// counts attempts type xi
          if (counter == 3) {
            display.setTextSize(3);
            display.setCursor(8, 10);
            display.println("ACCESS");
            display.setCursor(8, 35);
            display.println("DENIED");
            display.display();
          } else {
            inputPassword = "";

            display.setCursor(20, 30);
            display.setTextSize(1);
            display.setCursor(15, 0);
            display.println("Incorrect password ");
            display.setCursor(15, 10);
            display.print(3 - counter);
            display.print(" attempt(s) left");
            display.setCursor(40, 20);
            display.print("Try again: ");
            display.display();
          }  
          }
      }
    }
}
}
