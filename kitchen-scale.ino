#include "HX711.h"
#include <LiquidCrystal.h>

#define CLK A0
#define DOUT A1
#define calibration_factor 2153.0
HX711 scale;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int resetPin = 10;
float weight;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Initializing...");
  delay(100);
  
  pinMode(resetPin, INPUT);

  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor);
  scale.tare();                           // reset weight on scale to 0 grams

  lcd.clear();
}

void loop() {
  weight = scale.get_units();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weight:");
  lcd.setCursor(0, 1);
  lcd.print(weight);
  lcd.print("  grams");

  if(digitalRead(resetPin) == 0){
    scale.tare();     // reset weight on scale to 0 grams
  }
  scale.power_down();             // put the ADC in sleep mode
  delay(10);
  
  scale.power_up(); 
}
