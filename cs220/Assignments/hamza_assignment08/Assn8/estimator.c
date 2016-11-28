#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>


extern void many_nop();
extern void a_ret();

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1){
	long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
	result->tv_sec = diff / 1000000;
	result->tv_usec = diff % 1000000;

       	return (diff<0);
}	
int main(){
	struct timeval tvDiff, tvStart, tvEnd;
	unsigned int i,j;
	unsigned long sumRet = 0, sumNop = 0, HUGE_NUMBER = 0xfffffff;
	long double avgRet, avgNop, diffTime, nopsPerMicroSecond, nopsPerSecond;
	for(i=0; i < 10; i++){
		gettimeofday(&tvStart, NULL);
		for(j=0; j < HUGE_NUMBER; j++){
	 		a_ret();
		}
		gettimeofday(&tvEnd, NULL);
		timeval_subtract(&tvDiff, &tvEnd, &tvStart);
		sumRet += (tvDiff.tv_sec * 1000000)  + tvDiff.tv_usec; 
	}
	for(i=0;i<10;i++){
	       	gettimeofday(&tvStart, NULL);
		for(i=0; i < HUGE_NUMBER ; i++){
			many_nop();
		}
	        gettimeofday(&tvEnd, NULL);
	        timeval_subtract(&tvDiff, &tvEnd, &tvStart);
                sumNop += (tvDiff.tv_sec * 1000000)  + tvDiff.tv_usec;      

	}

	avgRet = ((double) sumRet)/ 10;
	avgNop = ((double) sumNop )/ 10;	
	diffTime = avgNop - avgRet;
	nopsPerMicroSecond = ((unsigned long)(HUGE_NUMBER * 100))/diffTime;
	nopsPerSecond = nopsPerMicroSecond * 1000000;
	printf("%u\n", nopsPerSecond);





	return 0;
}
