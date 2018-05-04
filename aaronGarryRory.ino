
/*************************************************
*** The Motion Following Motorized Camera Base ***
***               by Lindsay Fox               ***
*************************************************/

// Servor motor

#include <Stepper.h>
#define STEPS 200
Stepper myStepper = Stepper(STEPS, 4,5,6,7);

// LED status lights
int LEDpin[] = {2,3,10,11}; // LED pin numbers
int currentLEDpin = 2; // the current LED pin; begin with the first in the sequence above

int currentPIRposition = 0; // set current angle of servo

// PIR sensors
int PIRpin[] = {8,9,12,13}; // PIR pin numbers
int currentPIRpin = 8; // the current PIR pin; begin with the first in the sequence above
int PIRprevState[] = {1,1,1,1}; // the previous state of the PIR (0 = LOW, 1 = HIGH)
int PIRposition[] = {50,100,150,200}; // assign angles for servo motor (0-157 distributed equally between 5 PIR sensors)
boolean PIRstatus; // Set status of PIR sensor as either true or false



///// SETUP //////////////////////////////////////
void setup()  {
  
  Serial.begin(9600);
  myStepper.setSpeed(30);
  
  for (int p = 0; p < 4; p++)  { // set all PIR sensors as INPUTS
  pinMode(PIRpin[p], INPUT);
    } // end 'p' for

      for (int l = 0; l < 4; l++)  { // set all LEDs as OUTPUTS
  pinMode(LEDpin[l], OUTPUT);
    } // end 'l' for
      
  /////// CALIBRATE PIR SENSORS ///////
  Serial.print("Calibrating PIR Sensors ");
    for(int c = 0; c < 15; c++){ // calibrate PIR sensors for 15 seconds (change from 10-60 sec depending on your sensors)
      Serial.print(".");
      delay(1000); // wait 1 second
      } // end calibration for
    Serial.println("PIR Sensors Ready");
  
  //myStepper.step(100); // move the servo to the center position to begin
  
  } // end setup



///// MAIN LOOP //////////////////////////////////
void loop()  {

  for (int PIR = 0; PIR < 4; PIR++) { // start this loop for each PIR sensor
    currentPIRpin = PIRpin[PIR]; // set current PIR pin to current number in 'for' loop
    PIRstatus = digitalRead(currentPIRpin);
    
    if (PIRstatus == HIGH) { // if motion is detected on current PIR sensor
      //digitalWrite(currentLEDpin, HIGH); // turn corresponding LED on
      if(PIRprevState[PIR] == 0) { // if PIR sensor's previous state is LOW
        if (currentPIRposition != currentPIRpin && PIRprevState[PIR] == 0) { // if high PIR is different than current position PIR then move to new position
          if(currentPIRpin == PIRpin[0])
          {
            digitalWrite(LEDpin[0], HIGH);
              myStepper.step(-75);
              delay(5000);
              myStepper.step(+75);
              
              digitalWrite(LEDpin[0], LOW);
              delay(2000);
              
          }
          if(currentPIRpin == PIRpin[1])
          {
            digitalWrite(LEDpin[1], HIGH);
              myStepper.step(25);
              delay(5000);
              myStepper.step(-25);
              
              digitalWrite(LEDpin[1], LOW);
              delay(2000);
          }
          if(currentPIRpin == PIRpin[2])
          {
            digitalWrite(LEDpin[2], HIGH);
              myStepper.step(-25);
              delay(5000);
              myStepper.step(25);
              digitalWrite(LEDpin[2], LOW);
              delay(2000);
          }
          if(currentPIRpin == PIRpin[3])
          {
            digitalWrite(LEDpin[3], HIGH);
              myStepper.step(75);
              delay(5000);
              myStepper.step(-75);
              digitalWrite(LEDpin[3], LOW);
              delay(2000);
          }
          
          Serial.print("Current angle : ");
          Serial.println(PIRposition[PIR]);

          currentPIRposition = currentPIRpin; // reset current PIR position to active [PIR] pin
          PIRprevState[PIR] = 1; // set previous PIR state to HIGH
          }
        PIRprevState[PIR] = 1; // set previous PIR state to HIGH if the current position is the same as the current PIR pin
        } // end PIRprevState if  
      } // end PIRstatus if
    
    else  { //
      digitalWrite(currentLEDpin, LOW);  //the led visualizes the sensors output pin state
      PIRprevState[PIR] = 0;   // set previous PIR state to LOW
      } // end else
      
    } // end [PIR] for loop
  } // end main loop
