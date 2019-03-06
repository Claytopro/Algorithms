/*
runs other programs to test them.
*/

#include "stdio.h"
#include "sys/timeb.h"

int main(){
/*
  FILE *fp;
  struct timeb t_start, t_end;
  int in,count,i=0;
  float timeElapsed;
  int array1[50000];

  fp=fopen("data_1.txt","r");
  while(i<50000 && (in = fscanf(fp,"%d", &array1[i++]))==1);

  i=0;
  while(i<50000){
    printf("%d\n",array1[i] );
    i++;
  }
  printf("i == %d\n",i );

  ftime(&t_start);
  count = bruteForceInversions(array1,50000);
  ftime(&t_end);
  timeElapsed = (int)(1000.0(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm));

  printf("brute force:%d , took %d milliseconds\n",count,timeElapsed);

  mergeSort(array1,0,50000-1);

  printf("recursive:%d\n",);
*/

  return 1;
}
