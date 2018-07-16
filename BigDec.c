#include <stdio.h>
#include <string.h>
#include "BigDec.h"

static C_BigDec BigDec_modularPowerAction(C_BigDec number, C_BigDec exp, C_BigDec mod);
static inline C_BigDec BigDec_delZeroes(C_BigDec number, size_t length);

static inline C_BigDec BigDec_delZeroes(C_BigDec number, size_t length) {
	
	C_BigDec hlptr;
	int i;
	
	if(number[0]=='0')
	{	
		i=0;
		while(number[i]=='0'&&i!=length-1) i++;
		hlptr=(C_BigDec)malloc((length+1-i)*sizeof(char));
		memcpy(hlptr,number+i,length+1-i); 
		free(number);
		number=hlptr;
	}
	
	if(strcmp(number,"")==0)
	{
		free(number);
		number=(C_BigDec)malloc(2*sizeof(char));
		number[0]='0';
		number[1]='\0';
	}
	
	return number;
}

C_BigDec BigDec_div(C_BigDec number1, C_BigDec number2) {
	
	C_BigDec numberhlp,number3,x,aux,q,pop;
	size_t nb1_len,nb2_len,nb3_len;
	char ans,negnmb1,negnmb2,buff[2];
	register int i,j,z,m;
	
	pop=NULL;
	
	if(strcmp(number2,"0")==0)
	{
		fprintf(stderr,"[ERROR] Division by 0.");
		return NULL;
	}
	
	if(number1[0]=='-')
	{
		negnmb1=1;
		number1=number1+1;		
	}
	else
		negnmb1=0;
		
	if(number2[0]=='-')
	{
		negnmb2=1;
		number2=number2+1;
	}
	else
		negnmb2=0;


	ans=BigDec_max(number1,number2);
	if(ans==0)
	{
		numberhlp=(C_BigDec)malloc(2*sizeof(char));
		numberhlp[0]='0';
		numberhlp[1]='\0';
		return numberhlp;
	}
	else if(ans==1&&!negnmb1^negnmb2)
	{
		numberhlp=(C_BigDec)malloc(2*sizeof(char));
		numberhlp[0]='1';
		numberhlp[1]='\0';
		return numberhlp;
	}
	else if(ans==1)
	{
		numberhlp=(C_BigDec)malloc(3*sizeof(char));
		numberhlp[0]='-';
		numberhlp[1]='1';
		numberhlp[2]='\0';
		return numberhlp;
	}
	
	nb1_len=strlen(number1);
	nb2_len=strlen(number2);
	nb3_len=nb1_len;
	
	numberhlp=(C_BigDec)malloc((nb2_len+1)*sizeof(char));
	number3=(C_BigDec)malloc((nb3_len+1)*sizeof(char));
	
	memset(number3,'0',nb3_len);
	number3[nb3_len]='\0';
	
	for(i=0,j=0;i<nb1_len;i++)
	{	
		numberhlp[j]=number1[i];
		numberhlp[j+1]='\0';	
		
		if(j+1<nb2_len)
		{	
		number3[i]='0';
		j++;
		continue;
		}
			
		if(BigDec_max(numberhlp,number2)==0)
		{
		number3[i]='0';
		j++;
		continue;
		}
		
		for(z=1;z<=9;z++)
		{
			numberhlp=BigDec_delZeroes(numberhlp,strlen(numberhlp));
			sprintf(buff,"%d",z);
			q=BigDec_mul(number2,buff);
			if(BigDec_max(numberhlp,q)==1)
			{
				number3[i]=z+'0';
				free(q);
				j=0;
				break;
			}
			else if(z==9&&BigDec_max(numberhlp,q)==2)
			{
				number3[i]=z+'0';
				aux=q;
				q=BigDec_sub(numberhlp,q);
				free(aux);
				memcpy(numberhlp,q,strlen(q));
				j=strlen(q);
			}
			else if(z>1&&BigDec_max(numberhlp,pop)==2&&BigDec_max(numberhlp,q)==0)
			{
				number3[i]=(z-1)+'0';
				aux=q;
				q=BigDec_sub(numberhlp,pop);
				free(aux);
				memcpy(numberhlp,q,strlen(q));
				j=strlen(q);
				free(q);
				break;	
			}
			
			if(pop!=NULL)
				free(pop);
			
			pop=q;
		}
		
	}
	
	if(pop!=NULL)
		free(pop);
	free(numberhlp);
	
	number3=BigDec_delZeroes(number3,nb3_len);
	
	if(negnmb1^negnmb2)
	{
		number1=(C_BigDec)malloc((strlen(number3)+2)*sizeof(char));
		memcpy(number1+1,number3,strlen(number3)+1);
		free(number3);
		number1[0]='-';
		number3=number1;
	}
	
	return number3;
	
}

