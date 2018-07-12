#include "BigDec.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include "BigDec.hpp"
		
BigDec::BigDec()
{
	this->strMalloc=0;
	this->value=new char[2];
	this->value[0]='0';
	this->value[1]='\0';
}

BigDec::BigDec(std::string value)
{
	if(checkValue(value)==true)
	{
		this->strMalloc=0;
		size_t len;
		len=value.size();
		this->value=new char[len+1];
		for(int i=0;i<len;i++)
			this->value[i]=value[i];
		this->value[len]='\0';
	}
	else
	{
		this->strMalloc=0;
		this->value=new char[2];
		this->value[0]='0';
		this->value[1]='\0';
	}
}

BigDec::BigDec(const char value[])
{
	if(checkValue(value)==true)
	{
		this->strMalloc=0;
		size_t len;
		len=strlen(value);
		this->value=new char[len+1];
		for(int i=0;i<len;i++)
			this->value[i]=value[i];
		this->value[len]='\0';
	}
	else
	{
		this->strMalloc=0;
		this->value=new char[2];
		this->value[0]='0';
		this->value[1]='\0';
	}
}

BigDec::~BigDec()
{
	delValue();
}

BigDec::BigDec(BigDec &number)
{
	C_BigDec pom;
	size_t nb_len;
	
	nb_len=strlen(number.value);
	this->strMalloc=number.strMalloc;
	this->value=new char[nb_len+1];
	strncpy(this->value,number.value,nb_len+1);
}

void BigDec::copy(BigDec *ptr, BigDec &obj)
{
	size_t len;
	
	len=strlen(obj.value);
	ptr->delValue();
	ptr->strMalloc=obj.strMalloc;
	ptr->value=new char[len+1];
	strncpy(ptr->value,obj.value,len+1);
}

BigDec& BigDec::operator+(BigDec &number)
{
	BigDec pom(BigDec_add(this->value,number.value));
	BigDec *ptr=new BigDec;
	copy(ptr,number);
	return *ptr;
}

BigDec& BigDec::operator+(C_BigDec number)
{
	if(checkValue(number)==true)
	{
	BigDec pom(BigDec_add(this->value,number));
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
	}
	else
	return *this;
}

BigDec& operator+(C_BigDec number1, BigDec &number2)
{
	if(number2.checkValue(number1)==true)
	{
		BigDec pom(BigDec_add(number1,number2.value));
		BigDec *ptr=new BigDec;
		number2.copy(ptr,pom);
		return *ptr;
	}
	else
		return number2;
}

BigDec& BigDec::operator=(BigDec &number)
{
	if(this==&number)
	return *this;
	
	C_BigDec pom;
	size_t nb_len;
	
	delValue();
	nb_len=strlen(number.value);
	this->strMalloc=number.strMalloc;
	this->value=new char[nb_len+1];
	strncpy(this->value,number.value,nb_len+1);
	return *this;
}

void BigDec::operator+=(BigDec &number)
{
	C_BigDec ptr;
	ptr=BigDec_add(this->value, number.value);
	
	delValue();
	this->strMalloc=1;
	this->value=ptr;
}

BigDec& BigDec::operator=(C_BigDec number)
{
	if(checkValue(number)==true)
	{
		size_t nb_len;
		
		delValue();	
		nb_len=strlen(number);
		this->strMalloc=1;
		this->value=new char[nb_len+1];
		strncpy(this->value,number,nb_len+1);
		return *this;
	}
	else
		return *this;
}

void BigDec::operator+=(C_BigDec number)
{
	if(checkValue(number)==true)
	{
		C_BigDec ptr;
		ptr=BigDec_add(this->value, number);
		
		delValue();
		this->strMalloc=1;
		this->value=ptr;
	}
}

BigDec& BigDec::operator++()
{
	this->strMalloc=1;
	this->value=BigDec_add(this->value, "1");
	return *this;
}


BigDec BigDec::operator++(int)
{
	BigDec pom(*this);
	++(*this);
	return pom;
}

std::ostream& operator<<(std::ostream &os, BigDec &number)
{
	os<<number.value;
	return os;
}

