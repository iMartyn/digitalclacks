#include <Arduino.h>
#include <Servo.h> 
#include "alphabet.h"

#define LEFT_ARM_PIN 10
#define RIGHT_ARM_PIN 9
#define MAX_RANGE 150
#define MIN_RANGE 5
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

int limitAngle(int anAngle)
{
	if (anAngle < MIN_RANGE) {
		return MIN_RANGE;
	} else if (anAngle > MAX_RANGE) {
		return MAX_RANGE;
	}
	return anAngle;
}

int leftArmAngle(int intendedAngle)
{
	int correctAngle = (intendedAngle + 180 + 45);
	if (correctAngle >= 360) {
		correctAngle -= 360;
	}
	correctAngle = map(correctAngle,0,270,MIN_RANGE,MAX_RANGE);
	return limitAngle(correctAngle);
}

int rightArmAngle(int intendedAngle)
{
	int correctAngle = (intendedAngle + 45);
	if (correctAngle >= 360) {
		correctAngle -= 360;
	}
	correctAngle = map(correctAngle,0,270,MIN_RANGE,MAX_RANGE);
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
	leftArmServo.write(MIN_RANGE);
	rightArmServo.write(MIN_RANGE);
	delay(5000);
	leftArmServo.write(MAX_RANGE);
	rightArmServo.write(MAX_RANGE);
	delay(5000);
	//leftArmServo.write(leftArmAngle(letterAngleLeft[SPECIAL_REST]));
	//rightArmServo.write(rightArmAngle(letterAngleRight[SPECIAL_REST]));
	inNumbersMode = 0;
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
			displaySymbol(lookupByte, inByte);
		}
	}
}