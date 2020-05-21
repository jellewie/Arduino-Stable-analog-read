/*
  Program written by JelleWho
*/
#include "StableAnalog.h"

StableAnalog PotMeterA   = StableAnalog(1); //Declair some variable (in this case PotMeterA) to be at some pin (in this case 1)
StableAnalog PotMeterB   = StableAnalog(15);

void setup() {
  Serial.begin(115200);
}

void loop() {

  POT A = PotMeterA.ReadStable(2, 3, 16);
  //values are as definition ("PotMinChange, PotStick, SkipFirst")
  //PotMinChange  Howmuch the pot_value needs to change before we process it
  //PotStick      If this close to HIGH or LOW stick to it
  //SkipFirst     Skip the first x of measurements, this is so we have proper averages, else if will climb up from 0

  if (A.Changed) {    //If the value has changed (0=FALSE=not changed, and 1>=TRUE=amount of changed)
    Serial.println("Analog read A changed to " + String(A.Value) + " which is a change of " + String(A.Changed));
  }

  POT B = PotMeterA.ReadStable(2, 3, 0);
  if (B.Changed) {    //If the value has changed (0=FALSE=not changed, and 1>=TRUE=amount of changed)
    Serial.println("Analog read B changed to " + String(B.Value) + " which is a change of " + String(B.Changed));
  }

  delay(50);
}
