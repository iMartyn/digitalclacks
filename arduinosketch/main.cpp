#include <Arduino.h>
#include <Servo.h> 
#include "alphabet.h"

#define LEFT_ARM_PIN 10
#define RIGHT_ARM_PIN 9
#define MAX_RANGE 165
#define MIN_RANGE 5
#define DEGREE_DIVISOR 2

/*
 WaveFlag
 */
int main(void)
{
	init();
	setup();
	for (;;)
		loop();

	return 0; // must NEVER be reached
}

Servo leftArmServo; // create servo object to control a servo 
Servo rightArmServo; // create servo object to control a servo 
int pos;

int limitAngle(int anAngle)
{
	Serial.print(" Limit ");
	Serial.println(anAngle);
	if (anAngle < MIN_RANGE) {
		return MIN_RANGE;
	} else if (anAngle > MAX_RANGE) {
		return MAX_RANGE;
	}
	return anAngle;
}

int leftArmAngle(int intendedAngle)
{
	Serial.print(" L: ");
	Serial.print(intendedAngle);
	int correctAngle = (intendedAngle + 180 + 45);
	if (correctAngle >= 360) {
		correctAngle -= 360;
	}
	return limitAngle(correctAngle / DEGREE_DIVISOR);
}

int rightArmAngle(int intendedAngle)
{
	Serial.print(" R: ");
	Serial.print(intendedAngle);
	int correctAngle = (intendedAngle + 45);
	if (correctAngle >= 360) {
		correctAngle -= 360;
	}
	return limitAngle(correctAngle / DEGREE_DIVISOR);
}

void setup()
{
	// initialize the digital pin as an output.
	// Pin 13 has an LED connected on most Arduino boards:
	pinMode(13, OUTPUT);
	leftArmServo.attach(LEFT_ARM_PIN); // attaches the servo on pin 9 to the servo object 
	rightArmServo.attach(RIGHT_ARM_PIN); // attaches the servo on pin 10 to the servo object 
	Serial.begin(9600);
	leftArmServo.write(5);//leftArmAngle(letterAngleLeft[SPECIAL_REST]));
	rightArmServo.write(5);//rightArmAngle(letterAngleRight[SPECIAL_REST]));
}

void magicError()
{
	/* TODO: WAVE ABOUT*/
}

void loop()
{
	if (Serial.available()) {
		int inByte = Serial.read();
		int lookupByte;
		if (inByte == ' ') {
			lookupByte = SPECIAL_REST;
		} else if ((inByte >= '1') && (inByte <= '9')) {
			lookupByte = inByte - '1';
		} else if (inByte == '0') {
			lookupByte = 'k' - 'a';
		} else if ((inByte >= 'A') && (inByte <= 'Z')) {
			lookupByte = inByte - 'A';
		} else if ((inByte >= 'a') && (inByte <= 'z')) {
			lookupByte = inByte - 'a';
		} else {
			lookupByte = SPECIAL_RESET_ERR;
		}
		if (lookupByte == SPECIAL_RESET_ERR) {
			magicError();
		} else {
			leftArmServo.write(leftArmAngle(letterAngleLeft[lookupByte]));
			rightArmServo.write(rightArmAngle(letterAngleRight[lookupByte]));
		}
	}
}