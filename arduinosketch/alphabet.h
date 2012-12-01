/* 
 * File:   alphabet.h
 * Author: martyn
 *
 * Created on 01 December 2012, 17:24
 */

#ifndef ALPHABET_H
#define	ALPHABET_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#define FLAG_POS0 0
#define FLAG_POS1 45
#define FLAG_POS2 90
#define FLAG_POS3 135 
#define FLAG_POS4 180
#define FLAG_POS5 225
#define FLAG_POS6 270
#define FLAG_POS7 315

#define SPECIAL_REST 26
#define SPECIAL_NUMERALS 27
#define SPECIAL_CANCEL 28
#define SPECIAL_RESET_ERR -1

/* Angle we set the servo to, 0 is assumed to be 0 degrees starting from 
 * straight down. Arm 1 here */
int letterAngle1[29] = {
	/* A = 1, B = 2, C = 3, D = 4, E = 5, F = 6, G = 7 */
	FLAG_POS0,FLAG_POS0,FLAG_POS0,FLAG_POS0,FLAG_POS0,FLAG_POS0,FLAG_POS0,
	/* H = 8, I = 9, J = LETTERS, K = 0, L, M, N */
	FLAG_POS1,FLAG_POS1,FLAG_POS4,FLAG_POS1,FLAG_POS1,FLAG_POS1,FLAG_POS1,
	/* O, P, Q, R & S */
	FLAG_POS2,FLAG_POS2,FLAG_POS2,FLAG_POS2,FLAG_POS2,
	/* T, U & V*/
	FLAG_POS3,FLAG_POS3,FLAG_POS3,
	/* W & X */
	FLAG_POS4,FLAG_POS4,
	/* Y & Z */
	FLAG_POS6,FLAG_POS6,
	/* REST, NUMS, CANCEL */
	FLAG_POS0,FLAG_POS4,FLAG_POS3
};
/* And arm 2 here. */
int letterAngle2[29] = {
	/* A = 1, B = 2, C = 3, D = 4, E = 5, F = 6, G = 7 */
	FLAG_POS1,FLAG_POS2,FLAG_POS3,FLAG_POS4,FLAG_POS5,FLAG_POS6,FLAG_POS7,
	/* H = 8, I = 9, J = LETTERS, K = 0, L, M, N */
	FLAG_POS2,FLAG_POS3,FLAG_POS6,FLAG_POS4,FLAG_POS5,FLAG_POS6,FLAG_POS7,
	/* O, P, Q, R & S */
	FLAG_POS3,FLAG_POS4,FLAG_POS5,FLAG_POS6,FLAG_POS7,
	/* T, U & V*/
	FLAG_POS4,FLAG_POS5,FLAG_POS6,FLAG_POS7,
	/* W & X */
	FLAG_POS6,FLAG_POS7,
	/* Y & Z*/
	FLAG_POS3,FLAG_POS7,
	/* REST, NUMS, CANCEL */
	FLAG_POS0,FLAG_POS5,FLAG_POS7
};


#endif	/* ALPHABET_H */

