#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct Process{
  int pId;
  int at;
  int bt;
  int pr;
  int ct;
  int tat;
  int wt;

};
//sort arrival time by ascending
void sortByAT(struct Process * p,int n){
  for(int i=0;i<n;i++){
     for(int j=i+1;j<n;j++){
       if(p[i].at>p[j].at){
        struct Process temp=p[j];
        p[j]=p[i];
        p[i]=temp;
       }
     }
  }

}

void displayProcess(struct Process * p,int n){
     printf("\n\n+----------+----------+----------+----------+----------+----------+----------+\n");
     printf("\n|    PID    |    AT    |    BT    |    CT    |     TAT    |    WT    |    PR    |\n");
    printf("\n\n+----------+----------+----------+----------+----------+----------+----------+\n");
   for(int i=0;i<n;i++){
      printf("\n | %-8d | %-8d | %-8d | %-8d | %-8d | %-8d | %-8d |",p[i].pId,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].pr);

   }
       printf("\n+----------+----------+----------+----------+----------+----------+----------+\n");


}

void FCFS(struct Process *p,int n){
    printf("======First Come First Server=====");
    printf("Gannt chart: \n");
    printf("(0) | ");
    int _ct=0;
    for(int i=0;i<n;i++){
       _ct+=p[i].bt;
       p[i].ct=_ct;
       p[i].tat=_ct-p[i].at;
       p[i].wt=p[i].tat-p[i].bt;
       printf(" P%d (%d) | ",p[i].pId,p[i].ct);

    }
}

void SJF_PR(struct Process *p ,int n){
    printf("=====SJF Preemptive=====");
    printf("\nGannt Chart : ");
    printf("(0) | ");
    int completed=0;
    int _t=0;
    int Timegiven[100000]={0};
    while(completed<n){
        int min_bt=10000000;
        int ind=-1;
        for(int i=0;i<n;i++){
           if(p[i].at<=_t&&(p[i].bt-Timegiven[i])<min_bt&&Timegiven[i]!=p[i].bt){
              min_bt=p[i].bt-Timegiven[i];
              ind=i;
           }
        }
         _t++;
        if(ind!=-1){
          Timegiven[ind]++;//give one unit
            if(Timegiven[ind]==p[ind].bt){
                  p[ind].ct=_t;
                  p[ind].tat=p[ind].ct-p[ind].at;
                  p[ind].wt=p[ind].tat-p[ind].bt;
                  completed++;
                  printf(" P%d (%d) |",p[ind].pId,p[ind].ct);
            }
        }
    }

}

void SJF_NP(struct Process *p,int n){
  printf("======SJF Non Preemptive=====");
  printf("\n Gannt Chart: \n");
  printf(" (0) |");
  int Timegiven[100000]={0};
  int _t=0;

  int completed=0;
 
 
  while(completed<n){
    int min_t=10000000;
     int ind=-1;
     for(int i=0;i<n;i++){
       if(p[i].at<=_t&&p[i].bt<min_t&&Timegiven[i]!=p[i].bt){
          min_t=p[i].bt;
          ind=i;
       }
     }
     if(ind!=-1){
      p[ind].ct=_t+p[ind].bt;
      _t+=p[ind].bt;
      p[ind].tat=p[ind].ct-p[ind].at;
      p[ind].wt=p[ind].tat-p[ind].bt;
      Timegiven[ind]+=p[ind].bt;
      completed++;
      printf("P%d (%d) |",p[ind].pId,p[ind].ct);

         
     }else{
      _t++;
     }
  }
}

//lowest no taken as highest priorty
void PR_NP(struct Process *p,int n){
     printf("=====Priority Non-Preemptive=====");
     printf(" Gannt Chart: \n");
     printf(" (0) |");
     int completed = 0;
     int Timegiven[100000]={0};

     int _t=0;
     while(completed<n){
        int min_pr=10000000;
        int ind=-1;
        for(int i=0;i<n;i++){
           if(p[i].at<=_t&&p[i].pr<min_pr&&Timegiven[i]!=p[i].bt){
            ind = i;
            min_pr=p[i].pr;
           }
        }
        if(ind!=-1){
         p[ind].ct=p[ind].bt+_t;
         _t+=p[ind].bt;
         p[ind].tat=p[ind].ct-p[ind].at;
         p[ind].wt=p[ind].tat-p[ind].bt;
         completed++;
         Timegiven[ind]+=p[ind].bt;
         printf("P%d (%d)",p[ind].pId,p[ind].ct);
        }else{
         _t++;
        }
     }
}