std::istream& operator>>(std::istream &os, BigDec &number)
{
	std::string pom;
	size_t len;
	os>>pom;
	if(number.checkValue(pom)==true)
	{
		len=pom.size();
		number.delValue();
		number.value=new char[len+1];
		number.strMalloc=0;
		
		for(int i=0;i<len;i++)
		number.value[i]=pom[i];
		number.value[len]='\0';
	}
	
	return os;
}

void BigDec::delValue()
{
	if(this->strMalloc)
	free(this->value);
	else
	delete[] this->value;
}

BigDec& BigDec::operator-(BigDec &number)
{
	BigDec pom(BigDec_sub(this->value,number.value));
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
}

BigDec& operator-(C_BigDec number1, BigDec &number2)
{
	if(number2.checkValue(number1)==true)
	{
		BigDec pom(BigDec_sub(number1,number2.value));
		BigDec *ptr=new BigDec;
		number2.copy(ptr,pom);
		return *ptr;
	}
	else
		return number2;
}

BigDec& BigDec::operator-(C_BigDec number)
{
	if(checkValue(number)==true)
	{
		BigDec pom(BigDec_sub(this->value,number));
		BigDec *ptr=new BigDec;
		copy(ptr,pom);
		return *ptr;
	}
	else
		return *this;
}

void BigDec::operator-=(BigDec &number)
{
	C_BigDec ptr;
	ptr=BigDec_sub(this->value,number.value);
	
	delValue();
	this->strMalloc=1;
	this->value=ptr;
}

void BigDec::operator-=(C_BigDec number)
{
	if(checkValue(number)==true)
	{
		C_BigDec ptr;
		ptr=BigDec_sub(this->value,number);
		
		delValue();
		this->strMalloc=1;
		this->value=ptr;
	}
}

BigDec& BigDec::operator*(BigDec &number)
{
	BigDec pom(BigDec_mul(this->value,number.value));
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
}

BigDec& BigDec::operator*(C_BigDec number)
{
	if(checkValue(number)==true)
	{
		BigDec pom(BigDec_mul(this->value,number));
		BigDec *ptr=new BigDec;
		copy(ptr,pom);
		return *ptr;
	}
	else
		return *this;
}

BigDec& operator*(C_BigDec number1, BigDec &number2)
{
	if(number2.checkValue(number1)==true)
	{
		BigDec pom(BigDec_mul(number1,number2.value));
		BigDec *ptr=new BigDec;
		number2.copy(ptr,pom);
		return *ptr;
	}
	else
		return number2;
}

void BigDec::operator*=(BigDec &number)
{
	C_BigDec ptr;
	ptr=BigDec_mul(this->value,number.value);
	delValue();
	this->strMalloc=1;
	this->value=ptr;
}

void BigDec::operator*=(C_BigDec number)
{
	if(checkValue(number)==true)
	{
		C_BigDec ptr;
		ptr=BigDec_mul(this->value,number);
		delValue();
		this->strMalloc=1;
		this->value=ptr;
	}
}

BigDec& BigDec::operator/(BigDec &number)
{
	BigDec pom(BigDec_div(this->value,number.value));
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
}

BigDec& BigDec::operator/(C_BigDec number)
{
	if(checkValue(number)==true)
	{
		BigDec pom(BigDec_div(this->value,number));
		BigDec *ptr=new BigDec;
		copy(ptr,pom);
		return *ptr;
	}
	else
		return *this;
}

BigDec& operator/(C_BigDec number1, BigDec &number2)
{
	if(number2.checkValue(number1)==true)
	{
		BigDec pom(BigDec_div(number1,number2.value));
		BigDec *ptr=new BigDec;
		number2.copy(ptr,pom);
		return *ptr;
	}
	else
		return number2;
}
	
void BigDec::operator/=(BigDec &number)
{
	C_BigDec ptr;
	ptr=BigDec_div(this->value,number.value);
	delValue();
	this->strMalloc=1;
	this->value=ptr;
}

void BigDec::operator/=(C_BigDec number)
{
	if(checkValue(number)==true)
	{
		C_BigDec ptr;
		ptr=BigDec_div(this->value,number);
		delValue();
		this->strMalloc=1;
		this->value=ptr;
	}
}

BigDec& BigDec::operator^(unsigned long long exp)
{
	BigDec pom(BigDec_pow(this->value,exp));
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
}
	
