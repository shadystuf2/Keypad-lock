// LATEST VERSION
// have to use digital input pin!
// Im so sorry to whoever has to read this, but yes the if statements are necessary...
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

#define RLED_PIN 25
#define YLED_PIN 26
#define GLED_PIN 27

// variables
String inputPassword;
String password;
int counter = 0;
int xc = 45;
bool isPassword = false;
bool menu = false;

// Objects
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED FAILED");
    while(true);
  }
   
  pinMode(RLED_PIN, OUTPUT);
  pinMode(YLED_PIN, OUTPUT);
  pinMode(GLED_PIN, OUTPUT);

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
//menuuu
  if (menu) {
              if (key == '1') {
                isPassword = false;
                password = "";
                counter = 0;
                inputPassword = "";
                xc = 45;
                
                display.clearDisplay();
                display.setTextSize(1);
                display.setCursor(15, 27);
                display.println("Resetting password");
                display.display();
                delay(2000);
                
                display.clearDisplay();
                display.setTextSize(1);
                display.setCursor(0, 0);
                display.println("Enter new password");
                display.print("press # to confirm):");
                display.display();
                menu = false;

              }
              if (key == '2') {
                display.clearDisplay();
                display.display();
                menu = false;
              }
              return;
          
          }
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
      // verify password
      if (key == '#' && password.length() == 4) {
        
        xc = 45; 
        display.clearDisplay();
        display.setTextSize(3);
        display.setCursor(2, 20);
        display.println("SUCCESS");
        display.display();
        delay(2000);

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
        display.setCursor(xc, 50);
        display.print(key);
        display.display();
        inputPassword += key;
        xc += 7;
      }

      // access granted/denied
      if (key == '#'){
        if (inputPassword == password) {
          menu = true;

          display.clearDisplay();
          display.setTextSize(3);
          display.setCursor(5, 10);
          display.println("ACCESS");
          display.println("GRANTED");
          display.display();
          delay(2000);

          display.clearDisplay();
          display.setTextSize(1);
          display.setCursor(30, 0);
          display.println("MENU");
          display.println("1. Reset password");
          display.println("2. Quit");
          display.display();

          

        } else {
          display.clearDisplay();
          counter++;
          xc = 45;

          if (counter == 1) {
            digitalWrite(GLED_PIN, HIGH);
            digitalWrite(RLED_PIN, LOW);
            digitalWrite(YLED_PIN, LOW);
          }

          if (counter == 2) {
            digitalWrite(YLED_PIN, HIGH);
            digitalWrite(GLED_PIN, LOW);
            digitalWrite(RLED_PIN, LOW);

          }
          
          if (counter == 3) {
            digitalWrite(RLED_PIN, HIGH);
            digitalWrite(YLED_PIN, LOW);
            digitalWrite(GLED_PIN, LOW);
          }

          /// counts attempts type xi
          if (counter == 3) {
            display.setTextSize(3);
            display.setCursor(8, 10);
            display.println("ACCESS");
            display.setCursor(8, 35);
            display.println("DENIED");
            display.display();
            delay(2000);

            display.clearDisplay();
            display.setTextSize(1);
            display.setCursor(15, 27);
            display.println("jk, for 10s only");
            display.display();
            delay(10000);
            inputPassword = "";
            counter = 0;

            display.clearDisplay();
            display.setTextSize(1);
            display.setCursor(0, 0);
            display.print("Enter your password: ");
            display.print("(press # to send it) ");
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