C_BigDec BigDec_add(C_BigDec number1, C_BigDec number2) {
	
	C_BigDec ptrhlp,number3,fixnumber3;
	char eq,negnmb;
	int i,j;
	negnmb=0;
	
		if(number1[0]=='-'&&number2[0]=='-')
		{
			number1=number1+1;
			number2=number2+1;
			negnmb=1;
		}
		else if(number1[0]=='-')
		{
			number1=number1+1;
			return BigDec_sub(number2, number1);
		}
		else if(number2[0]=='-')
		{
			number2=number2+1;
			return BigDec_sub(number1, number2);
		}
	
	size_t nb1_len,nb2_len;
	nb1_len=strlen(number1);
	nb2_len=strlen(number2);
	
	if(nb1_len<nb2_len)
	{		
		ptrhlp=number1;
		number1=number2;
		number2=ptrhlp;
		
		nb1_len^=nb2_len;
		nb2_len^=nb1_len;
		nb1_len^=nb2_len;
	}
	
	number3=(C_BigDec)malloc((nb1_len+2)*sizeof(char));
	number3[nb1_len+1]='\0';
	eq=0;

	for(i=nb1_len-1,j=nb2_len-1;i>=0;i--)
	{
		if(j>=0)
		{
		eq+=(number1[i]-'0')+(number2[j]-'0');
		j--;
		}
		else
		eq+=number1[i]-'0';
	
		number3[i+1]=eq%10+'0';
		eq/=10;
	}
	
	number3[0]=eq+'0';
	
	number3=BigDec_delZeroes(number3,nb1_len+2);
	
	if(negnmb)
	{
		number1=(C_BigDec)malloc((strlen(number3)+2)*sizeof(char));
		memcpy(number1+1,number3,strlen(number3)+1);
		number1[0]='-';
		number3=number1;
	}
	return number3;
}

C_BigDec BigDec_sub(C_BigDec number1, C_BigDec number2) {

	C_BigDec ptrhlp,number3;
	size_t nb1_len,nb2_len,nb3_len;
	register int i,j,z;
	char negnmb,eq,rest,negnmb1,negnmb2;
	
	negnmb=0;
	
	if(number1[0]=='-')
	{
		negnmb1=1;
		number1=number1+1;
	}
	else
		negnmb1=0;
	
	if(number2[0]=='-')
	{
		negnmb2=1;
		number2=number2+1;
	}
	else
		negnmb2=0;
		
	if(negnmb1==0&&negnmb2==1)
		return BigDec_add(number1,number2);
	else if(negnmb1==1&&negnmb2==1)
	{
		ptrhlp=number1;
		number1=number2;
		number2=ptrhlp;
	}
	else if(negnmb1==1&&negnmb2==0)
	{
		ptrhlp=BigDec_add(number1,number2);
		number1=(C_BigDec)malloc((strlen(ptrhlp)+2)*sizeof(char));
		memcpy(number1+1,ptrhlp,strlen(ptrhlp)+1);
		number1[0]='-';
		return number1;		
	}

	nb1_len=strlen(number1);
	nb2_len=strlen(number2);
	
	if(nb1_len<nb2_len)
	{
		ptrhlp=number1;
		number1=number2;
		number2=ptrhlp;
		
		nb1_len^=nb2_len;
		nb2_len^=nb1_len;
		nb1_len^=nb2_len;
		negnmb=1;
	}
	else if(nb1_len==nb2_len)
	{
		i=0;
		while(number1[i]!='\0')
		{
			if(number1[i]>number2[i])
			break;
			
			if(number1[i]<number2[i])
			{
			ptrhlp=number1;
			number1=number2;
			number2=ptrhlp;
			
			nb1_len^=nb2_len;
			nb2_len^=nb1_len;
			nb1_len^=nb2_len;
			negnmb=1;
			break;
			}
			
			i++;
		}
	}


		number3=(C_BigDec)malloc((nb1_len+1)*sizeof(char));
		number3[nb1_len]='\0';
		z=nb1_len-1;

	rest=0;
	for(i=nb1_len-1,j=nb2_len-1;i>=0;i--,z--)
	{	
		if(j>=0)
		{
		eq=(number1[i]-'0')-(number2[j]-'0')+rest;
		j--;
		}
		else
		eq=number1[i]-'0'+rest;
		
		rest=0;
		
		if(eq<0)
		{
		eq+=10;
		rest--;
		}
		
		number3[z]=eq+'0';
	}
	
	nb3_len=strlen(number3);
	number3=BigDec_delZeroes(number3,nb3_len);
	
	if(negnmb)
	{
		number1=(C_BigDec)malloc((strlen(number3)+2)*sizeof(char));
		memcpy(number1+1,number3,strlen(number3)+1);
		number1[0]='-';
		number3=number1;
	}
	
	return number3;
}

