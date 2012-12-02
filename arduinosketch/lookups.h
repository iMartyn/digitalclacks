/* 
 * File:   alphabet.h
 * Author: martyn
 *
 * Created on 01 December 2012, 17:24
 */

#ifndef ALPHABET_H
#define	ALPHABET_H

#define FLAG_POS0 0
#define FLAG_POS1 1
#define FLAG_POS2 2
#define FLAG_POS3 3
#define FLAG_POS4 4
#define FLAG_POS5 5
#define FLAG_POS6 6
#define FLAG_POS7 7

#define SPECIAL_REST 26
#define SPECIAL_NUMERALS 27
#define SPECIAL_ALPHAMODE ('J'-'A')
#define SPECIAL_CANCEL 28
#define SPECIAL_RESET_ERR -1

/* Angle we set the servo to, 0 is assumed to be 0 degrees starting from 
 * straight down. Arm 1 here */
const int letterAngleRight[29] = {
	/* A = 1, B = 2, C = 3, D = 4, E = 5, F = 6, G = 7 */
	FLAG_POS0,FLAG_POS0,FLAG_POS0,FLAG_POS0,FLAG_POS5,FLAG_POS6,FLAG_POS7,
	/* H = 8, I = 9, J = LETTERS, K = 0, L, M, N */
	FLAG_POS1,FLAG_POS1,FLAG_POS6,FLAG_POS4,FLAG_POS5,FLAG_POS6,FLAG_POS7,
	/* O, P, Q, R & S */
	FLAG_POS3,FLAG_POS4,FLAG_POS5,FLAG_POS6,FLAG_POS7,
	/* T, U & V*/
	FLAG_POS4,FLAG_POS5,FLAG_POS7,
	/* W & X */
	FLAG_POS6,FLAG_POS7,
	/* Y & Z */
	FLAG_POS6,FLAG_POS6,
	/* REST, NUMS, CANCEL */
	FLAG_POS0,FLAG_POS5,FLAG_POS7
};
/* And arm 2 here. */
const int letterAngleLeft[29] = {
	/* A = 1, B = 2, C = 3, D = 4, E = 5, F = 6, G = 7 */
	FLAG_POS1,FLAG_POS2,FLAG_POS3,FLAG_POS4,FLAG_POS0,FLAG_POS0,FLAG_POS0,
	/* H = 8, I = 9, J = LETTERS, K = 0, L, M, N */
	FLAG_POS2,FLAG_POS3,FLAG_POS4,FLAG_POS1,FLAG_POS1,FLAG_POS1,FLAG_POS1,
	/* O, P, Q, R & S */
	FLAG_POS2,FLAG_POS2,FLAG_POS2,FLAG_POS2,FLAG_POS2,
	/* T, U & V*/
	FLAG_POS3,FLAG_POS3,FLAG_POS3,
	/* W & X */
	FLAG_POS4,FLAG_POS4,
	/* Y & Z*/
	FLAG_POS3,FLAG_POS7,
	/* REST, NUMS, CANCEL */
	FLAG_POS0,FLAG_POS4,FLAG_POS3
};

const int flagsPositionsLeft[8] = {130,104,77,52,30,10,-1,154};
const int flagsPositionsRight[8] = {29,6,-1,152,125,100,75,54};

#define FLAG_LEFT_POS_0 = 130
#define FLAG_LEFT_POS_1 = 104
#define FLAG_LEFT_POS_2 = 77
#define FLAG_LEFT_POS_3 = 52
#define FLAG_LEFT_POS_4 = 30
#define FLAG_LEFT_POS_5 = 10
#define FLAG_LEFT_POS_7 = 154

#define FLAG_RIGHT_POS_0 = 29
#define FLAG_RIGHT_POS_1 = 6
#define FLAG_RIGHT_POS_3 = 152
#define FLAG_RIGHT_POS_4 = 125
#define FLAG_RIGHT_POS_5 = 100
#define FLAG_RIGHT_POS_6 = 75
#define FLAG_RIGHT_POS_7 = 54

	

#endif	/* ALPHABET_H */

