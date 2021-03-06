#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     US,             sensorSONAR)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorNom,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorPulley,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorBL,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     motorBR,       tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    box,                  tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

//if whichAuto = false, we will run the ramp autonomous code
const bool whichAuto = true;

void turnLeft(int ticks) {
	//nMotorEncoder[motorFL] = 0;
	//nMotorEncoder[motorFR] = 0;
	motor[motorBL] = -100;
	motor[motorBR] = 100;
	motor[motorFL] = -100;
	motor[motorFR] = 100;
	wait1Msec(ticks);
	motor[motorBL] = 0;
	motor[motorBR] = 0;
	motor[motorFL] = 0;
	motor[motorFR] = 0;
}

void turnRight(int ticks) {
	motor[motorBL] = 100;
	motor[motorBR] = -100;
	motor[motorFL] = 100;
	motor[motorFR] = -100;
	wait1Msec(ticks);
	motor[motorBL] = 0;
	motor[motorBR] = 0;
	motor[motorFL] = 0;
	motor[motorFR] = 0;
}

//TODO correct value for this
//Finds the ir beacon
//recurse prevents the robot from repeatedly turning too far to face the right way
/*void sensIR(int recurse) {
	bool found = false;
	while(!found) {
		while(SensorValue[IR] == 0) {}
		int val = SensorValue[IR]; //wtf is a `word` datatype
		if(val == 5) {
			found = true;
			//TODO this
		} else if(val < 5) {
			turnTicks(TURN_SPEED * -1, (val * COEF) / recurse);
			sensIR(recurse + 1);
		} else {
			turnTicks(TURN_SPEED, (val * COEF) / recurse);
			sensIR(recurse + 1);
		}
	}
}*/

/*void sensIR() {
	sensIR(1);
}*/

void backwards(int duration, int speed) {
	motor[motorBL] = speed;
	motor[motorBR] = speed;
	motor[motorFL] = speed;
	motor[motorFR] = speed;
	wait1Msec(duration);
	motor[motorBL] = 0;
	motor[motorBR] = 0;
	motor[motorFL] = 0;
	motor[motorFR] = 0;
}

void back(int target, int speed) {
	int current = nMotorEncoder[motorBL];
	motor[motorBL] = -speed;
	motor[motorBR] = -speed;
	motor[motorFL] = -speed;
	motor[motorFR] = -speed;
	while(nMotorEncoder[motorBL] - current > -target) {}
	motor[motorBL] = 0;
	motor[motorBR] = 0;
	motor[motorFL] = 0;
	motor[motorFR] = 0;
	wait1Msec(500);
}
void back(int target) {
	back(target, 50);
}

void forward(int target, int speed) {
	int current = nMotorEncoder[motorBL];
	motor[motorBL] = speed;
	motor[motorBR] = speed;
	motor[motorFL] = speed;
	motor[motorFR] = speed;
	while(nMotorEncoder[motorBL] - current < target) {}
	motor[motorBL] = 0;
	motor[motorBR] = 0;
	motor[motorFL] = 0;
	motor[motorFR] = 0;
	wait1Msec(500);
}

void forward(int target) {
	forward(target, 50);
}

void left(int target) {
	int current = nMotorEncoder[motorBL];
	motor[motorBL] = -50;
	motor[motorFL] = -50;
	motor[motorBR] = 50;
	motor[motorFR] = 50;
	while(nMotorEncoder[motorBL] - current > -target) {}
	motor[motorBL] = 0;
	motor[motorBR] = 0;
	motor[motorFL] = 0;
	motor[motorFR] = 0;
	wait1Msec(500);
}

void right(int target) {
	int current = nMotorEncoder[motorBL];
	motor[motorBL] = 50;
	motor[motorFL] = 50;
	motor[motorBR] = -50;
	motor[motorFR] = -50;
	while(nMotorEncoder[motorBL] - current < target) {}
	motor[motorBL] = 0;
	motor[motorBR] = 0;
	motor[motorFL] = 0;
	motor[motorFR] = 0;
	wait1Msec(500);
}

void allUp() {
	nMotorEncoder[motorPulley] = 0;
	motor[motorPulley] = 100;
	int last = -1;
	while(nMotorEncoder[motorPulley] == last || nMotorEncoder[motorPulley] < 6350) {
		last = nMotorEncoder[motorPulley];
		wait1Msec(100);
		nxtDisplayTextLine(4, "sensor: %d", nMotorEncoder[motorPulley]);
	}
	motor[motorPulley] = 0;
}

void allDown() {
	//nMotorEncoder[motorPulley] = 6270;
	int st = nMotorEncoder[motorPulley];
	motor[motorPulley] = -50;
	while(nMotorEncoder[motorPulley] > st - 6100) {}
	motor[motorPulley] = 0;
}

void autonomous() {
	//forwardMarch(100);
		//wait1Msec(1700);
		//forwardMarch(0);
	//	int power = 50;
servo[box] = 220;
	nMotorEncoder[motorBL] = 0;
	nMotorEncoder[motorPulley] = 0;
	//nMotorEncoder[motorBR] = 0;
	//back(2436);
	back(3886);
	//while(true) { nxtDisplayTextLine(3, "sensor: %d", SensorValue[US]); }
	if(whichAuto){
		//NEED TO REPLACE TIME VALUES WITH ENCODER VALUES
		//int min = 255;
		int avg = 0;
		for(int i = 0; i < 5; i++) {
			avg += SensorValue[US];
			//int current = SensorValue[US];
			//min = min < current ? min : current;
			wait1Msec(200);
		}
		avg /= 5;
	//while(true) { nxtDisplayTextLine(3, "avg: %d", avg); }
		//pos 3 = 19, pos 2 = 255, pos 1 = 36
		if(avg < 20) { //pos 3
			forward(400, 20);
			allUp();
			back(600, 10);
			servo[box] = 0;
			wait1Msec(2000);
			forward(400, 10);
			servo[box] = 220;
			wait1Msec(1000);
			allDown();
		} else if(avg > 100) { //pos 2
			forward(1450, 20);
			left(900);
			back(2750);
			right(1770);
			back(250, 10);
			allUp();
			back(410, 10);
			servo[box] = 0;
			wait1Msec(2000);
			forward(400, 10);
			servo[box] = 220;
			allDown();
			wait1Msec(1000);
		} else { //pos 1
			forward(1450, 20);
			left(700);
			back(5630);
			right(2450);
			allUp();
			back(1700, 10);
			servo[box] = 0;
			wait1Msec(2000);
			forward(400, 10);
			servo[box] = 220;
			wait1Msec(1000);
			allDown();
		}
		while(true) { nxtDisplayTextLine(4, "sensor: %d", SensorValue[US]); nxtDisplayTextLine(3, "avg: %d", avg); }
	}
	else backwards(1900, -80);
/*
	switch(SensorValue[IR]) {
	case 1: {
		forwardMarch(100);
		wait1Msec(1400);
		forwardMarch(0);
		motor[motorPulley] = 100;
		wait1Msec(9000);
		motor[motorPulley] = 0;

		break;
	}
	//case 3: {
		//forwardMarch();
		//wait1Msec();
		//forwardMarch();
	//}
	}*/

}


task main()
{
  //initializeRobot();

  waitForStart(); // Wait for the beginning of autonomous phase.

  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ////                                                   ////
  ////    Add your robot specific autonomous code here.  ////
  ////                                                   ////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////

  autonomous();
  //while(true) {
  //	nxtDisplayTextLine(1, "sensor: %d", SensorValue[US]);
	//}
}