C_BigDec BigDec_tradPow(C_BigDec base, unsigned long long exp) {
	
	C_BigDec sum,hlptr;
	int i,j;
	i=2;
	
	hlptr=(C_BigDec)malloc((strlen(base)+1)*sizeof(char));
	memcpy(hlptr,base,strlen(base)+1);
	
	while(i<=exp)
	{
		sum=BigDec_mul(hlptr,hlptr);
		free(hlptr);
		hlptr=sum;
		i*=2;
	}
	
	if(i>exp)
	i/=2;
	
	for(j=i;j<exp;j++)
		sum=BigDec_mul(sum,base);
	
	return sum;
	
}

C_BigDec BigDec_powRes(C_BigDec base, unsigned long long exp) {
	
	if(exp==0)
	{
		C_BigDec a;
		a=(C_BigDec)malloc(2*sizeof(char));
		a[0]='1';
		a[1]='\0';
		return a;
	}
	else if(exp%2==0)
	{
		C_BigDec a,b;
		size_t length;
		a=BigDec_powRes(base,exp/2);	
		b=BigDec_mul(a,a);
		free(a);
		return b;
	}
	else
	{
		C_BigDec a,b;
		size_t length;
		a=BigDec_powRes(base,exp-1);	
		b=BigDec_mul(a,base);
		free(a);
		return b;
	}
		
}

C_BigDec BigDec_pow(C_BigDec base, unsigned long long exp) {
		
	C_BigDec numberhlp;
	
	if(base[0]=='-')
	{
		int baseLeng;
		baseLeng=strlen(base);
		numberhlp=(C_BigDec)malloc(baseLeng*sizeof(char));
		memcpy(numberhlp,base+1,baseLeng);
		base=numberhlp;
		numberhlp=BigDec_powRes(base,exp);
		free(base);
		baseLeng=strlen(numberhlp)+1;
		
		if(exp%2==1)
		baseLeng++;
		
		base=(C_BigDec)malloc(baseLeng*sizeof(char));
		
		if(exp%2==1)
		{
			memcpy(base+1,numberhlp,baseLeng);
			base[0]='-';
		}
		else
			memcpy(base,numberhlp,baseLeng);
		
		return base;
	}
	else
		return BigDec_powRes(base,exp);
}

C_BigDec BigDec_mul(C_BigDec number1, C_BigDec number2) {
	
	C_BigDec number3,ptrhlp;
	size_t nb1_len,nb2_len,nb3_len,lastNr1,lastNr2,lastNr3;
	int i,j,eq;
	char negnmb;
	
	nb1_len=strlen(number1);
	nb2_len=strlen(number2);
	nb3_len=nb1_len+nb2_len;
	
	negnmb=0;
	if(number1[0]=='-'&&number2[0]=='-')
	{
		number1=number1+1;
		nb1_len--;
			
		number2=number2+1;	
		nb2_len--;
	}
	else if(number1[0]=='-')
	{
		number1=number1+1;
		nb1_len--;
		negnmb=1;
	}
	else if(number2[0]=='-')
	{
		number2=number2+1;
		nb2_len--;
		negnmb=1;
	}
	
	if(strlen(number1)<strlen(number2))//number1>=number2
	{
		ptrhlp=number1;
		number1=number2;
		number2=ptrhlp;
		
		nb1_len^=nb2_len;
		nb2_len^=nb1_len;
		nb1_len^=nb2_len;
	}
	
	number3=(C_BigDec)malloc((nb3_len+1+negnmb)*sizeof(char));
	number3[nb3_len+negnmb]='\0';
	
	for(i=0;i<nb3_len;i++)
	number3[i]='0';
	
	lastNr1=nb1_len-1;
	lastNr2=nb2_len-1;
	lastNr3=nb3_len-1;

	for(i=lastNr2;i>=0;i--)
	{
		eq=0;
		for(j=lastNr1;j>=0;j--)
		{
			eq=eq+(number2[i]-'0')*(number1[j]-'0');
			number3[lastNr3-(lastNr2-i)-(lastNr1-j)]+=eq%10;
			
			eq/=10;
			
			if(number3[lastNr3-(lastNr2-i)-(lastNr1-j)]-'0'>9)
			{
				eq+=(number3[lastNr3-(lastNr2-i)-(lastNr1-j)]-'0')/10;
				number3[lastNr3-(lastNr2-i)-(lastNr1-j)]=(number3[lastNr3-(lastNr2-i)-(lastNr1-j)]-'0')%10+'0';
			}
		}	
		
		if(eq)
		number3[lastNr3-(lastNr2-i)-(lastNr1-j)]+=eq;
	}
	
	number3=BigDec_delZeroes(number3,nb3_len);

	if(negnmb)
	{
		if(number3[0]=='0')
		number3[0]='-';
		else
		{
			number1=(C_BigDec)malloc((nb3_len+2)*sizeof(char));
			memcpy(number1+1,number3,nb3_len+1);
			free(number3);
			number1[0]='-';
			number3=number1;
		}
	}

	return number3;	
}

