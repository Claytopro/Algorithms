/*
By:Clayton Provan
Assignement 4 part 1
march 24th
*/

#include "stdio.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
struct used to represent a process,has some redundant properties but makes it easier to read and follow
*/
typedef struct treeNode{
  char* key;
  float val;

  struct treeNode *left;
  struct treeNode *right;
} Node;


Node* createTREE(char ** keys,float** C,float** R, int i,int j);
Node* initlizeNode(char* key);
void findNode(char *toFind,Node *root);


static int myCompare(const void* a, const void* b);
const float MAX_VAL = 3.40282 * 1000000;

int main(){
  FILE *fp;
  char *tempStr = malloc(sizeof(char)*1000);
  char *searchStr  = malloc(sizeof(char)*1000);
  char **str;
  char **keys;
  char *key;

  Node *root = malloc(sizeof(Node));

  int i=0;
  int j=0;
  int k=0;
  int n=0;
  int d=0;

  float** C;
  float** R;
  float *freq;
  int count=0;
  float minval=0;
  float kMin =0;
  int s =0;
  float sum=0;


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

  n=k;

  C = malloc((n+2 )* sizeof(float*));
  for(i = 0; i < n+2; i++)
  {
      C[i] = malloc((n+2)*sizeof(float));
      for (j = 0; j < n+2; j++)
      {
        C[i][j] = 0;
      }
  }
  R = malloc((n+2 ) * sizeof(float*));
  for(i = 0; i < (n+2 ); i++)
  {
      R[i] = malloc((n+2 )*sizeof(float));
      for (j = 0; j <(n+2 ); j++)
      {
        R[i][j] = 0;
      }
  }


  //find optimatBST
  for(i=1;i<=n;i++){
    C[i][i-1] = 0;
    C[i][i] = freq[i];
    R[i][i] = i;
  }
  C[n+1][n] = 0;
  for(d=1;d<=n-1;d++){
    for(i=1;i<= n-d;i++){
      j=i+d;
      minval = MAX_VAL;
      for(k=i;k<=j;k++){
        if(C[i][k-1] + C[k+1][j] < minval){
          minval = C[i][k-1] + C[k+1][j];
          kMin =k;
        }
      }
      R[i][j] = kMin;
      sum = freq[i];
      for(s= i+1;s<=j;s++){
        sum = sum + freq[s];
      }
      C[i][j] = minval + sum;
    }
  }

//make binary tree
  root = createTREE(keys,C,R,1,n);

  printf("Enter a key: ");
  fgets(searchStr, sizeof(char)*1001, stdin);
  searchStr[strcspn(searchStr, "\n")] = 0;

  findNode(searchStr,root);

/*
  FREE ALL MEMEORY USED IN FIDNING AND CREATION OF BINARY TREE.
*/
  free(searchStr);
  free(freq);
  for(j=0;j<n+2;j++){
    free(C[j]);
  }
  free(C);

  for(j=0;j<n+2;j++){
    free(R[j]);
  }
  free(R);
  for(j=0;j<k;j++){
    free(keys[j]);
  }
  free(keys);

fclose(fp);
return 1;
}

static int myCompare(const void* a, const void* b){
    return strcmp(*(const char**)a, *(const char**)b);
}

//create binary tree
Node* createTREE(char ** keys,float** C,float** R, int i,int j){
  Node *temp =NULL;
  float k;
  if(i<=j){
    k = R[i][j];

    temp = initlizeNode(keys[(int)k]);
    temp->val = C[i][j];
    temp->left = createTREE(keys,C,R, i,k-1);
    temp->right = createTREE(keys,C,R,k+1,j);
  }
  return temp;
}

//initilize nodes with given keys
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
    printf("compared with %s (%.3f),found\n",root->key,root->val);
  }else if(strcmp(toFind,root->key)<0){
    printf("compared with %s (%.3f),go left subtree\n",root->key,root->val);
    findNode(toFind,root->left);
  }else if(strcmp(toFind,root->key)>0){
    printf("compared with %s (%.3f),go right subtree\n",root->key,root->val);
    findNode(toFind,root->right);
  }

}
