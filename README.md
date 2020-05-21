# Arduino-Stable-analog-read
 A library kind of way that allows you to take averages of analog reads to have more stable values

# Arduino-Button
 A library kind of way to simply use a button with multiple triggers in Arduino, an example is included
 Multiple buttons can be used. Also due to interrupts being used, button pressed cannot be lost.
 
 Just simple get and save the value with 'CheckButton()'
 and then simple use '.StartPress' or 'StartDoublePress' to do some actions

# How to use
1. Create an instance 'StableAnalog PotMeterA   = StableAnalog(1);'
2. Get the value of the instance 'POT A = PotMeterA.ReadStable(2, 3, 16);'

The ReadStable takes these 3 values PotMinChange, PotStick, and SkipFirst
PotMinChange  Howmuch the pot_value needs to change before we process it
PotStick      If this close to HIGH or LOW stick to it
SkipFirst     Skip the first x of measurements, this is so we have proper averages, else if will climb up from 0

The average can be adjusted in the StableAnalog.h file with 'AverageAmount'