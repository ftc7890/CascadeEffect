#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "prodrive.h"
#include "hitechnic-gyro.h" //Include library for gyroscope

#define GRAB_ONE_DOWN 220
#define GRAB_ONE_UP 20
#define GRAB_ONE_MID 180


#define GRAB_TWO_DOWN 220 // FIGURE THESE OUT
#define GRAB_TWO_UP 20
#define GRAB_TWO_MID 180



#define TICKS_PER_INCH 97
#define DRIVE_PACE 10
#define DOWN_RAMP_DIST 110
#define DRAWBRIDGE_DOWN 256
#define DRAWBRIDGE_UP 128

#define THIRTY_CM_TICKS 2600
#define CENTER_ENCODER_STEPS 10100

//bool isLifting;

//int currentLifterPos;
//int lifterTickPosition;
//bool lifterMoving;
//int offset = 40;



void resetEncoder (tMotor anyMotor) {
	nMotorEncoder[anyMotor] = 0;
}

void motorSet (tMotor anyMotor, int power) {
	motor[anyMotor] = power;
}

void moveEncoderSteps(tMotor anyMotor, int encoderSteps, int power) {
	resetEncoder(anyMotor);
	while(abs(nMotorEncoder[anyMotor]) < encoderSteps) {
		motorSet(anyMotor, power);
	}
	motorSet(anyMotor, 0);
}

void resetDriveEncoders () {
	resetEncoder(leftA);
}

////***************** DRIVING ********************\\



void powerSide (int side, int power) {
	if (side == 0) {
		motorSet(leftA,power);
		motorSet(leftB,power);
	}
	else if (side == 1) {
		motorSet(rightA,power);
		motorSet(rightB,power);
	}
}

void drive (int leftPow, int rightPow) {
	powerSide(0,leftPow);
	powerSide(1,rightPow);
}

void straightDrive (int power) {
	drive(power, power);
}

void halt () {
	straightDrive(0);
}

void pivot (int direction, int power, float deg) {
	float heading = 0;
	float angle = deg;
	int delay = 20;
	wait1Msec(250);

	int offset = SensorValue(HTGYRO);

	if (direction == 1) {
		while (abs(heading) < abs(angle)) {
			heading += (SensorValue(HTGYRO) - offset) * (float)(delay / 1000.0);
			powerSide(0,power);
			powerSide(1,-power);
			wait1Msec(delay);
		}
	}
	else {
		while (abs(heading) < abs(angle)) {
		heading += (SensorValue(HTGYRO) - offset) * (float)(delay / 1000.0);
			powerSide(0,-power);
			powerSide(1,power);
			wait1Msec(delay);
		}
	}
	halt();
}

void swingTurn (int direction, int power, float deg) {
	float heading = 0;
	float angle = deg;
	int delay = 20;
	wait1Msec(250);

	int offset = SensorValue(HTGYRO);

	if (direction == 1) {
		while (abs(heading) < abs(angle)) {
			heading += (SensorValue(HTGYRO) - offset) * (float)(delay / 1000.0);
			powerSide(1,-power);
			powerSide(0,0);
			wait1Msec(delay);
		}
	}
	else {
		while (abs(heading) < abs(angle)) {
		heading += (SensorValue(HTGYRO) - offset) * (float)(delay / 1000.0);
			powerSide(0,-power);
			powerSide(1,0);
			wait1Msec(delay);
		}
	}
	halt();
}

void driveDistance (int power,int inches) {
	resetDriveEncoders();
	int tickGoal = abs(inches*TICKS_PER_INCH);
	while (abs(nMotorEncoder[leftA]) < tickGoal) {
			straightDrive(power * sgn(inches));
	}
	halt();
}

void driveDistance (int leftPower, int rightPower,int inches) {
	resetDriveEncoders();
	int tickGoal = abs(inches*TICKS_PER_INCH);
	while (abs(nMotorEncoder[leftA]) < tickGoal) {
			drive(leftPower * sgn(inches), rightPower * sgn(inches));
	}
	halt();
}

