// By: KaKei Pun
// For Non-Continous Servo Only

#include <Servo.h>

// Global Control
const int numberOfJoint = 1;
const int delayIteration = 15;


// Stay Button
const int stayButtonPin = 7;
int buttonState = 0;

// Shoulder
int shoulderInput = A0;
int shoulderOutput = 9;
int shoulderValue = 90;
int shoulderMovementSmoother = 2;
int shoulderMin = 0;
int shoulderMax = 180;

// Array
Servo servo[6];
int inputPinArray [] = {shoulderInput};
int outputPinArray [] = {shoulderOutput};
int valuesArray[] = {shoulderValue};
int movementSmoothArray [] = {shoulderMovementSmoother};
int minimumArray [] = {shoulderMin};
int maximumArray [] = {shoulderMax};

int i;
int tempValue;

void setup() {
  Serial.begin(9600);
  pinMode(stayButtonPin, INPUT);
  for(i = 0; i < numberOfJoint; i++){
      servo[i].attach(outputPinArray[i]);
      servo[i].write(valuesArray[i]);
  }
}

void loop() {
  buttonState = digitalRead(stayButtonPin);
  if(buttonState == LOW){
    
      for(i = 0; i < numberOfJoint; i++){
          valuesArray[i] = movementCalculation(
                valuesArray[i], 
                analogRead(inputPinArray[i]), 
                minimumArray[i],
                maximumArray[i],
                movementSmoothArray[i]
                );
          servo[i].write(valuesArray[i]);
      }
  }
  delay(delayIteration);                          
}

int movementCalculation(int currentValue, int inputValue, int minimum, int maximum, int movementPrecision){
  int targetValue = map(inputValue, 0, 1023, 0, 2);
  if(targetValue == 1)
      return currentValue;
  else if(targetValue == 2){
      if(currentValue + movementPrecision < maximum)
          return currentValue + movementPrecision;
  }
  else if(targetValue == 0){
      if(currentValue - movementPrecision > minimum)
          return currentValue - movementPrecision;
  }
}