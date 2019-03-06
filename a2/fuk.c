

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>
#include <sys/timeb.h>


int main() {
  FILE *file;
  char * fileName = malloc(200 * sizeof(char));

  file = fopen("data_2.txt", "r");
  struct timeb start, end;
  int numberOfPoints = 0;
  double numbers[2][30000];
  for (int i = 0; i < 30000; i++) {
    for (int j = 0; j < 2; j++) {
      fscanf(file, "%lf", &numbers[j][i]);
    }
  }

  // start time
  ftime(&start);

  for (int i = 0; i < 30000; i++) {
    for (int j = 0; j < 30000; j++) {
      int side = 0;
      for (int k = 0; k < 30000; k++) {

        double a, b, c, d, value;

        double x = numbers[0][k];
        double x1 = numbers[0][i];
        double x2 = numbers[0][j];
        double y = numbers[1][k];
        double y1 = numbers[1][i];
        double y2 = numbers[1][j];

        a = numbers[0][k] - numbers[0][i]; // x - x1
        b = numbers[1][j] - numbers[1][i]; // y2 - y1
        c = numbers[1][k] - numbers[1][i]; // y - y1
        d = numbers[0][j] - numbers[0][i]; // x2 - x1



        value = (a * b) - (c * d);

        if (value > 0) {
          if (side == -1) { // detected point on wrong side, skip point
            break;
          }
          side = 1;
        }
        if (value < 0) {
          if (side == 1) { // detected point on wrong side, skip point
            break;
          }
          side = -1;
        }

        // check if extreme
        if (value == 0) {
          if ((x > x1 && x > x2) || (x < x1 && x > x2) || (y < y1 && y < y2) || (y > y1 && y > y2)){
            break;
          }
        }

        if (k == 29999) { // every point successfull
          if (side != 0) {
            if (i != j) {
              numberOfPoints++;
              printf("i:%d j:%d k:%d\n",i,j,k );
              printf("(%.1f,%.1f)\n", numbers[0][i], numbers[1][i]);
              j++;
              i++;
            }
          }
        }
      }
    }
  }
  // end time
  ftime(&end);
  int diff1 =
      (int)(1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
  printf("Number of points: %d\n", numberOfPoints);
  printf("Execution time was %d milliseconds\n", diff1);
  return 1;
}