//**************** LIFTER *******************\\

task lifterDownFromCenter () {
	moveEncoderSteps(lifter, CENTER_ENCODER_STEPS-200, -100);
}

void lifterUpThirty () {
	moveEncoderSteps(lifter,THIRTY_CM_TICKS,100);
}

void lifterDownThirty () {
	moveEncoderSteps(lifter,THIRTY_CM_TICKS,-100);
}

task lifterToCenter () {
	isLifting = true;
	moveEncoderSteps(lifter, CENTER_ENCODER_STEPS + 200, 100);
	motorSet(lifter,100);
	wait1Msec(800);
	motorSet(lifter,0);
	isLifting = false;
}


//void moveLifterNumTicks (int ticks) {
//		resetEncoder(lifter);
//		lifterMoving = true;
//		while (abs(nMotorEncoder[lifter]) < abs(ticks)) {
//			motorSet(lifter,sgn(ticks)*100);
//		}
//		lifterTickPosition += ticks;
//		lifterMoving = false;
//}

//void lifterToZero () {
//	switch (currentLifterPos) {
//		case 0:
//			break; //already there
//		case 30:
//			moveLifterNumTicks(-LOWGOAL_LIFT_TICKS + offset);
//			break;
//		case 60:
//			moveLifterNumTicks(-MIDGOAL_LIFT_TICKS + offset);
//			break;
//		case 90:
//			moveLifterNumTicks(-TALLGOAL_LIFT_TICKS + offset);
//			break;
//		case 120:
//			moveLifterNumTicks(-CENTERGOAL_LIFT_TICKS + offset + 50);
//	}
//}

//void lifterToThirty () {
//	switch (currentLifterPos) {
//		case 0:
//			moveLifterNumTicks(LOWGOAL_LIFT_TICKS);
//			break;
//		case 30:
//			break; //already there
//		case 60:
//			moveLifterNumTicks(-LOWGOAL_LIFT_TICKS + offset);
//			break;
//		case 90:
//			moveLifterNumTicks(-MIDGOAL_LIFT_TICKS + offset);
//			break;
//		case 120:
//			moveLifterNumTicks(-TALLGOAL_LIFT_TICKS + offset);
//	}
//}

//void lifterToSixty () {//finish these functions for all positions
//	switch (currentLifterPos) {
//		case 0:
//			moveLifterNumTicks(MIDGOAL_LIFT_TICKS);
//			break;
//		case 30:
//			moveLifterNumTicks(LOWGOAL_LIFT_TICKS);
//			break;
//		case 60:
//			break; //already there
//		case 90:
//			moveLifterNumTicks(LOWGOAL_LIFT_TICKS);
//			break;
//		case 120:
//			moveLifterNumTicks(-LOWGOAL_LIFT_TICKS  + offset);
//	}
//}

//void lifterToNinety () {
//	switch (currentLifterPos) {
//		case 0:
//			moveLifterNumTicks(TALLGOAL_LIFT_TICKS);
//			break;
//		case 30:
//			moveLifterNumTicks(MIDGOAL_LIFT_TICKS);
//			break;
//		case 60:
//			break; //already there
//		case 90:
//			break; //already there
//		case 120:
//			moveLifterNumTicks(-LOWGOAL_LIFT_TICKS + offset);
//	}
//}

//void lifterToCenter () {
//	switch (currentLifterPos) {
//		case 0:
//			moveLifterNumTicks(CENTERGOAL_LIFT_TICKS);
//			break;
//		case 30:
//			moveLifterNumTicks(TALLGOAL_LIFT_TICKS);
//			break;
//		case 60:
//			moveLifterNumTicks(MIDGOAL_LIFT_TICKS);
//			break;
//		case 90:
//			moveLifterNumTicks(LOWGOAL_LIFT_TICKS);
//			break; //already there
//	}
//}

