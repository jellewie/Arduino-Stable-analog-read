/*
  Program written by JelleWho https://github.com/jellewie
*/
//#define StableAnalog_AverageAmount 16                         //On how much points to take the average from (default=16)
//#define StableAnalog_AnalogResolution 8                       //Howmany bits an analog read is (default=8 same as default Arduino boards)

#include "StableAnalog/StableAnalog.h"

StableAnalog PotMeterA = StableAnalog(1);                       //Declare that we want to stabilize this input
StableAnalog PotMeterB = StableAnalog(15);                      //Declare some variable (in this case PotMeterB) to be at some pin (in this case 15)

void setup() {
  Serial.begin(115200);
  analogReadResolution(StableAnalog_AnalogResolution);          //Set StableAnalog_AnalogResolution
}

void loop() {

  POT A = PotMeterA.ReadStable(2, 3);
  //Values are as definition ("PotMinChange, PotStick, SkipFirst, Mode") as described in 'StableAnalog/StableAnalog.cpp' in '*::ReadStable(*){*}' 
  //  most have default values, for example you dont need to declare Mode when you don't use it
  //SkipFirst    Howmany measurements to block on start, so we can read stably, note this only does skip the first x after the first run. never again after that
  //PotMinChange Howmuch the pot_value needs to change before we process it
  //PotStick     If this close to HIGH(max) or LOW(min) stick to it
  //SkipFirst    Skip the first x of measurements, this is so we have proper averages, else if will climb up from 0
  //Mode         0=analogRead(default)  1=touchRead
  
  if (A.Changed) {                                              //If the value has changed (0=FALSE=not changed, and 1>=TRUE=amount of changed)
    Serial.println("Analog read A changed to " + String(A.Value) + " which is a change of " + String(A.Changed));
  }
  
  POT B = PotMeterA.ReadStable(2, 3, 0);
  if (B.Changed) {                                              //If the value has changed (0=FALSE=not changed, and 1>=TRUE=amount of changed)
    Serial.println("Analog read B changed to " + String(B.Value) + " which is a change of " + String(B.Changed));
  }

  delay(50);
}