void PR_P(struct Process *p,int n){
     printf("=====Priority Preemptive=====");
     printf(" Gannt Chart :\n");
     printf(" (0) |");
     int _t=0;
     int completed =0;
     int Timegiven[100000]={0};

     while(completed<n){
       int min_pr=10000000;
       int ind=-1;
       for(int i=0;i<n;i++){
          if(p[i].at<=_t&&p[i].pr<min_pr&&Timegiven[i]!=p[i].bt){
               ind=i;
               min_pr=p[i].pr;
          }
       }
       _t++;
       if(ind!=-1){
           Timegiven[ind]++;
           if(Timegiven[ind]==p[ind].bt){
             p[ind].ct=_t;
             p[ind].tat=p[ind].ct-p[ind].at;
             p[ind].wt=p[ind].tat-p[ind].bt;
             completed++;
             printf("P%d (%d) |",p[ind].pId,p[ind].ct);
           }
       }
     }
}

void RR(struct Process *p,int n){
    printf("=====Round Robbin=====");
    int tq;
    printf("Enter the time quatntun:\n");
    scanf("%d",&tq);
    printf("Gannt Chart: \n");
    printf(" (0) |");
    int completed=0;
    int Timegiven[100000]={0};
     int _t=0;
     int queue[100];
     int front=0;
     int rear=0;
     int inQueue[100]={0};
     for(int i=0;i<n;i++){
         if(p[i].at==0){
              queue[rear++]=i;
              inQueue[i]=1;
         }
     }
    while(completed<n){
      if(front==rear){
         _t++;
           for(int i=0;i<n;i++){
            if(p[i].at<=_t&&!inQueue[i]&&Timegiven[i]<p[i].bt){
               queue[rear++]=i;
               inQueue[i]=1;
            }
             
           }
           continue;
      }
      int i=queue[front++];//pop
      int requiredtime=(p[i].bt-Timegiven[i]>tq)?tq:(p[i].bt-Timegiven[i]);
      Timegiven[i]+=requiredtime;
      _t+=requiredtime;
      printf("P%d (%d) |",p[i].pId,_t);


      //newly arrived process
      for(int j=0;j<n;j++){
           if(p[j].at<=_t&&!inQueue[j]&&Timegiven[j]<p[j].bt){
            queue[rear++]=j;
            inQueue[j]=1;
           }
      }

      if(Timegiven[i]<p[i].bt){
          queue[rear++]=i;
      }else if(Timegiven[i]==p[i].bt&&p[i].ct==0){
         p[i].ct=_t;
          p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            completed++;

      }
      if(Timegiven[i]>=p[i].bt){
            inQueue[i]=0;
      }
      
    }
}

int main(){
     int n;
     printf("Enter the number of processes:\n");
     scanf("%d",&n);
      struct Process *P=(struct Process*)calloc(n,sizeof(struct Process));
      for(int  i=0;i<n;i++){
         printf("Enter the process id: ");
         scanf("%d",&P[i].pId);
         printf("Enter the arrival time: ");
         scanf("%d",&P[i].at);
         printf("Enter the burst time: ");
         scanf("%d",&P[i].bt);
         printf("Enter the process prority: ");
         scanf("%d",&P[i].pr);
      }
     while(1){
      int choice;
      printf("1.FCFS\n 2.SJF Non-Preemptive\n 3.SJF Preemptive\n4.Priority Non-Preemptive\n5.Priority Preemptive\n6.Round Robbin\n7.Exit\n");
      printf("Enter the choice: \n");
      scanf("%d",&choice);
      switch(choice){
          case 1:
          sortByAT(P,n);
          FCFS(P,n);
          displayProcess(P,n);
          break;
          case 2:
          sortByAT(P,n);
           SJF_NP(P,n);
          displayProcess(P,n);
          break;
          case 3:
          sortByAT(P,n);
          SJF_PR(P,n);
          displayProcess(P,n);
          break;
          case 4:
                    sortByAT(P,n);
             PR_NP(P,n);
             displayProcess(P,n);
             break;
             case 5:
             sortByAT(P,n);
             PR_P(P,n);
             displayProcess(P,n);
             break;
    case 6:
             sortByAT(P,n);
               RR(P,n);
          displayProcess(P,n);
          break;


          case 7:
          _exit(0);
          break;
          default:
          printf("Select the appropriate option...");
      }
      

     }
     return 0;

}