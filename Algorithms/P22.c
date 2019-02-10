/*\
quick sort convex hull
based on textbook pg195 to pg197
https://math.stackexchange.com/questions/274712/calculate-on-which-side-of-a-straight-line-is-a-given-point-located


*/



#include "stdio.h"
#include "sys/timeb.h"
#include "math.h"

int findHull(double Section[30000][2],int sectionLength, double pointOne[1][2],double pointTwo[1][2] );
int QuickHull(double array[30000][2]);


int main(){
  FILE *fp;
  struct timeb t_start, t_end;
  int i,j,count;
  int timeElapsed,points;

  double array[30000][2];
  points =0;


  fp=fopen("data_2.txt","r");
  for(i=0; i<30000; i++){
    for(j=0;j<2;j++){
      fscanf(fp,"%lf",&array[i][j]);
    }
  }


  ftime(&t_start);
  points = QuickHull(array);


  ftime(&t_end);
  timeElapsed = (int)(1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm));
  printf("points : %d, in %d milliseconds\n",points,timeElapsed);

  fclose(fp);

  return 1;
}


int QuickHull(double array[30000][2]){
  int i,r,l,points=0;
  double side;
  double x,x1,x2,y,y1,y2;

  double leftArray[30000][2];
  double rightArray[30000][2];

  double leftMost[1][2];
  double rightMost[1][2];

  //initilize arrays to something
  leftMost[0][0]=array[0][0];
  leftMost[0][1]=array[0][1];

  rightMost[0][0]=array[0][0];
  rightMost[0][1]=array[0][1];


  //find left and right most points of x axis
  for(i=0;i<30000;i++){
      if(array[i][0]<leftMost[0][0]){
        leftMost[0][0] = array[i][0];
        leftMost[0][1] = array[i][1];
      }
      if(array[i][0]>rightMost[0][0]){
        rightMost[0][0] = array[i][0];
        rightMost[0][1] = array[i][1];
      }
  }

  //right most and left most points makes segement that divides the rest of points into two sides
  x1 = leftMost[0][0];
  y1 = leftMost[0][1];

  x2 = rightMost[0][0];
  y2 = rightMost[0][1];
  r=l=0;

  for(i=0; i<30000; i++){
    //distance=(x−x1)(y2−y1)−(y−y1)(x2−x1)
    //if its negative or postive indicates side
    x= array[i][0];
    y= array[i][1];
    side = ((x-x1)*(y2-y1)) - ((y-y1)*(x2-x1));

    if(side >0){
      rightArray[r][0] = array[i][0];
      rightArray[r][1] = array[i][1];
      r++;
    }

    if(side <0){
      leftArray[l][0] = array[i][0];
      leftArray[l][1] = array[i][1];
      l++;
    }


  }
  points =2;
  printf("x:%lf,y:%lf\n",leftMost[0][0],leftMost[0][1] );
  printf("x:%lf,y:%lf\n",rightMost[0][0],rightMost[0][1] );

  points += findHull(rightArray,r,leftMost,rightMost);
  points += findHull(leftArray,l,rightMost,leftMost);



  return points;
}


int findHull(double section[30000][2],int sectionLength, double pointOne[1][2],double pointTwo[1][2] ){
  double furthestPoint[1][2];

  double s1[30000][2];
  double s2[30000][2];


  double x,x1,x2,y,y1,y2;
  double greatestDistance,lineDistance;
  int i, s1Length,s2Length, points;
  //printf("right most x %lf , y:%lf , section length :%d\n",pointOne[0][0],pointOne[0][1],sectionLength );

  if(sectionLength ==0){
    return 0;
  }
  points =0;


  //ininitlize points
  furthestPoint[0][0] = section[0][0];
  furthestPoint[0][1] = section[0][1];

  x1 = pointOne[0][0];
  y1 = pointOne[0][1];

  x2 = pointTwo[0][0];
  y2 = pointTwo[0][1];

  greatestDistance =0;
  lineDistance =0;
  s1Length=0;
  s2Length=0;
//  printf("x:%lf,y:%lf\n",furthestPoint[0][0],furthestPoint[0][1]);

  //finds point furthest from pointOne pointtwo line
  for(i =0; i<sectionLength; i++){
    x = section[i][0];
    y = section[i][1];

    //distance=(x−x1)(y2−y1)−(y−y1)(x2−x1)

    lineDistance = (((x-x1)*(y2-y1)) - ((y-y1)*(x2-x1)));
    if(lineDistance >= greatestDistance){
      greatestDistance = lineDistance;
      furthestPoint[0][0] = section[i][0];
      furthestPoint[0][1] = section[i][1];
    }

  }


  //get all points to right of PC and CQ


  for(i=0;i<sectionLength;i++){
    x = section[i][0];
    y = section[i][1];
    //for line pointOne to furthestPoint
    x1 = pointOne[0][0];
    y1 = pointOne[0][1];

    x2 = furthestPoint[0][0];
    y2 = furthestPoint[0][1];

    lineDistance = (((x-x1)*(y2-y1)) - ((y-y1)*(x2-x1)));

    //if linedistacne isgreater than 0 its on right side of line
    if(lineDistance>0){
       s1[s1Length][0] = section[i][0];
       s1[s1Length][1] = section[i][1];
       s1Length++;
    }

    //the do the same for CQ line
    x1 = furthestPoint[0][0];
    y1 = furthestPoint[0][1];

    x2 = pointTwo[0][0];
    y2 = pointTwo[0][1];

    lineDistance = (((x-x1)*(y2-y1)) - ((y-y1)*(x2-x1)));

    if(lineDistance>0){
       s2[s2Length][0] = section[i][0];
       s2[s2Length][1] = section[i][1];
       s2Length++;
    }

  }
  //printf("s1 len :%d\n",s1Length );
  //printf("s2 len: %d\n",s2Length );
 points =1;
 printf("x:%.2lf,y:%.2lf\n",furthestPoint[0][0],furthestPoint[0][1]);
 points += findHull(s1,s1Length,pointOne,furthestPoint);
 points += findHull(s2,s2Length,furthestPoint,pointTwo);

 return points;
}
