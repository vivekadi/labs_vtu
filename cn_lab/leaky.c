#include<stdio.h>
#include<stdlib.h>



void buck_out(int *currbuck,int drate)
{
	if(*currbuck>0&&*currbuck>drate)
	{
		*currbuck=*currbuck-drate;
		printf("\n %d output , remain %d",drate,*currbuck);
	}
	
	else
	{
		printf("\n remaining data o/p =%d",*currbuck);
		*currbuck=0;
	}
}




int main()
{
	int currbuck=0,drate,bucksize=0,w_t,newpack,prevpack=0,i,j,count;
	printf("Enter bucketsize,datarate,count \n");
	scanf("%d,%d,%d",&bucksize,&drate,&count);
	
	for(i=0;i<=count;i++)
	{
		newpack=rand()%500;
		printf("\n\n Newpackis %d \n",newpack);
		newpack=newpack+prevpack;
		w_t=rand()%5;


		if(newpack<bucksize)
			currbuck=newpack;
		else
		{
			printf("\n %d currbuck size greater than bucksize , reject \n ",newpack);
			currbuck=prevpack;
		}
		
		printf("\n Current data in bucket %d", currbuck);
		printf("\n next data arrives in %d s", w_t);
		

		for(j=0;j<w_t;j++)
		{
			buck_out(&currbuck,drate);
		}

		prevpack=currbuck;
	}
	
	while(currbuck>0)
	{
		buck_out(&currbuck,drate);
	}
	return 0;
}

