#include <iostream>
#include <string>
#include <cstdlib>
#include <stdint.h>
#include <cstring>
#include <ctime>
#include <algorithm>
#include "RSA.h"

namespace RSA_NS
{
    BigDec_NS::BigDec RSA::modInv(BigDec_NS::BigDec &a, BigDec_NS::BigDec &b)
    {
        BigDec_NS::BigDec helpPtr, u, w, x, z, q;

        w=a;	z=b;
        u="1";	x="0";

        while(w != "0")
        {
            if(w < z)
            {
                std::swap(x, u);

                std::swap(w, z);
            }

            q  = w/z;
            u -= q*x;
            w -= q*z;
        }

        if(z != "1")
        {
            return BigDec_NS::BigDec("0");
        }
        else if(x < "0")
        {
            x+=b;
        }

        return BigDec_NS::BigDec(x);
    }

    BigDec_NS::BigDec RSA::checkPrime(BigDec_NS::BigDec &number)
    {
        C_BigDec c_number = const_cast<C_BigDec>(number.c_BigDec());
        std::string arg;
        FILE *pPipe;
        char buff[MAX_DIGITS+1];
        int counter = 1;


        arg  = "Prime.py ";
        arg += c_number;

        C_BigDec_delete(c_number);

        pPipe=popen(arg.c_str(), "r");

        fgets(buff, MAX_DIGITS, pPipe);
        fgets(buff, MAX_DIGITS, pPipe);

        pclose(pPipe);

        while(buff[counter] == '-' || (buff[counter] >= '0' && buff[counter] <= '9'))
        {
            counter++;
        }

        arg.clear();

        for(int i=0; i<counter-1; i++)
        {
            arg+=(buff+1)[i];
        }

        return BigDec_NS::BigDec(arg);
    }

    BigDec_NS::BigDec RSA::numGenerate(size_t length)
    {
        std::string aux;
        aux=static_cast<char>(rand()%9+'1');

        for(size_t i=1; i<length-1; i++)
        {
            aux+=static_cast<char>(rand()%10+'0');
        }

        aux+=static_cast<char>((rand()%5)*2+1+'0');

        return BigDec_NS::BigDec(aux);
    }

    BigDec_NS::BigDec RSA::relPrimeNum(BigDec_NS::BigDec &number)
    {
        BigDec_NS::BigDec nmb,gcd;

        nmb="3";

        while(number != nmb)
        {
            gcd=BigDec_NS::findGreatestCommonDivision(number, nmb);

            if(gcd == "1")
            {
                break;
            }
            else
            {
                nmb+="1";
            }
        }

        return BigDec_NS::BigDec(nmb);
    }
    
    BigDec_NS::BigDec* RSA::encrypt(char *message)
    {
        char nmb[MAX_NUM];
        BigDec_NS::BigDec aux, *encMessage;
        size_t length;

        length=strlen(message);
        encMessage=new BigDec_NS::BigDec[length];

        for(size_t i=0; i<length; i++)
        {
            sprintf(nmb, "%d", message[i]);
            aux=nmb;
            aux=BigDec_NS::modularPower(aux, this->pubKey.e, this->pubKey.n);
            encMessage[i]=aux;
        }

        return encMessage;
    }

    BigDec_NS::BigDec* RSA::encrypt(std::string &message)
    {
        char *charMessage;
        size_t length;

        length=message.size();
        charMessage=new char[length+1];

        for(size_t i=0; i<length; i++)
        {
            charMessage[i]=message[i];
        }

        charMessage[length]='\0';

        BigDec_NS::BigDec *ptr;
        ptr=encrypt(charMessage);
        delete[] charMessage;

        return ptr;
    }

    std::string RSA::decrypt(BigDec_NS::BigDec numbers[], size_t length)
    {
        std::string decMessage;
        BigDec_NS::BigDec aux;

        for(size_t i=0; i<length; i++)
        {
            aux=numbers[i];
            aux=BigDec_NS::modularPower(aux, this->privKey.d, this->privKey.n);
            decMessage+=char(atoi(aux));
        }

        return decMessage;
    }

    void RSA::publicKey(BigDec_NS::BigDec &e, BigDec_NS::BigDec &n, BigDec_NS::BigDec &x, size_t length)
    {
        BigDec_NS::BigDec p, q;
        srand(time(NULL));

        p=numGenerate(length);
        q=numGenerate(length);

        p=checkPrime(p);
        q=checkPrime(q);

        x=(p-"1")*(q-"1");
        n=p*q;
        e=relPrimeNum(x);
    }

    void RSA::privateKey(BigDec_NS::BigDec &d, BigDec_NS::BigDec &x, BigDec_NS::BigDec &e)
    {
        d=modInv(e, x);
    }

    void RSA::generateKeys(size_t primeNumbersLength)
    {
        if(primeNumbersLength < MIN_SIZE)
        {
            throw RSA::ExcWrongNumber(std::string("Keys length have to be over than" + std::to_string(MIN_SIZE-1)));
        }
        else if(primeNumbersLength > MAX_SIZE)
        {
            throw RSA::ExcWrongNumber(std::string("Keys length have to be over than" + std::to_string(MAX_SIZE+1)));
        }
        else
        {
            BigDec_NS::BigDec x;

            do
            {
                publicKey(this->pubKey.e, this->pubKey.n, x, primeNumbersLength);
                privateKey(this->privKey.d, x, this->pubKey.e);

            }while(this->pubKey.e < "0" || this->pubKey.n < "0" || x < "0" || this->privKey.d < "0");

            this->privKey.n=this->pubKey.n;
        }
    }

    //-------------------------------------------------------------------------------

    RSA::ExcWrongNumber::ExcWrongNumber(std::string msg): std::exception ()
    {
        this->lastError=msg;
    }

    const char* RSA::ExcWrongNumber::what() const noexcept
    {
        return lastError.c_str();
    }

    //-------------------------------------------------------------------------------

    RSA::PrivateKey RSA::getPrivateKey() const
    {
        return privKey;
    }

    RSA::PublicKey RSA::getPublicKey() const
    {
        return pubKey;
    }

    void RSA::setPublicKey(RSA::PublicKey key)
    {
        this->pubKey=key;
    }

    void RSA::setPrivateKey(RSA::PrivateKey key)
    {
        this->privKey=key;
    }
}
