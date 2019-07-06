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


/* *********************************************************************************
** Function: Rng_randomNumber
**
** Description: Generates random number in floating format,
**              based on rand() and srand() std c-lib callls.
**              It uses sum of current system time and user defined fudgeFactor.
**              fudgeFactor is to improve randomness 
**
** Input: User defined seed value
** 
** Output: Random number 
**
** Remarks:
************************************************************************************/
double Rng_randomNumber(double fudgeFactor)
{
	/*Form a seed using current time and user defined seed factor*/
	unsigned int seed = time(NULL) + fudgeFactor;
	
	/*Set the seed value for the random number generator*/
	srand(seed);
	return rand();
}
/* *********************************************************************************
** Function: Rng_randomNumberFromGivenRange
**
** Description: Generates random number in floating format,
** based on rand() and srand() std c-lib callls.
** The generated random number is within the user defined range. 
**
** Input: lowerLimit-> Lower value of range of random number
**        upperLimit-> Upper value of range of random number
** 
** Output: Random number 
**
** Remarks:
************************************************************************************/
double Rng_randomNumberFromGivenRange(double lowerLimit, double upperLimit)
{
	ASSERT(lowerLimit < upperLimit, ERROR: Paramater Inverted!!!);
	srand(time(NULL));
	return (lowerLimit + (upperLimit - lowerLimit) * RANDOM_NUM(0,1));
}
/* *********************************************************************************
** Function: Rng_randomNumUpto
**
** Description: Generates random number in floating format,
** 				based on rand() and srand() std c-lib callls.
** 				It uses a given number as end point of the range for random number.
**              i.e. the generated random number will always be less than the user
**              defined limit. 
**
** Input: User defined upper limit
** 
** Output: Random number 
**
** Remarks:
************************************************************************************/
double Rng_randomNumUpto(double upperLimit)
{
	ASSERT(upperLimit > 0, ERROR: Incorrect  Parameter!!!);
	
	return (upperLimit * RANDOM_NUM(0, 1));
}
/* *********************************************************************************
** Function: Rng_randomNumLtdByTwoConsecutiveNum
**
** Description: Generates random number in floating format,
**              based on rand() and srand() std c-lib callls.
**              It uses a given number as starting point of a range and treats the
**              next subsequent number as end point of the range.  
**
** Input: The starting point of the number.
** 
** Output: Random number 
**
** Remarks:
************************************************************************************/
double Rng_randomNumLtdByTwoConsecutiveNum(double firstNum)
{
	return (RANDOM_NUM(0,1) + firstNum);
}
/* *********************************************************************************
** Function: Rng_randomNumForGivenRange
**
** Description: Generates random number for a given range. User of this API shall
**              must make sure that the lower limit of the range is smaller than 
**              the upper limit. 
**
** Input: lowerLimit-> start point of the range.
**        upperLimit-> end point of the range.
** 
** Output: Random number 
**
** Remarks: If lowerlimit is greater than upper limit in that case program will exit.
************************************************************************************/
double Rng_randomNumForGivenRange(double lowerLimit, double upperLimit)
{
	ASSERT(lowerLimit < upperLimit, ERROR: Paramater Inverted!!!);
	
	return(lowerLimit + (upperLimit - lowerLimit) * RANDOM_NUM(0, 1));
}
/* *********************************************************************************
** Function: Rng_generateRandomBoolean
**
** Description: This function generates 1 and 0 randomly. This function uses c-lib 
**              APIs.
** 
** Input: None
** 
** Output: 1 or 0 
**
** Remarks:
************************************************************************************/
bool Rng_generateRandomBoolean(void)
{
	return floor(2 * RANDOM_NUM(0, 1));
}
/* *********************************************************************************
** Function: Rng_initSeedValues
**
** Description: Initializes both the seed values for dual phase linear congruential
**              random number generator. This function has file scope.        
**
** Input: pointer to the seed values structure
** 
** Output: None
**
** Remarks:
************************************************************************************/
static void Rng_initSeedValues(DP_LCG_SEED_t* pSeed_p)
{
	pSeed_p->s1st = A1 * (pSeed_p->s1st % Q1) - R1 * (pSeed_p->s1st / Q1);
	pSeed_p->s2nd = A2 * (pSeed_p->s2nd % Q2) - R2 * (pSeed_p->s2nd / Q2);
}
/* *********************************************************************************
** Function: Rng_dualPhaseLcgRandomNum
**
** Description: This function uses two seed values based on predetermined 
**              natural numbers. This function does not depend on c-library APIs.
**
** Input: None
** 
** Output: Random number 
**
** Remarks:
************************************************************************************/
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
