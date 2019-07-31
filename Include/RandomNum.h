#ifndef __RANDOMNUM_H__
#define __RANDOMNUM_H__
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
double Rng_randomNumber(double fudgeFactor);
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
double Rng_randomNumberFromGivenRange(double lowerLimit, double upperLimit);
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
double Rng_randomNumUpto(double upperLimit);
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
double Rng_randomNumLtdByTwoConsecutiveNum(double firstNum);
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
double Rng_randomNumForGivenRange(double lowerLimit, double upperLimit);
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
bool Rng_generateRandomBoolean(void);
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
int Rng_dualPhaseLcgRandomNum(void);
/* *********************************************************************************
** Function: Rng_mersenneTwister
**
** Description: This function generates random number with better randomness properties
**          
**
** Input: None
** 
** Output: Random number 
**
** Remarks:
************************************************************************************/
unsigned long Rng_mersenneTwisterRandomNum();
#endif
