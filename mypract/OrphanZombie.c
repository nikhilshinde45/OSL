#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>


//ascending
void insertion_sort(int *arr,int n){
  for(int i=0;i<n;i++){
     int temp=arr[i];
     int j=i-1;
     while(j>=0&&arr[j]>temp){
      arr[j+1]=arr[j];
      j--;
     }
     arr[j+1]=temp;
  }
}

//descending
void selection_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;  // assume current element is largest
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[max_idx]) {
                max_idx = j;  // update index of largest
            }
        }
        // swap only once per i
        if (max_idx != i) {
            int temp = arr[i];
            arr[i] = arr[max_idx];
            arr[max_idx] = temp;
        }
    }
}


//display array
void display_array(int *arr,int n){
   for(int i=0;i<n;i++){
     printf("%d",arr[i]);
   }
   printf("\n");
}

int main(){
      int choice;
      printf("1:Simulate Child process\n2.Simulate Orphan Process\n3.Simulate Zombie Process\n");
      printf("Enter your choice:");
      scanf("%d",&choice);
      pid_t p;
      switch(choice){ 
            case 1:
            printf("==========Starting the main program=============\n");
            printf("Process Id: %d",getpid());
            int n;
            printf("Enter the elements in the array:\n");
            scanf("%d",&n);
            int *arr = (int*)calloc(n,sizeof(int));
            for(int i=0;i<n;i++){
               scanf("%d",&arr[i]);
            }
            p=fork();
            
            if(p==-1){
              printf("Error in creating the child process\n");
            }else if(p==0){
              printf("===========In Child Process=========\n");
              printf("Child Process Id:%d",getpid());
              printf("Parent Process Id:%d",getppid());
              printf("Child Process sorting the array using insertion sort\n");
              // insertion_sort(arr,n);
              // display_array(arr,n);
              printf("Sorting is done by child process\n");
              printf("===========Child Process Done=========\n");
              _exit(-1);

            }else{
              printf("=======In Parent Process=======\n");
              printf("Parent Process Id:%d",getpid());
              printf("Parent wait to sort the array by child process first\n");
              wait(0);
              printf("Parent sorts the array using the selection sort\n");
              // selection_sort(arr,n);
              // display_array(arr,n);
              printf("Sorting is done by the parent\n");
              printf("==========PArent Pocess Done========\n");
              _exit(0);

            }
            break;
            case 2:
            printf("=========In main process=========\n");
            printf("Process Id:%d",getpid());
            p=fork();
            if(p<0){
              printf("Error in creating the child process\n");

            }else if(p==0){
               wait(0);//makes no diff
               printf("===========Back to the Child Process==========\n");
               printf("Child Process Id:%d",getpid());
               printf("Parent Process Id:%d",getppid());
               printf("Child Process Sorts the array using insertion\n");
               insertion_sort(arr,n);
              display_array(arr,n);
              printf("Child is in orphan state\n");
              printf("Sorting is done by child process\n");
              printf("===========Child Process Done=========\n");
              _exit(-1);

            }else{
               printf("==========IN Parent Process=========\n");
               printf("Parent Process Id:%d",getpid());
               printf("Parent sorts the array by using selection sort\n");
                selection_sort(arr,n);
              display_array(arr,n);
              printf("Sorting is done by the parent\n");
              printf("==========PArent Pocess Done========\n");
              _exit(0);

            }
            break;
            case 3:
            p=fork();
            if(p<0){
              printf("Error in creating the child process\n");
            }else if(p==0){
              printf("===========In child Process==========\n");
              printf("Child Process Id:%d\n",getpid());
              printf("Parent Process Id:%d\n",getppid());
              sleep(2);
              printf("Child process compltes its task and parent is in sleep\n");
              printf("=============child process done=============\n");
              _exit(-1);


            }else{
              printf("==========In Parent Process=========\n");
              printf("Parent Process Id:%d\n",getpid());
              printf("Parent going to sleep\n");
              sleep(5);
              printf("parent wakes up\n");
              printf("PArent Process done\n");
              while(1);
              _exit(0);



               
            }
             break;
             default:
             printf("Select Appropriate option");
         
      }
    return 0;
}