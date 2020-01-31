#include<stdio.h>
#include<string.h>

int main()
{
	int code[20],copy[30],n,i,j,k,count=1;
	printf("Enter code length\n");
	scanf("%d",&n);
	printf("Enter code\n");
	for(i=0;i<n;i++)
		scanf("%d",&code[i]);
	i=0;j=0;
	while(i<n)
	{
		if(code[i]==1)
		{
			copy[j]=code[i];
			for(k=i+1;code[k]==1&&count<5&&k<n;k++)
			{
				j++;
				copy[j]=code[k];
				count++;
				if(count==5)
				{
					k++;
					//copy[j]=0;
				}
				i=k;
				
			}
				
		}
		
		else
			copy[j]=code[i];
		i++;
		j++;
		count=1;
	}

	printf("bit_stuff\n");
	for(i=0;i<j;i++)
		printf("%d",copy[i]);

	return(0);
}
