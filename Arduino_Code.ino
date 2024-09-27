#include <LiquidCrystal.h>  // Initialize the library for LCD
#include <Servo.h>          // Include the servo library

// Pin Definitions
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Servo myservo1;
int ir_s1 = 2;  // IR sensor at entry gate
int ir_s2 = 4;  // IR sensor at exit gate
int servoPin = 3;  // Servo control pin

// Parking Lot Variables
int Total = 5;  // Total number of parking spaces
int Space;      // Available parking spaces

// Flags
int flag1 = 0;
int flag2 = 0;

void setup() {
  // Pin Modes
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
  
  // Initialize Servo
  myservo1.attach(servoPin);
  myservo1.write(100);  // Close gate initially
  
  // Initialize LCD
  lcd.begin(16, 2);  
  lcd.setCursor(0, 0);
  lcd.print("  Car  Parking  ");
  lcd.setCursor(0, 1);
  lcd.print("     System     ");
  delay(2000);
  lcd.clear();  
  
  // Initialize space count
  Space = Total;
}

void loop() { 
  // Check for vehicle entry
  if (digitalRead(ir_s1) == LOW && flag1 == 0) {
    if (Space > 0) {
      flag1 = 1;
      myservo1.write(0);  // Open gate
      Space--;  // Decrease available spaces
    } else {
      // No available spaces
      lcd.setCursor(0, 0);
      lcd.print(" Sorry, No Space ");  
      lcd.setCursor(0, 1);
      lcd.print("  Available  "); 
      delay(1000);
      lcd.clear();
    }
  }
  
  // Check for vehicle exit
  if (digitalRead(ir_s2) == LOW && flag2 == 0) {
    flag2 = 1;
    myservo1.write(0);  // Open gate
    Space++;  // Increase available spaces
  }
  
  // If both entry and exit events occurred, reset flags and close gate
  if (flag1 == 1 || flag2 == 1) {
    delay(1000);  // Short delay before closing the gate
    myservo1.write(100);  // Close gate
    flag1 = 0;
    flag2 = 0;
  }
  
  // Update LCD with space status
  lcd.setCursor(0, 0);
  lcd.print("Total Space: ");
  lcd.print(Total);
  
  lcd.setCursor(0, 1);
  lcd.print("Available: ");
  lcd.print(Space);
}


