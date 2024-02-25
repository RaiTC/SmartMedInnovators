#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

unsigned long displayStartTime = 0;
unsigned long interactionStartTime = 0;
const int colorR = 0;
const int colorG = 0;
const int colorB = 0;
const unsigned long loopInterval = 5000; // 5 seconds

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD
  Serial.begin(9600); // Initialize serial communication
  lcd.setRGB(colorR, colorG, colorB);

  // Seed the random number generator with an analog reading
  randomSeed(analogRead(0));
}

void loop() {

  // Clear the display
  lcd.clear();

  // Generate a new random value for loop
  float userInput = random(2, 4000) / 1000.0;  // Random value between 0.002 and 4; Healthy -> Non-Healthy

  // Display Patients Blood Index
  lcd.setRGB(255, 255, 255);  // Set backlight color to white (General)
  lcd.setCursor(0, 0);  // Move to the first line
  lcd.print("BLD Index:");
  lcd.print(userInput, 3);  // Display userInput with 3 decimal places

  // Move to the second line
  lcd.setCursor(0, 1);

  // if-else statement tree >>>

  // Mild TBI
  if (userInput >= 0.263 && userInput <= 1.830) {
    lcd.setRGB(255, 255, 255);  // Set backlight color to white
    lcd.print("Mild Risk TBI");
  } 
  // Mod TBI
  else if (userInput >= 1.831 && userInput <= 3.595) {
    lcd.setRGB(255, 255, 0);  // Set backlight color to yellow
    lcd.print("Mod Risk TBI");
  } 
  // Severe TBI
  else if (userInput >= 3.596) {
    lcd.setRGB(255, 0, 0);  // Set backlight color to red
    lcd.print("Severe Risk TBI");
  }
  // No diseases found
  else  if (userInput <= 0.262) {
    lcd.setRGB(0, 255, 0);  // Set backlight color to green
    lcd.print("No Risk");
  }
  //Error Handling
  else {
    lcd.setRGB(128, 0, 128); // Set backlight color to purple
    lcd.print("Invalid Data");
  }

  // Delay for xx seconds
  delay(loopInterval);
}
