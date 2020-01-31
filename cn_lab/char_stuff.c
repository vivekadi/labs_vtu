#include<stdio.h>
#include<string.h>

int main()
{
	int i=0,j=0,n;
	char a[20],b[20];
	gets(a);
	n=strlen(a);
	char s[6]={'d','l','e','s','t','x'};
	char e[6]={'d','l','e','e','t','x'};
	for(j=0;j<6;j++)
		b[j]=s[j];
	
	while(i<n)
	{
		if(a[i]=='d'&&a[i+1]=='l'&&a[i+2]=='e')
		{
			b[j]='d';
			b[j+1]='l';
			b[j+2]='e';
			j+=3;
		}
		b[j]=a[i];
		i++;	j++;
	}
	
	for(j=j,i=0;j<j+6,i<6;j++,i++)
		b[j]=e[i];
	b[j+1]='\0';

	puts(b);
	
	return(0);
}
