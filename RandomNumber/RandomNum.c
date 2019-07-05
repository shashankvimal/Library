#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "profile.h"

#define RANDOM_NUM(...)	((double)rand() / (double)(RAND_MAX))
#define M1              (2147483647)
#define M2 				(2147483399)
#define A1				(40015)
#define A2				(40692)
#define Q1				(M1/A1)
#define Q2				(M2/A2)
#define R1				(M1%A1)
#define R2				(M2%A2)

typedef struct
{
	int s1st;
	int s2nd;
}DP_LCG_SEED_t;

DP_LCG_SEED_t seeds = {1, 1};


/*
**
**
**
** 
*/
double Rng_randomNumber(double fudgeFactor)
{
	/*Form a seed using current time and user defined seed factor*/
	unsigned int seed = time(NULL) + fudgeFactor;
	
	/*Set the seed value for the random number generator*/
	srand(seed);
	return rand();
}

double Rng_randomNumberFromGivenRange(double lowerLimit, double upperLimit)
{
	ASSERT(lowerLimit < upperLimit, ERROR: Paramater Inverted!!!);
	srand(time(NULL));
	return (lowerLimit + (upperLimit - lowerLimit) * RANDOM_NUM(0,1));
}

double Rng_randomNumUpto(double upperLimit)
{
	ASSERT(upperLimit > 0, ERROR: Incorrect  Parameter!!!);
	
	return (upperLimit * RANDOM_NUM(0, 1));
}

double Rng_randomNumLtdByTwoConsecutiveNum(double firstNum)
{
	return (RANDOM_NUM(0,1) + firstNum);
}

double Rng_randomNumForGivenRange(double lowerLimit, double upperLimit)
{
	ASSERT(lowerLimit < upperLimit, ERROR: Paramater Inverted!!!);
	
	return(lowerLimit + (upperLimit - lowerLimit) * RANDOM_NUM(0, 1));
}

bool Rng_generateRandomBoolean(void)
{
	return floor(2 * RANDOM_NUM(0, 1));
}

static void Rng_initSeedValues(DP_LCG_SEED_t* pSeed_p)
{
	pSeed_p->s1st = A1 * (pSeed_p->s1st % Q1) - R1 * (pSeed_p->s1st / Q1);
	pSeed_p->s2nd = A2 * (pSeed_p->s2nd % Q2) - R2 * (pSeed_p->s2nd / Q2);
}

int Rng_dualPhaseLcgRandomNum(void)
{
	int result;
	
	Rng_initSeedValues(&seeds);
	
	if( seeds.s1st <= 0) seeds.s1st += M1;
	if( seeds.s2nd <= 0) seeds.s2nd += M2;
	
	result = (seeds.s1st - seeds.s2nd); if(result < 1) result += (M1 - 1);
	
	return result;
	
}

int main(int argc, char *argv[]) 
{
	
	unsigned char i;
	
	PROFILE_INIT();
	
	PROFILE_BEGIN();
	for(i = 0; i < 5; i++) printf("Random Number: %d\n", Rng_dualPhaseLcgRandomNum());
	PROFILE_END();
	
	PROFILE_SHOW_TIME_TAKEN();
	
	return 0;
}
