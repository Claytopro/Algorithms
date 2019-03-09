/*
runs other programs to test them.
*/

#include "stdio.h"
#include "stdlib.h"
#include "sys/timeb.h"
void printMenu();
int p11();
int p12();
int p21();
int p22();
int p23();

int main(int argc,char* argv[]){

  int choice =6;
  choice = atoi(argv[1]);


    switch (choice) {
      case 1:
      p11();
    break;
      case 2:

      p12();
    break;
      case 3:
      p21();

    break;
      case 4:

      p22();
    break;
      case 5:

      p23();
    break;

    default:
    printf("invalud number\n");
    }

  return 1;
}

void printMenu(){
  printf("1:run brute force anagram\n");
  printf("2:run presorting anagram\n");
  printf("3:run brute force string searching \n");
  printf("4:run Horspool's algorithm for string searching\n");
  printf("5:run Boyer-Moore's alrgorithm for string searching\n");
  printf("6:exit\n");
}
