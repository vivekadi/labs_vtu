#include<stdio.h>
#include<string.h>

int main()
{
	int i=0,j=0,n,remlen;
	char a[30],b[30],scopy[6],ecopy[6];
	gets(a);
	n=strlen(a);
	
	strncpy(scopy,a,6);
	remlen=n-15;
	strncpy(ecopy,a+9+remlen,6);

	char s[6]={'d','l','e','s','t','x'};
	char e[6]={'d','l','e','e','t','x'};
	
	if(strcmp(scopy,s)==0)
		i+=6;
	
	while(i<n)
	{
		if(a[i]=='d'&&a[i+1]=='l'&&a[i+2]=='e')
		{
			//b[j]='d';
			//b[j+1]='l';
			//b[j+2]='e';
			i+=6;
		}
		b[j]=a[i];
		i++;	j++;
	}
	
	b[j+1]='\0';

	puts(b);
	
	return(0);
}
