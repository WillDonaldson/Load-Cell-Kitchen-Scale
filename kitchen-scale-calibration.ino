#include "HX711.h"
HX711 scale;

#define CLK  A0
#define DOUT  A1

int calibration_factor = 1000; 

void setup() {
  Serial.begin(9600);
  Serial.println("Kitchen scale calibration");
  Serial.println("Remove all weight from scale");

  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  
  Serial.println("Place an object of known weight on the load cell");
  Serial.println("Adjust calibration factor using the following keys");
  Serial.println("'a' or 'z' to increase or decrease by 100, respectively");
  Serial.println("'s' or 'x' to increase or decrease by 10, respectively");
  Serial.println("'d' or 'c' to increase or decrease by 1, respectively");
}

void loop() {
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 2);
  Serial.print(" grams"); 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  
  if(Serial.available()){
    char input = Serial.read();
    if(input == 'a'){ calibration_factor += 100; }
    else if(input == 'z'){  calibration_factor -= 100; }
    else if(input == 's'){  calibration_factor += 10; }
    else if(input == 'x'){  calibration_factor -= 10; }
    else if(input == 'd'){  calibration_factor += 1; }
    else if(input == 'c'){  calibration_factor -= 1; }
  }
}

