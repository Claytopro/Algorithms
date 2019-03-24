/*
By:Clayton Provan
Assignement 4 part 1
march 24th
*/

#include "stdio.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Node *greedyCreateTree();

typedef struct treeNode{
  char* key;

  //the minimum average number of comparisons of the subtree
  float val;

  struct treeNode *left;
  struct treeNode *right;
} Node;

static int myCompare(const void* a, const void* b);

Node* initlizeNode(char* key);
void findNode(char *toFind,Node *root);
Node* greedyCreateTree(char ** keys,float* R, int i,int j);

int main(){
  FILE *fp;
  char *tempStr = malloc(sizeof(char)*1000);
  char *searchStr  = malloc(sizeof(char)*1000);
  char **str;
  char **keys;
  char *key;

  Node *root;

  int i=0;
  int j=0;
  int k=0;
  int count=0;

  float *freq;




  fp=fopen("data_7.txt","r");
  str =calloc(1000000,sizeof(char*));

  while( fscanf(fp, "%s", tempStr) != EOF )
  {
    str[i] = calloc(1,sizeof(char)*strlen(tempStr)+1);
    strcpy(str[i],tempStr);
    i++;
  }
  free(tempStr);

  qsort(str, i, sizeof(const char*), myCompare);


  //turn sorted list into list of frequencies and keys.
  keys = calloc(i+2,sizeof(char*));
  freq = malloc(sizeof(float)*(i+2));
  k=0;
  /*
  CREATE ARRAYS OF FREQUENCY AND OF UNIQUE KEYS
  */
  while(j<i){
    key = str[j];

    while(j<i && strcmp(str[j],key)==0){
      count++;
      j++;
    }

    keys[k+1] = calloc(1,sizeof(char)*strlen(key)+1);
    strcpy(keys[k+1],key);

    freq[k+1] = (float)count/i;
    k++;
    count =0;
  }

  /*
  FREE ALL STRINGS INSIDE READ IN STRING ARRAY.
  */
  for(j=0;j<i;j++){
    free(str[j]);
  }
  free(str);


  root = greedyCreateTree(keys,freq,1,k);


  printf("Enter a key: ");
  fgets(searchStr, sizeof(char)*1001, stdin);
  searchStr[strcspn(searchStr, "\n")] = 0;

  findNode(searchStr,root);

/*
  FREE ALL MEMEORY USED IN FIDNING AND CREATION OF BINARY TREE.
*/
  free(searchStr);
  free(freq);
  for(j=0;j<k;j++){
    free(keys[j]);
  }
  free(keys);

return 1;
}


/*
create a binary tree with the input by a greedy technique
where we will select the key with the greatest freqency to be the sub node
and then recursively find the next node in the array within the bounds
to find the next greatest frequency and create the leafs.
*/

Node* greedyCreateTree(char ** keys,float* R, int i,int j){
  Node *temp =NULL;
  int a=0;
  float max=0;
  int maxIndex;

  if(i<=j){
    maxIndex =i;
    max = R[i];
    //find highest frequency
    for(a=i+1;a<j;a++){
      if(R[a] > max){
        maxIndex=a;
        max = R[a];
      }
    }

    temp = initlizeNode(keys[maxIndex]);
    temp->val =  R[maxIndex];


    temp->left = greedyCreateTree(keys,R, i,maxIndex-1);
    temp->right = greedyCreateTree(keys,R,maxIndex+1,j);
  }
  return temp;
}



Node* initlizeNode(char* key){
  Node* temp = malloc(sizeof(Node));
  int len = strlen(key) +1;
  temp->key = malloc(sizeof(char)*len);
  strcpy(temp->key,key);

  temp->left = NULL;
  temp->right = NULL;

  return temp;
}

void findNode(char *toFind,Node *root){
  if(root == NULL){
    printf("Not found.\n");
    return;
  }
  //node is found.
  if(strcmp(toFind,root->key)==0){
    printf("compared with %s (%.5f),found\n",root->key,root->val);
  }else if(strcmp(toFind,root->key)<0){
    printf("compared with %s (%.5f),go left subtree\n",root->key,root->val);
    findNode(toFind,root->left);
  }else if(strcmp(toFind,root->key)>0){
    printf("compared with %s (%.5f),go right subtree\n",root->key,root->val);
    findNode(toFind,root->right);
  }

}

static int myCompare(const void* a, const void* b){
    return strcmp(*(const char**)a, *(const char**)b);
}
