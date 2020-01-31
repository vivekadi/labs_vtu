#include<stdio.h>


int max,node,infinity;

void dkt(int cost[max][max],int node);

int main()
{
	int i,j;
	printf("Enter max,infinity, number of nodes\n");	
	scanf("%d,%d,%d",&max,&infinity,&node);
	int cost[max][max];
	
	printf("Enter the cost matrix\n");
	for(i=0;i<node;i++)
		for(j=0;j<node;j++)
			scanf("%d",&cost[i][j]);
	
	
	dkt(cost,node);
	
	return (0);
}

void dkt(int cost[max][max],int node)
{
	int distance[max], prevdist[max];
	int visit[max],count,minimumdist,nextnode,startnode,i,j;

	printf("Enter start node\n");
	scanf("%d",&startnode);

	for(i=0;i<node;i++)
	{
		distance[i]=cost[startnode][i];
		prevdist[i]=startnode;
		visit[i]=0;
	}

	distance[startnode]=0;
	visit[startnode]=1;
	count=1;


	while(count<node-1)
	{
		minimumdist=infinity;
		
		for(i=0;i<node;i++)
		{
			if(distance[i]<minimumdist && !visit[i])
			{
				minimumdist=distance[i];
				nextnode=i;
			}
		}

		visit[nextnode]=1;
		
		for(i=0;i<node;i++)
		{
			if(!visit[i])
			{
				if(minimumdist+cost[nextnode][i]<distance[i])
				{
					distance[i]=minimumdist+cost[nextnode][i];
					prevdist[i]=nextnode;
				}
			}
		}
		count++;
	}

	for(i=0;i<node;i++)
		if(i!=startnode)
		{
			printf("\n Distance of node %d=%d",i,distance[i]);
			printf("\nPath=%d",i);
			
			j=i;

			do
			{
				j=prevdist[j];
				printf("<-%d",j);
			} while(j!=startnode);
		}
}





