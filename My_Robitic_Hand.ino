#include <Servo.h>

// Global Control
const int delayIteration = 15;

// Stay Button
const int stayButtonPin = 7;
int buttonState = 0;

// Shoulder
Servo shoulderServo;
int shoulderInput = A0;
int shoulderValue = 0;
int shoulderMovementSmoother = 2;
int shoulderMin = 0;
int shoulderMax = 180;

void setup() {
  Serial.begin(9600);
  pinMode(stayButtonPin, INPUT);
  shoulderServo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  buttonState = digitalRead(stayButtonPin);
  if(buttonState == LOW){
      shoulderValue = movementCalculation(shoulderValue, analogRead(shoulderInput), shoulderMin, shoulderMax, shoulderMovementSmoother);  
      shoulderServo.write(shoulderValue);
  }

  delay(delayIteration);                          
}

int movementCalculation(int currentValue, int inputValue, int minimum, int maximum, int movementPrecision){
  int targetValue = map(inputValue, -100, 1080, minimum, maximum);
  int valueDifferent = currentValue - targetValue;
  
  if(valueDifferent > -movementPrecision && valueDifferent < movementPrecision)
    return targetValue;
  else if(currentValue < targetValue)
      return currentValue += movementPrecision;
  else if(currentValue > targetValue)
      return currentValue -= movementPrecision;
}

