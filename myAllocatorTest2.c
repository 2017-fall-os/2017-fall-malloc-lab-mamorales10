#include "stdio.h"
#include "stdlib.h"
#include "myAllocator.h"
#include "sys/time.h"
#include <sys/resource.h>
#include <unistd.h>

double diffTimeval(struct timeval *t1, struct timeval *t2) {
  double d = (t1->tv_sec - t2->tv_sec) + (1.0e-6 * (t1->tv_usec - t2->tv_usec));
  return d;
}

void getutime(struct timeval *t)
{
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  *t = usage.ru_utime;
}

int main() 
{
  void *p1, *p2, *p3, *p4, *p5;
  arenaCheck();

  /*Allocating space for p1-p5 to start test cases*/
  p1 = bestFitAllocRegion(250);
  arenaCheck();
  p2 = bestFitAllocRegion(3000);
  arenaCheck();
  p3 = bestFitAllocRegion(100);
  arenaCheck();
  p4 = bestFitAllocRegion(5000);
  arenaCheck();
  p5 = bestFitAllocRegion(2048);
  arenaCheck();

  /**** Best fit testing starts here ****/
  freeRegion(p1);
  freeRegion(p3);
  arenaCheck();
  
  /*Checking if p1 is allocated to the perfectly fitting block*/
  p1 = bestFitAllocRegion(104); 
  arenaCheck();
  freeRegion(p2);
  arenaCheck();
  
  /*Checking if p3 is indeed allocated to best fitting block*/
  p3 = bestFitAllocRegion(1020);
  arenaCheck();
  /**** Best fit testing ends here ****/

  /**** Improved resizeRegion testing starts here ****/

  /*Checking if the function will use the free space from the successor block*/
  p3 = resizeRegion(p3, 1025); 
  arenaCheck();

  /*Checking if the function will perform correctly with a successor block that is already allocated*/
  p1 = resizeRegion(p1, 106); 
  arenaCheck();
  
  /*Freeing all regions except for first in arena for the next test*/
  freeRegion(p1);
  freeRegion(p4);
  freeRegion(p5);
  arenaCheck();
  
  /*Checking if the function will only reallocated the necessary amount of space*/
  p3 = resizeRegion(p3, 10001); 
  arenaCheck();

  /**** Improved resizeRegion testing ends here ****/
  
  {				/* measure time for 10000 mallocs */
    struct timeval t1, t2;
    int i;
    getutime(&t1);
    for(i = 0; i < 10000; i++)
      if (bestFitAllocRegion(4) == 0) 
	break;
    getutime(&t2);
    printf("%d bestFitAllocRegion(4) required %f seconds\n", i, diffTimeval(&t2, &t1));
  }
  return 0;
}