//int getLifterGoalHeight () {
//		if (lifterTickPosition == 0) return 0;
//		else if ((lifterTickPosition > LOWGOAL_LIFT_TICKS - 5) && (lifterTickPosition < LOWGOAL_LIFT_TICKS + 5)) return 30;
//		else if ((lifterTickPosition > MIDGOAL_LIFT_TICKS - 5) && (lifterTickPosition < MIDGOAL_LIFT_TICKS + 5)) return 60;
//		else if ((lifterTickPosition > TALLGOAL_LIFT_TICKS - 5) && (lifterTickPosition < TALLGOAL_LIFT_TICKS + 5)) return 90;
//		else if ((lifterTickPosition > CENTERGOAL_LIFT_TICKS - 5) && (lifterTickPosition < CENTERGOAL_LIFT_TICKS + 5)) return 120;
//		return 256;
//}

//******************** SONAR *******************\\

int readSonar (int numReads) {
	int inputdata;

  // Set B0 for output
  HTSPBsetupIO(HTSPB, 0x1);

  // Read a 10bit wide analogue value from A0
  inputdata = 0;
	for (int i=0; i< numReads; i++) {
  	inputdata += HTSPBreadADC(HTSPB, 0, 10);
  	wait1Msec(5);
	}
	inputdata /= numReads;
	return inputdata;
  // If A0 is less than 50% of the max value
  // turn off the LED, otherwise switch it on
}

int sonarTurretPosition (int servoPos, int numReads) {
	servo[servoTurret] = servoPos;
	wait1Msec(750);
	int sonarVal = readSonar(numReads);
	return sonarVal;
}

int findOrientation () {
	int position = sonarTurretPosition (128,100);
	nxtDisplayCenteredTextLine(2,"Read: %d",position);
	wait1Msec(1000);
	if (position > 347 && position < 410)	return 1;
	else if (position > 410 && position < 1200) return 2;
	else if (position <= 347) return 3;
	else return 0; //indeterminate
}

void driveUntilCloserThan (int power,int targetDist) {
	int dist = readSonar(1);
	nxtDisplayCenteredTextLine(2,"dist:%d",dist);
	wait1Msec(500);
	while (dist > targetDist) {
		straightDrive(power);
		dist = readSonar(1);
		nxtDisplayCenteredTextLine(2,"dist:%d",dist);
	}
	halt();
}

void driveUntilFartherThan (int power,int targetDist) {
	int dist = readSonar(5);
	nxtDisplayCenteredTextLine(2,"dist:%d",dist);
	wait1Msec(500);
	while (dist < targetDist) {
		straightDrive(power);
		dist = readSonar(5);
		nxtDisplayCenteredTextLine(2,"dist:%d",dist);
	}
	halt();
}


//****************** GRABBERS **************************

void grabbersDown () {
	servo[grabOne] = GRAB_ONE_DOWN;
	servo[grabTwo] = GRAB_TWO_DOWN;
	wait1Msec(100);
}


void grabbersUp () {
	servo[grabOne] = GRAB_ONE_UP;
	servo[grabTwo] = GRAB_TWO_UP;
	wait1Msec(100);
}

void grabbersMidway () {
	servo[grabOne] = GRAB_ONE_MID;
	servo[grabTwo] = GRAB_TWO_MID;
	wait1Msec(100);
}

//******************** DRAWBRIDGE **************************\\




void bridgeOpen () {
	servo[drawbridge] = 0;
	wait1Msec(500);
}

void bridgeClosed () {
	servo[drawbridge] = 225;
	wait1Msec(500);
}

//void scoreCenter () {
//	startTask(lifterToCenter);
//	wait1Msec(100);
//	driveDistance(-10,5);
//	while (isLifting) wait1Msec(1);
//	bridgeOpen();
//	wait1Msec(2000);
//	driveDistance(10,8);
//	wait1Msec(100);
//	bridgeClosed();
//	startTask(lifterDownFromCenter);
//}



#endif
