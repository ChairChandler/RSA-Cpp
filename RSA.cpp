#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include "BigDec.hpp"
#include "RSA.hpp"

BigDec& RSA::modInv(BigDec &a, BigDec &b) 
{

	uint16_t nm1_len,nm2_len;
	BigDec helpPtr,u,w,x,z,q;
	BigDec *retVal;
	
	w=a;	z=b;
	u="1";	x="0";
	
	while(w!="0")
	{
		if(w<z)
		{
			helpPtr=x;
			x=u;
			u=helpPtr;
			
			helpPtr=w;
			w=z;
			z=helpPtr;
		}
		
		q=w/z;
		u-=q*x;
		w-=q*z;
	}
	
	if(z!="1")
	{
		retVal=new BigDec("0");
		return *retVal;
	}
	
	if(x<"0")
	x+=b;
	
	retVal=new BigDec(x);
	return *retVal;
}

BigDec& RSA::checkPrime(BigDec &number) 
{
	
	FILE *pPipe;
	char buff[MAX_DIGITS+1],*arg;
	
	
	arg=new char[10+strlen(number)];
	memset(arg,'\0',10+strlen(number));
	strncat(arg,"Prime.py ",9);
	strncat(arg,number,strlen(number));
	
	pPipe=popen(arg,"r");
	fgets(buff,MAX_DIGITS,pPipe);
	fgets(buff,MAX_DIGITS,pPipe);
	pclose(pPipe);
	
	int i=1;
	while(buff[i]=='-'||(buff[i]>='0'&&buff[i]<='9'))
	i++;

	delete arg;
	arg=new char[i];
	memcpy(arg,buff+1,i-1);
	arg[i-1]='\0';
	
	BigDec *ptr;
	ptr=new BigDec(arg);
	delete arg;
	
	return *ptr;

}

BigDec& RSA::numGenerate(size_t length) 
{
	
	std::string aux;
	aux=char(rand()%9+'1');
	
	for(uint16_t i=1;i<length-1;i++)
	{
		aux+=char(rand()%10+'0');
	}
	
	aux+=char((rand()%5)*2+1+'0');	
	
	BigDec *number;
	number=new BigDec(aux);
	
	return *number;

}

BigDec& RSA::relPrimeNum(BigDec &number) 
{

	BigDec *nmb,gcd;

	nmb=new BigDec;
	*nmb="3";

	while(number!=*nmb)
	{	
		gcd=number.fgcd(*nmb);

		if(gcd=="1")
			break;
			
		*nmb+="1";
	}
	
	return *nmb;
}

BigDec* RSA::encrypt(char *message)
{
	
	char nmb[MAX_NUM];
	BigDec aux,*encMessage;
	uint16_t length;
	
	length=strlen(message);
	encMessage=new BigDec[length];
	
	for(uint16_t i=0;i<length;i++)
	{
		sprintf(nmb,"%d",message[i]);
		aux=nmb;
		aux=aux.modularPower(this->Public.e,this->Public.n);
		encMessage[i]=aux;
	}
	
	return encMessage;
}

BigDec* RSA::encrypt(std::string &message)
{
	char *charMessage;
	size_t length;
	
	length=message.size();
	charMessage=new char[length+1];
	
	for(uint16_t i=0;i<length;i++)
	{
		charMessage[i]=message[i];
	}
	
	charMessage[length]='\0';
	
	BigDec *ptr;
	ptr=encrypt(charMessage);
	delete[] charMessage;
	
	return ptr;
}

std::string RSA::decrypt(BigDec numbers[], size_t length)
{
	
	std::string decMessage;
	BigDec aux;
	
	for(uint16_t i=0;i<length;i++)
	{
		aux=numbers[i];
		aux=aux.modularPower(this->Private.d,this->Private.n);
		decMessage+=char(atoi(aux));
	}
	
	return decMessage;
	
}

void RSA::publicKey(BigDec &e, BigDec &n, BigDec &x, size_t length) 
{
	
	BigDec p,q;
	srand(time(NULL));
	
	p=numGenerate(length);
	q=numGenerate(length);
	p=checkPrime(p);
	q=checkPrime(q);

	x=(p-"1")*(q-"1");
	n=p*q;
	e=relPrimeNum(x);
	
}

void RSA::privateKey(BigDec &d, BigDec &x, BigDec &e) 
{
	
	d=modInv(e,x);
	
}

void RSA::generateKeys(size_t length) 
{
	
	if(length<MIN_SIZE)
	{
		std::cerr<<std::endl<<"[RSA_generateKeys] Keys length have to be over than "<<MIN_SIZE-1<<".";
		exit(EXIT_FAILURE);
	}
	else if(length>MAX_SIZE)
	{
		std::cerr<<std::endl<<"[RSA_generateKeys] Keys length have to be over than "<<MAX_SIZE+1<<".";
		exit(EXIT_FAILURE);
	}
	
	BigDec x;
	
	do
	{
	publicKey(this->Public.e,this->Public.n,x,length);
	privateKey(this->Private.d,x,this->Public.e);
	}while(this->Public.e<"0"||this->Public.n<"0"||x<"0"||this->Private.d<"0");
	
	this->Private.n=this->Public.n;
	
}
