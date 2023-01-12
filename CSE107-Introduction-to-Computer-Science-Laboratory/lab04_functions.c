#include <stdio.h>
#include <time.h>

int main()
{
  srand(time(NULL));
  
  int i,j,numbers[100];
  int count[10];
  
  
  for(i=0;i<100;i++)  
  numbers[i] = rand()%11;
    
   
   for(i = 0; i<10;i++){
     printf("%d --> %d \n",i,findNumberOfx(i,numbers,100));
   }
       


  for(j=1,i =0;i<10;i++,j++){
    count[i] = findNumberOfx(i,numbers,100);
  }
   
   printf("The mode is %d",findMode(numbers,100));
        return 0;
}


//This function finds the mode of an array with n elements.


int findMode(int arr[], int n){
  
  int mod,b, i, j;
    mod = b = 0;
    
   for (i = 0; i < n; ++i) {
      int c = 0;
      
      for (j = 0; j < n; ++j) {
         if (arr[j] == arr[i])
         ++c;
      }
      
      if (c > b ) {
         b = c;
         mod = arr[i];
      }
   }

   return mod;
}

//This function finds how many x are in an array with n elements.

int findNumberOfx(int x,int arr[],int n){
  
  int i;
  int flag=0;
  
for(i=0; i<100; i++){
    if(x == arr[i]){
    flag++;
  }
 }
 return flag;
}

//This function finds the maximum element of an array with 10 elements.


int findMax(int arr[]){
   int i, max = 0;
   
   for( i=0;i<10;i++){
     if(max < arr[i]){
       max = arr[i];
     }
  
   }
   return max;
  }
