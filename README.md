# CascadeEffect
All the code and design files FTC 7890 Space Lions created for the 2014-15 FTC season.  Some highlights include our sonar mapping software and extensive use of 3D printed parts.  Enjoy!

# Helper functions library
Here is an overview of the methods and tasks contained in our helperFunctions.h library.
Encoders
 - void resetEncoder (tMotor anyMotor)
 - void moveEncoderSteps(tMotor anyMotor, int encoderSteps, int power)
 - void resetDriveEncoders ()
Driving
 - void motorSet (tMotor anyMotor, int power)
 - void powerSide (int side, int power)
 - void drive (int leftPow, int rightPow)
 - void straightDrive (int power)
 - void halt ()
 - void pivot (int direction, int power, float deg)
 - void swingTurn (int direction, int power, float deg)
 - void driveDistance (int power,int inches)
Lifter
 - task lifterToCenter ()
 - task lifterDownFromCenter()
 - void lifterUpThirty()
 - void lifterDownThirty()
Sonar
 - int readSonar(int numReads)
 - int sonarTurretPosition(int servoPosition, int numReads)
 - int findOrientation()
 - void driveUntilCloserThan (int power, int targetDistance)
 - void driveUntilFartherThan (int power, int targetDistance)
Servos
 - void grabbersDown()
 - void grabbersUp()
 - void grabbersMidway()
 - void bridgeOpen()
 - void bridgeClosed()

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">Space Lions Cascade Effect Files</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="http://basementlions.org/ftc" property="cc:attributionName" rel="cc:attributionURL">FTC 7890 Space Lions</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.
