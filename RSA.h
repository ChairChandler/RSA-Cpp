#ifndef RSA_HPP
#define RSA_HPP
#include "BigDec.h"

namespace RSA_NS
{
    class RSA
    {
    public:
        struct PublicKey
        {
            BigDec_NS::BigDec e, n;
        };

        struct PrivateKey
        {
            BigDec_NS::BigDec d, n;
        };

    private:
        static const int MAX_NUM = 4;
        static const int MAX_DIGITS = 2048;
        static const int MAX_SIZE = 200;
        static const int MIN_SIZE = 3;

        void publicKey(BigDec_NS::BigDec &e, BigDec_NS::BigDec &n, BigDec_NS::BigDec &x, size_t length);
        void privateKey(BigDec_NS::BigDec &d, BigDec_NS::BigDec &x, BigDec_NS::BigDec &e);
        BigDec_NS::BigDec modInv(BigDec_NS::BigDec &a, BigDec_NS::BigDec &b);
        BigDec_NS::BigDec checkPrime(BigDec_NS::BigDec &number);
        BigDec_NS::BigDec numGenerate(size_t length);
        BigDec_NS::BigDec relPrimeNum(BigDec_NS::BigDec &number);

        PublicKey pubKey;
        PrivateKey privKey;

    public:

        void generateKeys(size_t primeNumbersLength);
        BigDec_NS::BigDec* encrypt(char message[]);
        BigDec_NS::BigDec* encrypt(std::string &message);
        std::string decrypt(BigDec_NS::BigDec numbers[], size_t length);


        class ExcWrongNumber: public std::exception
        {
        private:
            std::string lastError;

        public:
            ExcWrongNumber(std::string msg);
            const char* what() const noexcept;

        };


        PublicKey getPublicKey() const;
        PrivateKey getPrivateKey() const;

        void setPublicKey(RSA::PublicKey key);
        void setPrivateKey(RSA::PrivateKey key);
    };
}

#endif
