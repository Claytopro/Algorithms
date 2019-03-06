/*


*/

#include "stdio.h"
#include "sys/timeb.h"

int merge(int arr[], int l, int m, int r);
int mergeSort(int arr[], int l, int r);

int main(){
  FILE *fp;
  struct timeb t_start, t_end;
  int in,count,i=0;
  int timeElapsed;
  int array1[50000];

  fp=fopen("data_1.txt","r");
  while(i<50000 && (in = fscanf(fp,"%d", &array1[i++]))==1);


  ftime(&t_start);
  count = mergeSort(array1,0,50000-1);
  ftime(&t_end);
  timeElapsed = (int)(1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm));

  printf("Recursive:%d , took %d milliseconds\n",count,timeElapsed);

  return 1;
}

int merge(int arr[], int l, int m, int r)
{
    int i, j, k,count;
    int n1 = m - l + 1;
    int n2 =  r - m;
    count =0;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
            //L[i] > R[j]
            count += (n1 -i);
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    return count;
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
int mergeSort(int arr[], int l, int r)
{
  int m;
  int count=0;
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        m = l+(r-l)/2;

        // Sort first and second halves
        count = mergeSort(arr, l, m);
        count += mergeSort(arr, m+1, r);

        count += merge(arr, l, m, r);
    }
    return count;
}
