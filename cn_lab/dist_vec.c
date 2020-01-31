#include<stdio.h>

struct node
{
	unsigned dist[20];
	unsigned from[20];
}rt[10];


void main()
{
	int cost[20][20], src, dest, node, i, j, k, count=0;
	printf("\n Enter number of nodes\n");
	scanf("%d",&node);
	
	printf("\n Enter cost matrix\n");
	for(i=0;i<node;i++)
		for(j=0;j<node;j++)
		{
			scanf("%d",&cost[i][j]);
			//cost[i][i]=0;
			rt[i].dist[j]=cost[i][j];
			rt[i].from[j]=j;
		}

	for(i=0;i<node;i++)
	{
		printf("\n\n Router %d\n",i);
		
		for(j=0;j<node;j++)
			printf("\t\n node %d via %d Distance %d",j,rt[i].from[j],rt[i].dist[j]);
	}

	do
	{
		count=0;
		for(i=0;i<node;i++)
			for(j=0;j<node;j++)
				if(i!=j)
				for(k=0;k<node;k++)
					if(rt[i].dist[j]>rt[i].dist[k]+rt[k].dist[j])
					{
						rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
						rt[i].from[j]=rt[i].from[k];
						count++;
					}
	}while(count!=0);

	for(i=0;i<node;i++)
	{
		printf("\n\n Router %d\n",i+1);
		for(j=0;j<node;j++)
			printf("\t\n node %d via %d Distance %d",j,rt[i].from[j],rt[i].dist[j]);
	}
	
	printf("\n\n");
}
