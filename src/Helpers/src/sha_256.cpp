/*
 Copyright (c) 2014 Honeywell, Inc.  All rights reserved.

 This file is released under license.  Contact your HSM representative to setup
 a license agreement in order to obtain rights to use this file
 */
#define LOG_TAG "SHA_256"

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <linux/types.h>

#define AUTHENTICATION_KEY_BYTES	20
#define CHALLENGE_BYTES			20
#define ROMID_BYTES			4
#define TRUE				1
#define FALSE				0
#define MAC_RESULT_LEN			16

static int iSecret[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static int iChallenge[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static int iROMID[] = { 0, 0, 0, 0 };
static int iMAC[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static int Secret64bit = FALSE;
static const int WithID = TRUE;
static const int WithoutID = FALSE;


// 01234567 89ABCDEF FEDCBA98 76543210
static unsigned char DefaultAuthenticationKey[AUTHENTICATION_KEY_BYTES] =
{
	0x94, 0xDA,
	0x43, 0x3F,
	0xD1, 0x06,
	0x55, 0x9B,
	0x26, 0xFE,
	0x59, 0x22,
	0x3E, 0x33,
	0xF2, 0xD1,
	0x75, 0x3F,
	0x66, 0x14,
};

static unsigned char DefaultChallengeData[CHALLENGE_BYTES] =
{
	0xDF, 0x21,
	0xE5, 0x29,
	0x0E, 0x55,
	0xDD, 0xF9,
	0x8B, 0xC8,
	0x2B, 0x95,
	0x48, 0x35,
	0xFF, 0x32,
	0xB7, 0xCF,
	0xF8, 0xA7,
};
//***********************************************************************************
//Hash Core
//This method assembles the message block, then performs the sha hash on that block, and when
// finished stores the result in the internal MAC integer array. The ROMID to be used is passed into
// the method. This allows either the real ROMID or a value of all 1's to be used for the hash.
//***********************************************************************************
static void Hash(int useROMID)
{
	//Initialize hash values:
	//(first 32 bits of the fractional parts of the square roots of the first 8 primes 2..19):
	unsigned int h0 = 0x6a09e667;
	unsigned int h1 = 0xbb67ae85;
	unsigned int h2 = 0x3c6ef372;
	unsigned int h3 = 0xa54ff53a;
	unsigned int h4 = 0x510e527f;
	unsigned int h5 = 0x9b05688c;
	unsigned int h6 = 0x1f83d9ab;
	unsigned int h7 = 0x5be0cd19;
	//Initialize array of round constants:
	//(first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311):
	unsigned int k[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
			    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
			    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
			    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
			    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
			    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
			    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
			    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
			};
	//Other variables used in SHA calculation
	int i;
	unsigned int a, b, c, d, e, f, g, h;
	unsigned int s0, s1;
	unsigned int S0, S1, temp1, temp2, ch, maj;

	//Message block
	unsigned int w[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			};

	//Pre-processing: Start the message page construction
	w[0] = (unsigned int)((iChallenge[1] << 16) + iChallenge[0]);
	w[1] = (unsigned int)((iChallenge[3] << 16) + iChallenge[2]);
	w[2] = (unsigned int)((iChallenge[5] << 16) + iChallenge[4]);
	w[3] = (unsigned int)((iChallenge[7] << 16) + iChallenge[6]);
	w[4] = (unsigned int)((iChallenge[9] << 16) + iChallenge[8]);
	w[5] = (unsigned int)((iSecret[1] << 16) + iSecret[0]);
	w[6] = (unsigned int)((iSecret[3] << 16) + iSecret[2]);
	w[7] = (unsigned int)((iSecret[5] << 16) + iSecret[4]);
	w[8] = (unsigned int)((iSecret[7] << 16) + iSecret[6]);
	w[9] = (unsigned int)((iSecret[9] << 16) + iSecret[8]);
	w[10] = (unsigned int)0xFFFFFFFF;
	w[11] = (unsigned int)0xFFFFFFFF;
	w[12] = (unsigned int)0x80000000;
	w[13] = (unsigned int)0x00000000;
	w[14] = (unsigned int)0x00000000;
	w[15] = (unsigned int)0x00000180;

	//Update ROMID information if it is used
	if (useROMID)
	{
		w[10] = (unsigned int)((iROMID[1] << 16) + iROMID[0]);
		w[11] = (unsigned int)((iROMID[3] << 16) + iROMID[2]);
	}
	//Fill out the rest of the message page
	for (i = 16; i <= 63; i++)
	{
		s0 = ((w[i - 15] >> 7) | (w[i - 15] << 25)) ^ ((w[i - 15] >> 18) | (w[i - 15] << 14)) ^ (w[i - 15] >> 3);
		s1 = ((w[i - 2] >> 17) | (w[i - 2] << 15)) ^ ((w[i - 2] >> 19) | (w[i - 2] << 13)) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}

	//Initialize working variables to current hash value:
	a = h0;
	b = h1;
	c = h2;
	d = h3;
	e = h4;
	f = h5;
	g = h6;
	h = h7;

	//Compression function main loop:
	for (i = 0; i <= 63; i++)
	{
		S1 = ((e >> 6) | (e << 26)) ^ ((e >> 11) | (e << 21)) ^ ((e >> 25) | (e << 7));
		ch = (e & f) ^ (~e & g);
		temp1 = h + S1 + ch + k[i] + w[i];
		S0 = ((a >> 2) | (a << 30)) ^ ((a >> 13) | (a << 19)) ^ ((a >> 22) | (a << 10));
		maj = (a & b) ^ (a & c) ^ (b & c);
		temp2 = S0 + maj;
		h = g;
		g = f;
		f = e;
		e = d + temp1;
		d = c;
		c = b;
		b = a;
		a = temp1 + temp2;
	}

	//Add the compressed chunk to the current hash value:
	h0 = h0 + a;
	h1 = h1 + b;
	h2 = h2 + c;
	h3 = h3 + d;
	h4 = h4 + e;
	h5 = h5 + f;
	h6 = h6 + g;
	h7 = h7 + h;

	//Store off results from Hash
	iMAC[0] = (int)h0 & 0xFFFF;
	iMAC[1] = ((int)h0 >> 16) & 0xFFFF;
	iMAC[2] = (int)h1 & 0xFFFF;
	iMAC[3] = ((int)h1 >> 16) & 0xFFFF;
	iMAC[4] = (int)h2 & 0xFFFF;
	iMAC[5] = ((int)h2 >> 16) & 0xFFFF;
	iMAC[6] = (int)h3 & 0xFFFF;
	iMAC[7] = ((int)h3 >> 16) & 0xFFFF;
	iMAC[8] = (int)h4 & 0xFFFF;
	iMAC[9] = ((int)h4 >> 16) & 0xFFFF;
	iMAC[10] = (int)h5 & 0xFFFF;
	iMAC[11] = ((int)h5 >> 16) & 0xFFFF;
	iMAC[12] = (int)h6 & 0xFFFF;
	iMAC[13] = ((int)h6 >> 16) & 0xFFFF;
	iMAC[14] = (int)h7 & 0xFFFF;
	iMAC[15] = ((int)h7 >> 16) & 0xFFFF;
}

//***********************************************************************************
//SetSecret
//This method sets the internal secret value to be used in the SHA hash operation
//***********************************************************************************
static void SetSecret(int * Secret)
{
	iSecret[0] = Secret[0];
	iSecret[1] = Secret[1];
	iSecret[2] = Secret[2];
	iSecret[3] = Secret[3];
	iSecret[4] = Secret[4];
	iSecret[5] = Secret[5];
	iSecret[6] = Secret[6];
	iSecret[7] = Secret[7];
	iSecret[8] = Secret[8];
	iSecret[9] = Secret[9];
}

//***********************************************************************************
//SetChallenge
//This method sets the internal challenge value to be used in the SHA hash operation
//***********************************************************************************
static void SetChallenge(int * Challenge)
{
	iChallenge[0] = Challenge[0];
	iChallenge[1] = Challenge[1];
	iChallenge[2] = Challenge[2];
	iChallenge[3] = Challenge[3];
	iChallenge[4] = Challenge[4];
	iChallenge[5] = Challenge[5];
	iChallenge[6] = Challenge[6];
	iChallenge[7] = Challenge[7];
	iChallenge[8] = Challenge[8];
	iChallenge[9] = Challenge[9];
}

//**********************************************************************************
//SetROMID
//This method sets the internal ROMID value to be used in the SHA hash operation
//***********************************************************************************
static void SetROMID(int * ROMID)
{
	iROMID[0] = ROMID[0];
	iROMID[1] = ROMID[1];
	iROMID[2] = ROMID[2];
	iROMID[3] = ROMID[3];
}

//***********************************************************************************
//ComputeMACWithROMID
//This method performs a SHA hash alogorithm using the IC's ROM ID and stores the
// result as a 16 word value in the MAC array that was passed to the function. The ROM ID, Secret,
// and Challenge values must be set prior to calling this function.
//***********************************************************************************
static void ComputeMACWithROMID(int * MAC)
{
	Hash(WithID);
	MAC[0] = iMAC[0];
	MAC[1] = iMAC[1];
	MAC[2] = iMAC[2];
	MAC[3] = iMAC[3];
	MAC[4] = iMAC[4];
	MAC[5] = iMAC[5];
	MAC[6] = iMAC[6];
	MAC[7] = iMAC[7];
	MAC[8] = iMAC[8];
	MAC[9] = iMAC[9];
	MAC[10] = iMAC[10];
	MAC[11] = iMAC[11];
	MAC[12] = iMAC[12];
	MAC[13] = iMAC[13];
	MAC[14] = iMAC[14];
	MAC[15] = iMAC[15];
}

//***********************************************************************************
//ComputeMACWithoutROMID
//This method performs a SHA hash alogorithm using all 1's instead of IC's ROM ID and stores the
// result as a 16 word value in the MAC array that was passed to the function. The Secret, and
// Challenge values must be set prior to calling this function.
//***********************************************************************************
static void ComputeMACWithoutROMID(int * MAC)
{
	Hash(WithoutID);
	MAC[0] = iMAC[0];
	MAC[1] = iMAC[1];
	MAC[2] = iMAC[2];
	MAC[3] = iMAC[3];
	MAC[4] = iMAC[4];
	MAC[5] = iMAC[5];
	MAC[6] = iMAC[6];
	MAC[7] = iMAC[7];
	MAC[8] = iMAC[8];
	MAC[9] = iMAC[9];
	MAC[10] = iMAC[10];
	MAC[11] = iMAC[11];
	MAC[12] = iMAC[12];
	MAC[13] = iMAC[13];
	MAC[14] = iMAC[14];
	MAC[15] = iMAC[15];
}

//***********************************************************************************
//ComputeNextSecretWithROMID
//This method performs a SHA hash alogorithm using the IC's ROM ID and stores the result as a
//10 word value in the NextSecret array that was passed to the function. The ROM ID, Secret, and
// Challenge values must be set prior to calling this function.
//***********************************************************************************
static void ComputeNextSecretWithROMID(int * NextSecret)
{
	Hash(WithID);
	NextSecret[0] = iMAC[6];
	NextSecret[1] = iMAC[7];
	NextSecret[2] = iMAC[8];
	NextSecret[3] = iMAC[9];
	NextSecret[4] = iMAC[10];
	NextSecret[5] = iMAC[11];
	NextSecret[6] = iMAC[12];
	NextSecret[7] = iMAC[13];
	NextSecret[8] = iMAC[14];
	NextSecret[9] = iMAC[15];
}

//*********************************************************************************** 
//ComputeNextSecretWithoutROMID
//This method performs a SHA hash alogorithm
// result as a 10 word value in the NextSecret array that was passed to the function. The Secret,
// and Challenge values must be set prior to calling this function.
//***********************************************************************************
static void ComputeNextSecretWithoutROMID(int * NextSecret)
{
	Hash(WithoutID);
	NextSecret[0] = iMAC[6];
	NextSecret[1] = iMAC[7];
	NextSecret[2] = iMAC[8];
	NextSecret[3] = iMAC[9];
	NextSecret[4] = iMAC[10];
	NextSecret[5] = iMAC[11];
	NextSecret[6] = iMAC[12];
	NextSecret[7] = iMAC[13];
	NextSecret[8] = iMAC[14];
	NextSecret[9] = iMAC[15];
}

int calcaute_SHA256(int * rom_id, unsigned char * challenge_data,unsigned char *key, unsigned int *result_digest32)
{
	int i;
	int set_challenge_data[CHALLENGE_BYTES/2 + 1] = {0};
	int set_secret_data[AUTHENTICATION_KEY_BYTES/2 + 1] = {0};
	int set_romid_data[ROMID_BYTES] = {0};
	int final_mac_result[MAC_RESULT_LEN] = {0};
	int next_mac_result[MAC_RESULT_LEN] = {0};

	if(key == NULL){
		key = DefaultAuthenticationKey;
	}

	for(i = 0; i < AUTHENTICATION_KEY_BYTES; i+=2) {
		set_secret_data[i/2] = key[i + 1] << 8 | key[i];
	}
	SetSecret(set_secret_data);

	for(i = 0; i < CHALLENGE_BYTES; i+=2) {
		set_challenge_data[i/2] = DefaultChallengeData[i + 1]<<8 | DefaultChallengeData[i];
	}
	SetChallenge(set_challenge_data);

	for(i = 0; i < ROMID_BYTES; i++) {
		set_romid_data[i] = *(rom_id + i);
	}

	SetROMID(set_romid_data);

	ComputeNextSecretWithROMID(next_mac_result);

	SetSecret(next_mac_result);

	for(i = 0; i < CHALLENGE_BYTES; i+=2) {
		set_challenge_data[i/2] = challenge_data[i + 1]<<8 | challenge_data[i];
	}
	SetChallenge(set_challenge_data);

	SetROMID(set_romid_data);

	ComputeMACWithROMID(final_mac_result);

	for(i = 0; i < MAC_RESULT_LEN; i+=2){
		result_digest32[i/2] = (unsigned int)final_mac_result[i] + (unsigned int)(final_mac_result[i + 1] << 16);
	}

	return 0;
}
