// Simple gamepad example that demonstraits how to read five Arduino
// digital pins and map them to the Arduino Joystick library.
//
// The digital pins 2 - 6 are grounded when they are pressed.
// Pin 2 = UP
// Pin 3 = RIGHT
// Pin 4 = DOWN
// Pin 5 = LEFT
// Pin 6 = FIRE
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2016-11-24
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  12, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Button Pins
  pinMode(A0, INPUT_PULLUP); //UP
  pinMode(A1, INPUT_PULLUP); //Down
  pinMode(A2, INPUT_PULLUP); //Left
  pinMode(A3, INPUT_PULLUP); //Right
  pinMode(3, INPUT_PULLUP); //B1
  pinMode(2, INPUT_PULLUP); //B2
  pinMode(0, INPUT_PULLUP); //B3
  pinMode(1, INPUT_PULLUP); //B4
  pinMode(4, INPUT_PULLUP); //B5
  pinMode(15, INPUT_PULLUP); //B6
  pinMode(16, INPUT_PULLUP); //B7
  pinMode(14, INPUT_PULLUP); //B8
  pinMode(8, INPUT_PULLUP); //B9
  pinMode(9, INPUT_PULLUP); //B10
  pinMode(10, INPUT_PULLUP); //B11
  pinMode(6, INPUT_PULLUP); //B12

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
  
  Serial.begin(9600);
}


// Last state of the buttons
int lastButtonState[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int currentButtonState = 0;

void loop() {
  // Read pin values
  if(abs(analogRead(A0))<50){
    Joystick.setYAxis(-1);
  }
  if(abs(analogRead(A1))<50){
    Joystick.setYAxis(1);
  }
  if(abs(analogRead(A1)>50) && abs(analogRead(A0)>50)){
    Joystick.setYAxis(0);
  }
  if(abs(analogRead(A2))<50){
    Joystick.setXAxis(-1);
  }
  if(abs(analogRead(A3))<50){
    Joystick.setXAxis(1);
  }
  if(abs(analogRead(A2)>50) && abs(analogRead(A3)>50)){
    Joystick.setXAxis(0);
  }
  
  for (int index = 0; index < 16; index++)
  {
    switch (index) {
      case 0:
        currentButtonState = !digitalRead(A0);
      break;
      case 1:
        currentButtonState = !digitalRead(A1);
      break;
      case 2:
        currentButtonState = !digitalRead(A2);
      break;
      case 3:
        currentButtonState = !digitalRead(A3);
      break;
      case 4:
        currentButtonState = !digitalRead(3);
      break;
      case 5:
        currentButtonState = !digitalRead(2);
      break;
      case 6:
        currentButtonState = !digitalRead(0);
      break;
      case 7:
        currentButtonState = !digitalRead(1);
      break;
      case 8:
        currentButtonState = !digitalRead(4);
      break;
      case 9:
        currentButtonState = !digitalRead(15);
      break;   
      case 10:
        currentButtonState = !digitalRead(16);
      break;
      case 11:
        currentButtonState = !digitalRead(14);
      break;
      case 12:
        currentButtonState = !digitalRead(8);
      break;
      case 13:
        currentButtonState = !digitalRead(9);
      break;
      case 14:
        currentButtonState = !digitalRead(10);
      break;    
      case 15:
        currentButtonState = !digitalRead(6);
      break;
    }
    if (currentButtonState != lastButtonState[index])
    {
      switch (index) {
        case 0: // UP
          if (currentButtonState == 1) {
            Joystick.setYAxis(-1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 1: // RIGHT
          if (currentButtonState == 1) {
            Joystick.setXAxis(1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        case 2: // DOWN
          if (currentButtonState == 1) {
            Joystick.setYAxis(1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 3: // LEFT
          if (currentButtonState == 1) {
            Joystick.setXAxis(-1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        case 4: // B1
          Joystick.setButton(0, currentButtonState);
          break;
        case 5: // B2
          Joystick.setButton(1, currentButtonState);
          break;
        case 6: // B3
          Joystick.setButton(2, currentButtonState);
          break;
        case 7: // B4
          Joystick.setButton(3, currentButtonState);
          break;
        case 8: // B5
          Joystick.setButton(4, currentButtonState);
          break;
        case 9: // B6
          Joystick.setButton(5, currentButtonState);
          break;
        case 10: // B7
          Joystick.setButton(6, currentButtonState);
          break;
        case 11: // B8
          Joystick.setButton(7, currentButtonState);
          break;
        case 12: // B9
          Joystick.setButton(8, currentButtonState);
          break;
        case 13: // B10
          Joystick.setButton(9, currentButtonState);
          break;
        case 14: // B11
          Joystick.setButton(10, currentButtonState);
          break;
        case 15: // B12
          Joystick.setButton(11, currentButtonState);
          break;                       
      }
      lastButtonState[index] = currentButtonState;
    }
  }
  delay(5);
}
