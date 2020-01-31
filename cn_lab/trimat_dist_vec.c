#include<stdio.h>


void main()
{
	int src, dest, node, i, j, k, prevj=1;

	printf("\n Enter number of nodes\n");
	scanf("%d",&node);

	int cost[node][node], rtdist[node][node],from[node][node];
	
	
	printf("\n Enter cost matrix\n");
	for(i=0;i<node;i++)
		for(j=0;j<node;j++)
		{
			scanf("%d",&cost[i][j]);
			rtdist[i][j]=cost[i][j];
			from[i][j]=j;
		}

	for(i=0;i<node;i++)
	{
		printf("\n\n Router %d\n",i);
		
		for(j=0;j<node;j++)
			printf("\t\n node %d via %d Distance %d",j,from[i][j],rtdist[i][j]);
	}


	j=1;
	for(i=0;i<node-1;i++)
	{	
		j=prevj;
		for(;j<node;j++)
		{
			for(k=0;k<node;k++)
			{
				if(rtdist[i][j]>rtdist[i][k]+rtdist[k][j])
				{
					rtdist[i][j]=rtdist[i][k]+rtdist[k][j];
					from[i][j]=from[i][k];
					
				}
			}		
			rtdist[j][i]=rtdist[i][j];
			from[j][i]=from[i][j];	
		}
		prevj++;
	}
			


	for(i=0;i<node;i++)
	{
		printf("\n\n Router %d\n",i);
		for(j=0;j<node;j++)
			printf("\t\n node %d via %d Distance %d",j,from[i][j],rtdist[i][j]);
	}
	printf("\n\n");
}
