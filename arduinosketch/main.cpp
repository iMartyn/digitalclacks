#include <Arduino.h>
#include <Servo.h> 
#include "lookups.h"

#define LEFT_ARM_PIN 10
#define RIGHT_ARM_PIN 9
#define MIN_RANGE_LEFT 10
#define MAX_RANGE_LEFT 155
#define MIN_RANGE_RIGHT 7
#define MAX_RANGE_RIGHT 140
#define DEGREE_DIVISOR 2
#define DELAY_BETWEEN_CHARS 1000
#define DELAY_BETWEEN_ERROR 200

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
byte inNumbersMode;
byte inTestMode;

int limitAngle(int anAngle)
{
	if (anAngle < min(MIN_RANGE_LEFT,MIN_RANGE_RIGHT)) {
		return min(MIN_RANGE_LEFT,MIN_RANGE_RIGHT);
	} else if (anAngle > max(MAX_RANGE_LEFT,MAX_RANGE_RIGHT)) {
		return max(MAX_RANGE_LEFT,MAX_RANGE_RIGHT);
	}
	return anAngle;
}

int leftArmAngle(int intendedAngle)
{
	int correctAngle = flagsPositionsLeft[intendedAngle];
	return limitAngle(correctAngle);
}

int rightArmAngle(int intendedAngle)
{
	int correctAngle = flagsPositionsRight[intendedAngle];
	return limitAngle(correctAngle);
}

void setup()
{
	// initialize the digital pin as an output.
	// Pin 13 has an LED connected on most Arduino boards:
	pinMode(13, OUTPUT);
	leftArmServo.attach(LEFT_ARM_PIN); // attaches the servo on pin 9 to the servo object 
	rightArmServo.attach(RIGHT_ARM_PIN); // attaches the servo on pin 10 to the servo object 
	Serial.begin(9600);
	leftArmServo.write(MIN_RANGE_LEFT);
	rightArmServo.write(MIN_RANGE_RIGHT);
	delay(2000);
	leftArmServo.write(MAX_RANGE_LEFT);
	rightArmServo.write(MAX_RANGE_RIGHT);
	delay(2000);
	leftArmServo.write(leftArmAngle(letterAngleLeft[SPECIAL_REST]));
	rightArmServo.write(rightArmAngle(letterAngleRight[SPECIAL_REST]));
	inNumbersMode = 0;
	inTestMode = 0;
}

void displaySymbol(int lookupByte, int originalByte)
{
	if ((originalByte >= '0') && (originalByte <= '9')) {
		if (!inNumbersMode) {
			leftArmServo.write(leftArmAngle(letterAngleLeft[SPECIAL_NUMERALS]));
			rightArmServo.write(rightArmAngle(letterAngleRight[SPECIAL_NUMERALS]));
			inNumbersMode = 1;
			delay(DELAY_BETWEEN_CHARS);
		}
	} else if (inNumbersMode) {
		leftArmServo.write(leftArmAngle(letterAngleLeft[SPECIAL_ALPHAMODE]));
		rightArmServo.write(rightArmAngle(letterAngleRight[SPECIAL_ALPHAMODE]));
		inNumbersMode = 0;
		delay(DELAY_BETWEEN_CHARS);
	}
	leftArmServo.write(leftArmAngle(letterAngleLeft[lookupByte]));
	rightArmServo.write(rightArmAngle(letterAngleRight[lookupByte]));
	delay(DELAY_BETWEEN_CHARS);
}

void magicError()
{
	inNumbersMode = 0;
	leftArmServo.write(leftArmAngle(letterAngleLeft['u'-'a']));
	rightArmServo.write(rightArmAngle(letterAngleRight['u'-'a']));
	delay(DELAY_BETWEEN_ERROR);
	leftArmServo.write(leftArmAngle(letterAngleLeft['n'-'a']));
	rightArmServo.write(rightArmAngle(letterAngleRight['n'-'a']));
	delay(DELAY_BETWEEN_ERROR);
	leftArmServo.write(leftArmAngle(letterAngleLeft['u'-'a']));
	rightArmServo.write(rightArmAngle(letterAngleRight['u'-'a']));
	delay(DELAY_BETWEEN_ERROR);
	leftArmServo.write(leftArmAngle(letterAngleLeft['n'-'a']));
	rightArmServo.write(rightArmAngle(letterAngleRight['n'-'a']));
	delay(DELAY_BETWEEN_ERROR);
	leftArmServo.write(leftArmAngle(letterAngleLeft['u'-'a']));
	rightArmServo.write(rightArmAngle(letterAngleRight['u'-'a']));
	delay(DELAY_BETWEEN_ERROR);
	leftArmServo.write(leftArmAngle(letterAngleLeft['n'-'a']));
	rightArmServo.write(rightArmAngle(letterAngleRight['n'-'a']));
	displaySymbol(SPECIAL_REST,' ');
}

int testModeLeft = 0;
int testModeRight = 0;

void testMode(byte direction) {
	/* 
	 * 0 = left up
	 * 1 = left down
	 * 2 = right up
	 * 3 = right down
	*/
	if (direction == 0) {
		leftArmServo.write(testModeLeft++);
		Serial.print("Left Arm at ");
		Serial.println(testModeLeft);
	} else if (direction == 1) {
		leftArmServo.write(testModeLeft--);
		Serial.print("Left Arm at ");
		Serial.println(testModeLeft);
	} else if (direction == 2) {
		rightArmServo.write(testModeRight++);
		Serial.write("Right Arm at ");
		Serial.println(testModeRight);
	} else if (direction == 3) {
		rightArmServo.write(testModeRight--);
		Serial.write("Right Arm at ");
		Serial.println(testModeRight);
	}
}

void loop()
{
	if (Serial.available()) {
		int inByte = Serial.read();
		if (!inTestMode) {
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
				if (inByte == '#') {
					inTestMode = 1;
				}
			} else {
				displaySymbol(lookupByte, inByte);
			}
		} else {
			if (inByte == 13) {
				inTestMode = 0;
				magicError();
			} else if ((inByte >= 'a') && (inByte <= 'd')) {
				testMode(inByte - 'a');
			}
		}
	}
}