void BigDec::operator^=(unsigned long long exp)
{
	C_BigDec ptr;
	ptr=BigDec_pow(this->value,exp);
	delValue();
	this->strMalloc=1;
	this->value=ptr;
}

BigDec& BigDec::operator%(BigDec &number)
{
	BigDec pom(BigDec_mod(this->value,number.value));
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
}

BigDec& BigDec::operator%(C_BigDec number)
{
	if(checkValue(number)==true)
	{
		BigDec pom(BigDec_mod(this->value,number));
		BigDec *ptr=new BigDec;
		copy(ptr,pom);
		return *ptr;
	}
	else
		return *this;
}

BigDec& operator%(C_BigDec number1, BigDec &number2)
{
	if(number2.checkValue(number1)==true)
	{
		BigDec pom(BigDec_mod(number1,number2.value));
		BigDec *ptr=new BigDec;
		number2.copy(ptr,pom);
		return *ptr;
	}
	else
		return number2;
}

void BigDec::operator%=(BigDec &number)
{
	C_BigDec ptr;
	ptr=BigDec_mod(this->value,number.value);
	delValue();
	this->strMalloc=1;
	this->value=ptr;
}

void BigDec::operator%=(C_BigDec number)
{
	if(checkValue(number)==true)
	{
		C_BigDec ptr;
		ptr=BigDec_mod(this->value,number);
		delValue();
		this->strMalloc=1;
		this->value=ptr;
	}
}

bool BigDec::operator>(BigDec &number)
{
	if(this->value[0]!='-'&&number.value[0]=='-')
		return true;
	else if(this->value[0]=='-'&&number.value[0]!='-')
		return false;
	else
	{
		char ans;
		if(this->value[0]!='-')
		{
			ans=BigDec_max(this->value,number.value);
			
			if(ans==0)//<
			return false;
			else if(ans==2)
			return true;
		}
		else
		{
			ans=BigDec_max(this->value+1,number.value+1);
			
			if(ans==0)//>
			return true;
			else if(ans==2)
			return false;
		}
		
		if(ans==1)
		return false;
	}
}

bool BigDec::operator>(C_BigDec number)
{
	if(checkValue(number)==false)
		return false;
	
	if(this->value[0]!='-'&&number[0]=='-')
		return true;
	else if(this->value[0]=='-'&&number[0]!='-')
		return false;
	else
	{
		char ans;
		if(this->value[0]!='-')
		{
			ans=BigDec_max(this->value,number);
			
			if(ans==0)//<
			return false;
			else if(ans==2)
			return true;
		}
		else
		{
			ans=BigDec_max(this->value+1,number+1);
			
			if(ans==0)//>
			return true;
			else if(ans==2)
			return false;
		}
		
		if(ans==1)
		return false;
	}
}

bool operator>(C_BigDec number1, BigDec &number2)
{
	if(number2.checkValue(number1)==false)
		return false;
	
	if(number1[0]!='-'&&number2.value[0]=='-')
		return true;
	else if(number1[0]=='-'&&number2.value[0]!='-')
		return false;
	else
	{
		char ans;
		if(number1[0]!='-')
		{
			ans=BigDec_max(number1,number2.value);
			
			if(ans==0)//<
			return false;
			else if(ans==2)
			return true;
		}
		else
		{
			ans=BigDec_max(number1+1,number2.value+1);
			
			if(ans==0)//>
			return true;
			else if(ans==2)
			return false;
		}
		
		if(ans==1)
		return false;
	}
}

bool BigDec::operator>=(BigDec &number)
{
	if(this->operator>(number)==true)
	return true;
	
	return this->operator==(number);
}

bool BigDec::operator>=(C_BigDec number)
{
	if(this->operator>(number)==true)
	return true;
	
	return this->operator==(number);
}

bool operator>=(C_BigDec number1, BigDec &number2)
{
	if(operator>(number1,number2)==true)
	return true;
	
	return operator==(number1,number2);
}

bool BigDec::operator==(BigDec &number)
{
	if(strcmp(this->value,number.value)==0)
	return true;
	else
	return false;
}

bool BigDec::operator==(C_BigDec number)
{
	if(checkValue(number)==false)
		return false;
	
	if(strcmp(this->value,number)==0)
	return true;
	else
	return false;
}

