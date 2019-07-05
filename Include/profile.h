#ifndef __PROFILE_H__
#define __PROFILE_H__
#include <time.h>

	
#define PROFILE_BEGIN()\
do{\
	if(((startTime = clock()) == -1))\
	{\
		printf("clock returned error!!!\n"); exit(0);\
	}\
}while(0)
#define PROFILE_END()\
do{\
	if(((stopTime = clock()) == -1))\
	{\
		printf("clock returned error!!!\n"); exit(0);\
	}\
}while(0)

#define PROFILE_SHOW_TIME_TAKEN()	printf("%6.3f seconds elapsed\n",(double)(stopTime - startTime)/CLOCKS_PER_SEC)

#define PROFILE_INIT()	clock_t startTime, stopTime;


#endif /*__PROFILE_H__*/
