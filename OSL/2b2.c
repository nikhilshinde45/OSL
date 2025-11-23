 #include<stdio.h>
int main(int argc, char* argv[])
{

	int a[10],i,m,c=0,l,u,mid;
	
	printf("\n--------------------Now in Searching code program process : %d",getpid());
	printf("\nThe received sorted aray is : ");

	for(i=0;i<argc;i++)
	{
		a[i]=atoi(argv[i]);
		printf("%d - ",a[i]);
	}
	
	 printf("\n\n--------------------Enter the number to be searched  :  ");
    	scanf("%d",&m);
	
       	l=0;
       	u=i-1;
       	
    	while(l<=u)
	{
        	mid=(l+u)/2;
        	if(m==a[mid])
		{
             		c=1;
             		break;
         	}
         	else if(m<a[mid])
	 	{
         		u=mid-1;
         	}
         	else
	 	{
             		l=mid+1;
	 	}
    	}
    	if(c==0)
        	printf("\n\nThe number is not found.");
    	else
         	printf("\n\nThe number is found.");
	printf("\nSearch program over, returning to the child process");
	return 0;
}
