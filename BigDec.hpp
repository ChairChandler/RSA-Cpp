#ifndef BIGDEC_HPP
#define BIGDEC_HPP
#include <string>
#include <iostream>
#include "BigDec.h"

class BigDec
{	
	private:
		void delValue();
		void copy(BigDec *ptr, BigDec &obj);
		bool checkValue(C_BigDec number);
		bool checkValue(std::string number);
		char strMalloc;
		C_BigDec value;
	public:
		BigDec();
		BigDec(std::string value);
		BigDec(const char value[]);
		BigDec(C_BigDec value);
		BigDec(BigDec &number);
		virtual ~BigDec();
		
		BigDec& operator=(BigDec &number);
		BigDec& operator=(C_BigDec number);
		
		void operator+=(BigDec &number);
		void operator+=(C_BigDec number);
		
		BigDec& operator++();
		BigDec operator++(int);
		
		BigDec& operator+(BigDec &number);
		BigDec& operator+(C_BigDec number);
		friend BigDec& operator+(C_BigDec number1, BigDec &number2);
		
		friend std::ostream& operator<<(std::ostream &os, BigDec &number);
		friend std::istream& operator>>(std::istream &os, BigDec &number);
		
		BigDec& operator-(BigDec &number);
		BigDec& operator-(C_BigDec number);
		friend BigDec& operator-(C_BigDec number1, BigDec &number2);
		
		void operator-=(BigDec &number);
		void operator-=(C_BigDec number);
		
		BigDec& operator*(BigDec &number);
		BigDec& operator*(C_BigDec number);
		friend BigDec& operator*(C_BigDec number1, BigDec &number2);
		
		void operator*=(BigDec &number);
		void operator*=(C_BigDec number);
		
		BigDec& operator/(BigDec &number);
		BigDec& operator/(C_BigDec number);
		friend BigDec& operator/(C_BigDec number1, BigDec &number2);
	
		void operator/=(BigDec &number);
		void operator/=(C_BigDec number);
	
		BigDec& operator^(unsigned long long exp);
		
		void operator^=(unsigned long long exp);
		
		BigDec& operator%(BigDec &number);
		BigDec& operator%(C_BigDec number);
		friend BigDec& operator%(C_BigDec number1, BigDec &number2);

		void operator%=(BigDec &number);
		void operator%=(C_BigDec number);
		
		bool operator>(BigDec &number);
		bool operator>(C_BigDec number);
		friend bool operator>(C_BigDec number1, BigDec &number2);
		
		bool operator>=(BigDec &number);
		bool operator>=(C_BigDec number);
		friend bool operator>=(C_BigDec number1, BigDec &number2);
		
		bool operator==(BigDec &number);
		bool operator==(C_BigDec number);
		friend bool operator==(C_BigDec number1, BigDec &number2);
		
		bool operator!=(BigDec &number);
		bool operator!=(C_BigDec number);
		friend bool operator!=(C_BigDec number1, BigDec &number2);
		
		bool operator<(BigDec &number);
		bool operator<(C_BigDec number);
		friend bool operator<(C_BigDec number1, BigDec &number2);
		
		bool operator<=(BigDec &number);
		bool operator<=(C_BigDec number);
		friend bool operator<=(C_BigDec number1, BigDec &number2);
		
		BigDec& gcd(BigDec &number);
		BigDec& gcd(C_BigDec number);
		
		BigDec& fgcd(BigDec &number);
		BigDec& fgcd(C_BigDec number);
		
		BigDec& genrfn();	
		
		BigDec& modularPower(BigDec &exp, BigDec &mod);	
		BigDec& modularPower(BigDec &exp, C_BigDec mod);
		BigDec& modularPower(C_BigDec exp, BigDec &mod);
		BigDec& modularPower(C_BigDec exp, C_BigDec mod);
		
		template <class T>
		operator T*();
};

#endif
