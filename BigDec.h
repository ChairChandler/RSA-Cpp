#ifndef BIGDEC_H
#define BIGDEC_H
#include <string.h>
#include <stdlib.h>

typedef char* C_BigDec;
C_BigDec BigDec_add(C_BigDec number1, C_BigDec number2);
C_BigDec BigDec_sub(C_BigDec number1, C_BigDec number2);
C_BigDec BigDec_mul(C_BigDec number1, C_BigDec number2);
C_BigDec BigDec_div(C_BigDec number1, C_BigDec number2);
C_BigDec BigDec_pow(C_BigDec base, unsigned long long exp);
C_BigDec BigDec_tradPow(C_BigDec base, unsigned long long exp);
C_BigDec BigDec_powRes(C_BigDec base, unsigned long long exp);
C_BigDec BigDec_mod(C_BigDec number1, C_BigDec number2);
inline int BigDec_max(C_BigDec number1, C_BigDec number2);
C_BigDec BigDec_gcd(C_BigDec number1, C_BigDec number2);
C_BigDec BigDec_fgcd(C_BigDec number1, C_BigDec number2);
C_BigDec BigDec_genrfn(C_BigDec number);
C_BigDec BigDec_modularPower(C_BigDec number, C_BigDec exp, C_BigDec mod);

inline int BigDec_max(C_BigDec number1, C_BigDec number2) { //0-number1<number2 1-number1==number2 2-number1>number2
	
	int i;
	size_t nb1_len,nb2_len;
	
	nb1_len=strlen(number1);
	nb2_len=strlen(number2);
	
	if(nb1_len>nb2_len)
		return 2;
	else if(nb1_len<nb2_len)
		return 0;
		
	for(i=0;i<nb1_len;i++)
	{
		if(number1[i]>number2[i])
			return 2;
		
		if(number1[i]<number2[i])
			return 0;
	}
	
	return 1;
}

#endif
