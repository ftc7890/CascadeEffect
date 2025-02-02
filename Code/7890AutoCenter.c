#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     HTSPB,          sensorI2CCustom9V)
#pragma config(Sensor, S4,     HTGYRO,         sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     leftA,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftB,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     rightA,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rightB,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     lifter,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     spinner,       tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    drawbridge,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    grabOne,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    grabTwo,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servoTurret,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//** Team 7890: Space Lions
//** Horace Mann School, Bronx, NY
//** Version: 3/8/15
//** Tournament Iteration: NJ State Championship (NJIT)
//** Authors: Nick Keirstead, Jacob Hoglund, Joshua Gruenstein

//Steps of Program:
	//- Determine Position of center structure with sonar
	//- Score two autonomous balls in center goal (120 pts)
	//- Knock out the kickstand (30 pts)
	//--> ideal total = 150 pts


//Sensing Used:
		//- Custom Sonar Rangefinder connected to HiTechnic Superpro Protoboard
		//- HiTechnic Gyroscope
		//- Motor Encoders

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "helperFunctions.h"



void initializeRobot()
{
	servo[servoTurret] = 128; //point custom rangefinder forward
	grabbersMidway();
	bridgeClosed();
}

void scoreCenter  (int position) {
	switch (position) {
		case 1:
			driveDistance(15,2);
			startTask(lifterToCenter);
			driveUntilCloserThan(15,165);
			wait1Msec(50);
			pivot(0,15,35);
			wait1Msec(50);
			servo[servoTurret] = 190;
			wait1Msec(50);
			driveUntilFartherThan(15,500);
			wait1Msec(50);
			driveDistance(15,13);
			wait1Msec(50);
			pivot(0,15,35);
			wait1Msec(50);
			driveDistance(-10,10);
			wait1Msec(50);
			bridgeOpen();
				wait1Msec(1500);
				driveDistance(15,7);
				startTask(lifterDownFromCenter);
				pivot(1,20,35);
				wait1Msec(50);
				driveDistance(-15,20);
				wait1Msec(50);
				pivot(0,15,45);
				wait1Msec(50);
				driveDistance(-100,35);
			break;
		case 2:
			servo[servoTurret] = 75;
			wait1Msec(600);
			driveDistance(15,2);
			startTask(lifterToCenter);
			driveUntilCloserThan(15,140);
			wait1Msec(100);
			driveDistance(-15,10);
			wait1Msec(50);
			pivot(0,15,45);
			wait1Msec(50);
			driveDistance(15,22);
			wait1Msec(50);
			pivot(0,15,68);
			wait1Msec(50);
			driveDistance(-15,13);
			wait1Msec(500);
			bridgeOpen();
			wait1Msec(2000);
			driveDistance(15,8);
			wait1Msec(100);
			startTask(lifterDownFromCenter);
			pivot(1,15,60);
			wait1Msec(50);
			driveDistance(-15,10);
			wait1Msec(50);
			swingTurn(0,20,95);
			wait1Msec(50);
			driveDistance(-100,20);
			break;
		case 3:
			driveDistance(15,2);
			startTask(lifterToCenter);
			driveUntilCloserThan(15,170);
			wait1Msec(100);
			pivot(1,15,185);
			wait1Msec(50);
			driveDistance(-15,13);
			wait1Msec(50);
			bridgeOpen();
			wait1Msec(2000);
			driveDistance(15,7);
			bridgeClosed();
			startTask(lifterDownFromCenter);
			pivot(1,15,50);
			wait1Msec(50);
			driveDistance(-15,22);
			wait1Msec(50);
			pivot(0,15,65);
			wait1Msec(50);
			driveDistance(-100,30);
			wait1Msec(50);
			driveDistance(50,15);
			wait1Msec(500);
			driveDistance(-100,30);
			break;
	}
}

task main () {
	 	initializeRobot();
	 	waitForStart();
		int position = findOrientation();
		//nxtDisplayTextLine(2, "Position: %d", position);
		//wait1Msec(1000);
		scoreCenter(position);
}

////******************
//// NOTES SECTION

//library "prodrive.h" credit:
//	author Gustav Jansson (gus_at_hitechnic.com)
// 	date 10 October 2011
// 	version 0.1
