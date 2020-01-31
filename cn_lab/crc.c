#include<stdio.h>
#include<string.h>

char message[20], genpoly[18], parity[28];
int mlen,glen,i,j;

void xor()
{
	for(j=1;j<glen;j++)
		parity[j]=((parity[j]==genpoly[j])?'0':'1');
}


void crc()
{
	for(i=0;i<glen;i++)
		parity[i]=message[i];
	do
	{
		if(parity[0]=='1')
			xor();
		for(j=0;j<glen-1;j++)
			parity[j]=parity[j+1];

		parity[j]=message[i++];
	}while(i<=mlen+glen-1);
}

int main()
{
	printf("\n Enter the message bits\n");
	gets(message);
	mlen=strlen(message);
	
		
	printf("\n Enter generating polynomial\n");
	gets(genpoly);
	glen=strlen(genpoly);
	
	
	for(i=mlen;i<mlen+glen-1;i++)
		message[i]='0';
	printf("\n After appending zeros\n");
	puts(message);

	
	crc();
	printf("\n Checksum or parity is\n");
	puts(parity);

	
	for(i=mlen;i<mlen+glen-1;i++)
		message[i]=parity[i-mlen];
	printf("\n Codeword is\n");
	puts(message);

	printf("\n Enter received message\n");
	gets(message);
	
	crc();
	printf("\n Remainder is");
	puts(parity);

	for(i=0;(i<glen-1)&&(parity[i]!='1');i++);
	if(i<glen-1)
		printf("\n Error message\n");
	else
		printf("\n No Error in message\n");
	
	return 0;	
}
	








