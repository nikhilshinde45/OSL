#include<stdio.h>

void readMatrix(int mat[20][20],int np,int nr){
   for(int i=0;i<np;i++){
     for(int j=0;j<nr;j++){
       scanf("%d",&mat[i][j]);
     }
   }
}

void displayMatrix(int mat[20][20],int np,int nr){
  for(int i=0;i<np;i++){
     for(int j=0;j<nr;j++){
        printf("%d",mat[i][j]);
     }
     printf("\n");

  }
}

int main(){
      int np;
      printf("Enter the number of process:\n");
      scanf("%d",&np);
      int nr;
      printf("Enter the number of resources:\n");
      scanf("%d",&nr);
      int allocation[20][20],max[20][20],need[20][20],available[20];
      

      printf("Enter the resources allocation matrix\n");
      readMatrix(allocation,np,nr);
      printf("Enter the maximum resource for a process needed\n");
      readMatrix(max,np,nr);
      printf("Enter the availabel resources:\n");
      for(int i=0;i<nr;i++){
         scanf("%d",&available[i]);
      }

      //calculation of need matrix
      for(int i=0;i<np;i++){
        for(int j=0;j<nr;j++){
           need[i][j]=max[i][j]-allocation[i][j];
        }
      }

      printf("The need matrix of resources for processes:\n");
      displayMatrix(need,np,nr);
      int finish[20]={0};
      int safeState[20];
      int k=0;

      int completed =0;
      while(completed<np){
        int progress=0;
        for(int i=0;i<np;i++){
           if(finish[i]==0){
            int flag=1;
             for(int j=0;j<nr;j++){

                 if(need[i][j]>available[j]){
                      flag=0;
                      break;
                 }
             }
             if(flag){
                safeState[k]=i;
                k++;
                finish[i]=1;
                completed++;
                progress=1;
                
                for(int l=0;l<nr;l++){
                    available[l]+=allocation[i][l];
                }
             }


           }
        }
        if(progress==0){
           printf("\nNo Safe state exists\n");
           return 0;
        }
      }
      if(completed==np){
            printf("\nSystem is in safe state\n");
            printf("Process Sequence is:\n");
            for(int i=0;i<np;i++){
              printf("%d",safeState[i]);
            }
            printf("\n");
      }

}