bool operator==(C_BigDec number1, BigDec &number2)
{
	if(number2.checkValue(number1)==false)
		return false;
	
	if(strcmp(number1,number2.value)==0)
	return true;
	else
	return false;
}

bool BigDec::operator!=(BigDec &number)
{
	if(this->operator==(number)==true)
	return false;
	else
	return true;	
}

bool BigDec::operator!=(C_BigDec number)
{	
	if(this->operator==(number)==true)
	return false;
	else
	return true;
}

bool operator!=(C_BigDec number1, BigDec &number2)
{	
	if(operator==(number1,number2)==true)
	return false;
	else
	return true;
}

bool BigDec::operator<(BigDec &number)
{
	if(this->operator>=(number)==true)
	return false;
	else
	return true;
}

bool BigDec::operator<(C_BigDec number)
{	
	if(this->operator>=(number)==true)
	return false;
	else
	return true;
}

bool operator<(C_BigDec number1, BigDec &number2)
{	
	if(operator>=(number1,number2)==true)
	return false;
	else
	return true;
}

bool BigDec::operator<=(BigDec &number)
{
	if(this->operator>(number)==true)
	return false;
	else
	return true;
}

bool BigDec::operator<=(C_BigDec number)
{
	if(this->operator>(number)==true)
	return false;
	else
	return true;
}

bool operator<=(C_BigDec number1, BigDec &number2)
{
	if(operator>(number1,number2)==true)
	return false;
	else
	return true;
}

BigDec& BigDec::gcd(BigDec &number)
{
	BigDec pom(BigDec_gcd(this->value,number.value));	
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
}

BigDec& BigDec::gcd(C_BigDec number)
{
	if(checkValue(number)==false)
		return *this;
	
	BigDec pom(BigDec_gcd(this->value,number));
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
}

BigDec& BigDec::fgcd(BigDec &number)
{
	BigDec pom(BigDec_fgcd(this->value,number.value));
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
}

BigDec& BigDec::fgcd(C_BigDec number)
{
	if(checkValue(number)==false)
		return *this;
	
	BigDec pom(BigDec_fgcd(this->value,number));
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
}

BigDec& BigDec::genrfn()
{
	if(this->operator>("1") == true)
	{
		BigDec pom(BigDec_genrfn(this->value));
		BigDec *ptr=new BigDec;
		copy(ptr,pom);
		return *ptr;
	}
	else
	{
		std::cerr<<std::endl<<"[ERROR] First number have to be over than 1!"<<std::endl;
		return *this;
	}
}

BigDec& BigDec::modularPower(BigDec &exp, BigDec &mod)
{
	BigDec pom(BigDec_modularPower(this->value,exp.value,mod.value));
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
}

BigDec& BigDec::modularPower(BigDec &exp, C_BigDec mod)
{
	if(checkValue(mod)==false)
		return *this;
	
	BigDec pom(BigDec_modularPower(this->value,exp.value,mod));
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
}

BigDec& BigDec::modularPower(C_BigDec exp, BigDec &mod)
{
	if(checkValue(exp)==false)
		return *this;
	
	BigDec pom(BigDec_modularPower(this->value,exp,mod.value));
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
}

BigDec& BigDec::modularPower(C_BigDec exp, C_BigDec mod)
{
	if(checkValue(exp)==false||checkValue(mod)==false)
		return *this;
	
	BigDec pom(BigDec_modularPower(this->value,exp,mod));
	BigDec *ptr=new BigDec;
	copy(ptr,pom);
	return *ptr;
}

bool BigDec::checkValue(C_BigDec number)
{
	for(int i;i<strlen(number);i++)
	{
		if(!(number[i]=='-'||(number[i]>='0'&&number[i]<='9')))
		{
			std::cerr<<std::endl<<"[ERROR] Incorrect number value!"<<std::endl;
			return false;
		}
	}
	
	return true;
}

bool BigDec::checkValue(std::string number)
{
	for(int i;i<number.size();i++)
	{
		if(!(number[i]=='-'||(number[i]>='0'&&number[i]<='9')))
		{
			std::cerr<<std::endl<<"[ERROR] Incorrect number value!"<<std::endl;
			return false;
		}
	}
	
	return true;
}

template <class T>
BigDec::operator T*()
{
	return static_cast<T*>(value);
}
