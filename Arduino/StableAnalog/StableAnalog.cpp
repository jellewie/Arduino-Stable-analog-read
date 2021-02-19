/* Written by JelleWho https://github.com/jellewie
   https://github.com/jellewie/Arduino-Stable-analog-read
*/
StableAnalog::StableAnalog(byte _pin) {                 //Must be <class name> this is kinda the 'root' function
  this->pin = _pin;                                     //Make a pointer
  pinMode(pin, INPUT);                                  //Set the pin as input
}
byte StableAnalog::Read(byte mode) {
  PointTotal -= Point[Counter];                         //Remove the old value from the total value
  if (mode == 0) {
    Point[Counter] = (analogRead(pin) / StableAnalog_AnalogScaler);
  } else if (mode == 1) {
    Point[Counter] = (touchRead(pin) / StableAnalog_AnalogScaler);
  }
  PointTotal += Point[Counter];                         //Add the new value to the total value
  Counter++;
  if (Counter >= StableAnalog_AverageAmount)
    Counter = 0;
  byte ReturnValue = PointTotal / StableAnalog_AverageAmount;
  return ReturnValue;
}
POT StableAnalog::ReadStable(byte MinChange, byte Stick, byte SkipFirst, byte mode) {
  //SkipFirst    Howmany measurements to block on start, so we can read stably, note this only does skip the first x after the first run. never again after that
  //PotMinChange Howmuch the pot_value needs to change before we process it
  //PotStick     If this close to HIGH or LOW stick to it
  //SkipFirst    Skip the first x of measurements, this is so we have proper averages, else if will climb up from 0
  //Mode         0=analogRead(default)  1=touchRead

  byte New = Read();
  POT RV;
  if (InitCount < SkipFirst) {                          //If we have not yet a valid average (to few points)
    InitCount += 1;
    Old = New;                                          //  Update value
    return RV;
  } else if (InitCount == SkipFirst) {                  //If we are done, and the first update needs to be send
    InitCount += 1;
    Old = New - 100;                                    //  Throw the value off, so we force an update
  }
  if (abs(New - Old) > MinChange) {                     //If we have a big enough change
    RV.Changed = abs(New - Old);
    Old = New;                                          //  Update value
  } else
    RV.Changed = 0;
  if (Old < Stick)                                      //If we are close to min/0
    Old = 0;                                            //  Stick to zero
  if (Old > 255 - Stick)                                //If we are close to max/255
    Old = 255;                                          //  Stick to max
  RV.Value = Old;
  return RV;
}