C_BigDec BigDec_mod(C_BigDec number1, C_BigDec number2) {
	
	char ans;
	C_BigDec rem,res,pom;
	size_t nmb1_len;
	ans=BigDec_max(number1,number2);
	
	if(ans==0)
	{
		nmb1_len=strlen(number1);
		rem=(C_BigDec)malloc((nmb1_len+1)*sizeof(char));
		memcpy(rem,number1,nmb1_len+1);
		return rem;
	}
	else if(ans==1)
	{
		rem=(C_BigDec)malloc(2*sizeof(char));
		rem[0]='0';
		rem[1]='\0';
		return rem;	
	}
	
	res=BigDec_div(number1,number2);
	pom=BigDec_mul(res,number2);
	rem=BigDec_sub(number1,pom);
	
	free(res);
	free(pom);	
	
	return rem;
	
}

C_BigDec BigDec_gcd(C_BigDec number1, C_BigDec number2) {
	
	C_BigDec number3,helpPtr;
	char ans;
	
	if(number1[0]=='-')
	number1=number1+1;
	
	if(number2[0]=='-')
	number2=number2+1;

	ans=BigDec_max(number1,number2);
	
	while(ans!=1)//n1!=n2
	{
		if(ans==2)//n1>n2
		{
		helpPtr=number1;
		number1=BigDec_sub(number1,number2);
		free(helpPtr);
		}
		else if(ans==0)//n1<n2
		{
		helpPtr=number2;
		number2=BigDec_sub(number2,number1);
		free(helpPtr);
		}
		ans=BigDec_max(number1,number2);
	}
	
	return number1;
}

C_BigDec BigDec_fgcd(C_BigDec number1, C_BigDec number2) {
	
	C_BigDec a,b,c;

	a=(C_BigDec)malloc((strlen(number1)+1) * sizeof(char));
	b=(C_BigDec)malloc((strlen(number2)+1) * sizeof(char));
	c=NULL;
	
	memcpy(a,number1,strlen(number1)+1);
	memcpy(b,number2,strlen(number2)+1);
	
	while(strcmp(b,"0"))
	{
		c=BigDec_mod(a,b);
		free(a);
		a=b;
		b=c;
	}
	return a;
} 

C_BigDec BigDec_genrfn(C_BigDec number) {

	C_BigDec nmb,gcd,helpPtr;
	gcd=NULL;

	nmb=(C_BigDec)malloc(2*sizeof(char));
	nmb[0]='3';
	nmb[1]='\0';

	while(strcmp(number,nmb)!=0)
	{	
		if(gcd!=NULL)
		free(gcd);
		
		gcd=BigDec_fgcd(number,nmb);
		
		if(strcmp(gcd,"1")==0)
			break;
			
		helpPtr=nmb;
		nmb=BigDec_add(nmb,"1");
		free(helpPtr);
	}	
	free(gcd);
	return nmb;
}

C_BigDec BigDec_modularPower(C_BigDec number, C_BigDec exp, C_BigDec mod) {
	
	return	BigDec_modularPowerAction(number, exp, mod);

}

static C_BigDec BigDec_modularPowerAction(C_BigDec number, C_BigDec exp, C_BigDec mod) {
	
	if(strcmp(exp,"1")==0)
	{
		return number;
	}
	
	C_BigDec val=BigDec_mod(exp,"2");
	
	if(strcmp(val,"0")==0)
	{
		free(val);
		C_BigDec aux,tmp;
		
		tmp=BigDec_div(exp,"2");
		aux=BigDec_modularPowerAction(number, tmp, mod);
	
		free(tmp);
	
		tmp=BigDec_mul(aux,aux);
		
		if(strcmp(aux,number))
		free(aux);
		
		aux=tmp;
		tmp=BigDec_mod(tmp,mod);
		free(aux);
		
		return tmp;
	}
	else
	{
		free(val);
		C_BigDec aux,tmp;
		
		tmp=BigDec_div(exp,"2");
		aux=BigDec_modularPowerAction(number, tmp, mod);
		
		free(tmp);
		
		tmp=aux;
		aux=BigDec_mul(aux,aux);
		
		if(strcmp(tmp,number))
		free(tmp);
	
		tmp=aux;
		aux=BigDec_mul(aux,number);
		free(tmp);

		tmp=aux;
		aux=BigDec_mod(aux,mod);
		free(tmp);

		return aux;
	}
	
}
