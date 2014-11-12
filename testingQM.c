#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorFR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorFL,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorBL,       tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    ballDrop,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    lift,                 tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_4,    aRmLifter,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_5,    hookF,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------+
|                                														|
| Last Edited: Meet Patel 11/03/14
|																														|
+----------------------------------------------------------*/

#include "JoystickDriver.c"

void haltMotors() {
	//Setting all the motors and encoders to 0
	//nMotorEncoder[motorBL] = 0;
	//nMotorEncoder[motorBR] = 0;
	nMotorEncoder[motorFL] = 0;
	nMotorEncoder[motorFR] = 0;

	motor[motorBL] = 0;
	motor[motorFR] = 0;
	motor[motorBR] = 0;
	motor[motorFL] = 0;
}

void forwardMarch(int pwr) {
	 	motor[motorBL] = pwr;
    motor[motorFL] = pwr;
    motor[motorFR] = pwr;
    motor[motorBR] = pwr;
}

void moveTicks(int pwr, int dir, int ticks){
	//1440 ticks = 1 rotation
  nMotorEncoder[motorFR] = 0;
  nMotorEncoder[motorFL] = 0;
  // abs() lets you use the same program for both forward and backward directions.
  while(abs(nMotorEncoder[motorFL]) < ticks && abs(nMotorEncoder[motorFR]) < ticks){
    if(abs(nMotorEncoder[motorFL]) > abs(nMotorEncoder[motorFR])){ // if the left side is driving faster than the right side
      motor[motorBL] = (pwr-2)*dir;
      motor[motorFL] = (pwr-2)*dir;
      motor[motorFR] = (pwr+2)*dir;
      motor[motorBR] = (pwr+2)*dir;
    }
    else if (abs(nMotorEncoder[motorFR]) > abs(nMotorEncoder[motorFL])){ // if the right side is faster than the left side
      motor[motorBL] = (pwr+2)*dir;
      motor[motorFL] = (pwr+2)*dir;
      motor[motorFR] = (pwr-2)*dir;
      motor[motorBR] = (pwr-2)*dir;
    }
    else {
   	forwardMarch(100);
    }
  }
  haltMotors();
}

void turnTicks(int pwr, int ticks){
	//1440 ticks = 1 rotation
  nMotorEncoder[motorFR] = 0;
  nMotorEncoder[motorFL] = 0;
  // abs() lets you use the same program for both forward and backward directions.
  while(abs(nMotorEncoder[motorFL]) < ticks && abs(nMotorEncoder[motorFR]) < ticks){
    motor[motorFR] = -pwr;
    motor[motorFL] = pwr;
    motor[motorBR] = -pwr;
    motor[motorBL] = pwr;
  }
  haltMotors();
}

void auto1() {
	int dropstart = 80;
	int dropend = 240;
	int openLeft = 180;
	int openRight = 93;
	int closeRight = 147;
	int closeLeft = 129;
	int startRight = 200;
	int startLeft = 30;

	servo[ballDrop] = dropstart;
	//servo[hookFL] = startLeft;
	//servo[hookFR] = startRight;

	waitForStart();


	//forwards
	moveTicks(30, 1, 2000);

	wait10Msec(50);
	//turn right 45 deg
	turnTicks(30, 1370);
wait10Msec(50);
	moveTicks(30, 1, 1800);
wait10Msec(50);
	//turn left 45 deg
	turnTicks(50, 1380);

	wait10Msec(50);

	moveTicks(70, 1, 5000);

	//get ready to hook
	//servo[hookFL] = openLeft;
	//servo[hookFR] = openRight;

	wait10Msec(50);

	moveTicks(20, 1, 4700);
wait10Msec(100);
	//drop and hook

		//servo[hookFL] = closeLeft;
   // servo[hookFR] = closeRight;


	wait10Msec(75);

		servo[ballDrop] = dropend;

	wait10Msec(100);

	moveTicks(50, -1, 6000);

	turnTicks(50, 900);

	moveTicks(30, -1, 7000);



	wait10Msec(50);

	turnTicks(-50, 4500);

}

void turnLeft(int ticks) {
	nMotorEncoder[motorFL] = 0;
	nMotorEncoder[motorFR] = 0;
	motor[motorBL] = -100;
	motor[motorBR] = 100;
	motor[motorFL] = -100;
	motor[motorFR] = 100;
}

//TODO correct value for this
const int COEF = 20; //coeff conversion between IR sensor vals and ticks
const int TURN_SPEED = 50;
//Finds the ir beacon
//recurse prevents the robot from repeatedly turning too far to face the right way
void sensIR(int recurse) {
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
}

void sensIR() {
	sensIR(1);
}

int int2bin(int val) {
	int ret = 0;
	while(val > 0b01) {
		val >>= 1;
		ret++;
	}
	return ret;
}

const int THRESHOLD = 27;
task main()
{
	//waitForStart()
	//make sure there is a threshold the joystick values have to pass to move the motors
	//the motors might stop if we have values that are too low

	//The manual event loop
 while(true)
  {
    getJoystickSettings(joystick);  // Update Buttons and Joysticks

    nxtDisplayTextLine(3, "j1y1 %d", joystick.joy1_y1);
    nxtDisplayTextLine(4, "j1y2 %d", joystick.joy1_y2);

    short y1 = joystick.joy1_y1;
    //Threshold is 27 right now see above declaration ^^
    if(abs(y1) < THRESHOLD) {
    	y1 = 0;
  	}
    short y2 = joystick.joy1_y2;
    if(abs(y2) < THRESHOLD) {
    	y2 = 0;
  	}
    motor[motorBL] = y1;
    motor[motorFL] = y1;

    motor[motorBR] = y2;
    motor[motorFR] = y2;

    nxtDisplayTextLine(1, "left: %d", motor[motorBL]);
    nxtDisplayTextLine(2, "right: %d", motor[motorBR]);

    if(joy1Btn(7) == 1) {
    	//disengage primarys
    	nxtDisplayTextLine(5, "primary left");
    	servo[aRmLifter]=50;
    	wait10Msec(50);
    	//the value 132 stops THIS continous rotation servoget for some reason -bg
    	servo[aRmLifter] = 132;
  	}

  	if(joy1Btn(8) == 1) {
  		//engage primary
  		nxtDisplayTextLine(5, "primary right");
  		servo[aRmLifter]=200;
    	wait10Msec(50);
    	//the value 127 stops a continous rotation servo but you need servoTarget for some reason -bg
    	servo[aRmLifter] = 132;

  	}
 /* 	if(joy1Btn(7) == 1) {
  		//disengage secondary
  		nxtDisplayTextLine(6, "secondary left");
  	}
  	if(joy1Btn(8) == 1) {
  		//engage secondary
  		nxtDisplayTextLine(6, "secondary right");
  	}
/*    if(joy1Btn(1) == 1)                 // If Joy1-Button1 is pressed:
    {
    	nxtDisplayTextLine(3, "motor 1 go");
      motor[motorFR] = 100;              // Turn Motor A On at full power
    }
    else                            // If Joy1-Button1 is NOT pressed:
    {
     motor[motorFR] = 0;                 // Turn Motor A Off
    }*/
  }
}
