/*
brute force algorithm for convex hull
side of line formula from hhttps://math.stackexchange.com/questions/274712/calculate-on-which-side-of-a-straight-line-is-a-given-point-located
*/

#include "stdio.h"
#include "sys/timeb.h"

int extreme(double x,double x1, double x2,double y, double y1, double y2);

int main(){
  FILE *fp;
  struct timeb t_start, t_end;
  int count,i,j,l;
  int timeElapsed,lineSide,points;
  double x,x1,x2,y,y1,y2,checkedVal;
  double array[30000][2];



  fp=fopen("data_2.txt","r");
  for(i=0; i<30000; i++){
    for(j=0;j<2;j++){
      fscanf(fp,"%lf",&array[i][j]);
    }
  }
/*
  for(i=0; i<30000; i++){
    for(j=0;j<2;j++){
      printf("%.2f ",array[i][j]);
    }
    printf("\n");
  }
*/

  ftime(&t_start);

  for(i=0; i<30000;i++){
    for(j=0;j<30000;j++){
      if(i==j){
        continue;
      }
      lineSide =0;
      //compare a point in array to all other combinations of points.
      x1=array[i][0];
      y1=array[i][1];

      x2=array[j][0];
      y2=array[j][1];

      for(l=0;l<30000;l++){
        //get points
        x= array[l][0];
        y= array[l][1];

        //take equation from text book;
        //ax + by = c
        //a = y2 − y1 , b = x1−x2 , c = x1y2 − y1x2 .
        //checkedVal = ((x*(y2-y1)) + (y*(x1-x2)) ) - ((x1*y2) - (y1*x2));
        checkedVal = ((x-x1)*(y2-y1)) - ((y-y1)*(x2-x1));



        //all points must be on one side of the line
        if(checkedVal > 0){
          //all points must be on one side of the line
          if(lineSide == -1){
            break;
          }
          lineSide=1;
        }

        //point is negative
        if(checkedVal < 0){
          //if points exist that are on othe side of line it is not an extreme point
          if(lineSide ==1){
            break;
          }
          lineSide = -1;
        }

        if(checkedVal == 0){
          //check if value is a vertex point IE: extreme point
          if(extreme(x,x1,x2,y,y1,y2)){
            break;
          }
        }

      }


      if(l == 30000 && lineSide !=0){
        printf("i:%d j:%d  ",i,j );
        printf("x:%f at y:%f\n",x1,y1 );
        points++;
        i++;
        j++;
      }

    }
  }

  ftime(&t_end);
  timeElapsed = (int)(1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm));
  printf("points : %d, in %d milliseconds\n",points,timeElapsed);

  fclose(fp);
  return 1;
}

int extreme(double x,double x1, double x2,double y, double y1, double y2){
  if ((x < x1 && x > x2) || (x > x1 && x > x2) || (y < y1 && y < y2) || (y > y1 && y > y2)){
    return 1;
  }
  return 0;
}
