#include <DIYables_Keypad.h>  // DIYables_Keypad library
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>


hd44780_I2Cexp lcd;

#define SLAVE_ADDR 16
#define ANSWERSIZE 12

const int ROW_NUM = 4; // Four rows
const int COLUMN_NUM = 3; // Three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6};    // Connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3};  // Connect to the column pinouts of the keypad

int ledPin = 2;
int computerPin = 10;


DIYables_Keypad keypad = DIYables_Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

String random_passcode;
String input_password;

void scanI2CDevices() {
  Serial.println("Scanning for I2C devices...");
  byte count = 0;
  
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C device found at address 0x");
      Serial.println(address, HEX);
      count++;
    }
  }
  
  if (count == 0) {
    Serial.println("No I2C devices found.");
  } else {
    Serial.print("Total I2C devices found: ");
    Serial.println(count);
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(computerPin, OUTPUT);
  analogWrite(computerPin, 255);
  Wire.begin();
  Wire.setClock(50000);

  Serial.begin(9600);
  
  scanI2CDevices();

  lcd.begin(16, 2); // Initialize a 16x2 LCD
  lcd.backlight();    // Turn on the LCD backlight
  lcd.print("Input Passcode:");
  
  input_password.reserve(ANSWERSIZE); // Reserve space for 12 characters
  random_passcode.reserve(ANSWERSIZE);
}

void input() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    delay(200); // Debounce delay

    if (key == '*') {
      input_password = ""; // Clear input password
      lcd.clear();
      lcd.print("Input cleared");
      delay(2000);
      lcd.clear();
      lcd.print("Input Passcode:");
    } 
    else if (key == '#') {
      lcd.clear();
      if (random_passcode == input_password) {
        lcd.print("Correct Password!");
        Serial.println("Password is correct");
        input_password = "";
        // DO YOUR WORK HERE
        analogWrite(computerPin, 0);
        delay(1000);
        analogWrite(computerPin, 255);
        digitalWrite(ledPin, HIGH);
        delay(2000);
        digitalWrite(ledPin, LOW);
      } 
      else {
        lcd.print("Wrong Password!");
        Serial.println("Password is incorrect, try again");
      }
      delay(2000);  // Display result for 2 seconds
      lcd.clear();
      lcd.print("Input Passcode:");
      input_password = "";
    } 
    else {
      if (input_password.length() < ANSWERSIZE) {  // Prevent overflow
        input_password += key; // Append new character to input password string
        lcd.setCursor(0, 1);   // Move to the second line
        lcd.print(input_password);
        Serial.println(input_password);
      } else {
        Serial.println("Input limit reached");
        lcd.clear();
        lcd.print("Too Many #'s");
        input_password = "";
        delay(2000);
        lcd.clear();
        lcd.print("Input Passcode:");
      }
    }
  }
}

void resetI2C() {
  Wire.end();         // End current I2C session
  delay(50);          // Short delay
  Wire.begin();       // Reinitialize I2C
}

void loop() {
  input();
  
  // Call i2c periodically (every 10 seconds)
  static unsigned long lastCall = 0;
  if (millis() - lastCall >= 10000) {
    i2c();
    resetI2C();
    lastCall = millis();
  }
}

void i2c() {
  Serial.println("Starting I2C write to slave...");
  
  Wire.beginTransmission(SLAVE_ADDR);
  byte status = Wire.endTransmission();  // Send data and check the status

  if (status == 0) {
    Serial.println("I2C write successful");
  } else {
    Serial.print("I2C write error, status: ");
    Serial.println(status);  // Print error status code
  }
  
  delay(50);  // Allow some time before requesting data
  
  Wire.requestFrom(SLAVE_ADDR, ANSWERSIZE);
  // Clear previous passcode and read new response
  String response = "";
  while (Wire.available()) {
    char b = Wire.read();
    response += b;
  }
  random_passcode = response;  // Update the random passcode
  Serial.println("New passcode: " + random_passcode);
}
