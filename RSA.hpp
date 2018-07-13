#ifndef RSA_HPP
#define RSA_HPP
#include "BigDec.hpp"
#include <string>

const int MAX_NUM = 4;
const int MAX_DIGITS = 2048;
const int MAX_SIZE = 200;
const int MIN_SIZE = 3;

class RSA
{
	private:
		void publicKey(BigDec &e, BigDec &n, BigDec &x, size_t length);
		void privateKey(BigDec &d, BigDec &x, BigDec &e);
		BigDec& modInv(BigDec &a, BigDec &b);
		BigDec& checkPrime(BigDec &number);
		BigDec& numGenerate(size_t length);
		BigDec& relPrimeNum(BigDec &number);
	public:
		struct
		{	
			BigDec e,n;	
		} Public;
		
		struct
		{
			BigDec d,n;
		} Private;
	
		void generateKeys(size_t length);
		BigDec* encrypt(char *message);
		BigDec* encrypt(std::string &message);
		std::string decrypt(BigDec numbers[], size_t length);
};

#endif
