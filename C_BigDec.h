#ifndef C_BIGDEC_H
#define C_BIGDEC_H
#include <stdlib.h>

    #ifdef __cplusplus

    extern "C"
    {

        typedef char* C_BigDec;
        typedef const char* const__C_BigDec;

        C_BigDec C_BigDec_new(int sign, size_t digits);
        void C_BigDec_delete(C_BigDec number);

        C_BigDec C_BigDec_add(const__C_BigDec number1, const__C_BigDec number2);
        C_BigDec C_BigDec_sub(const__C_BigDec number1, const__C_BigDec number2);
        C_BigDec C_BigDec_mul(const__C_BigDec number1, const__C_BigDec number2);
        C_BigDec C_BigDec_div(const__C_BigDec number1, const__C_BigDec number2);
        C_BigDec C_BigDec_pow(const__C_BigDec base, unsigned long long exp);
        C_BigDec C_BigDec_mod(const__C_BigDec number1, const__C_BigDec number2);
        C_BigDec C_BigDec_findGreatestCommonDivision(const__C_BigDec number1, const__C_BigDec number2);
        C_BigDec C_BigDec_generateRandomFirstNumber(const__C_BigDec startNumber);
        C_BigDec C_BigDec_modularPower(const__C_BigDec number, const__C_BigDec exp, const__C_BigDec mod);

        C_BigDec C_BigDec_assign(C_BigDec *dest, const__C_BigDec source);
        C_BigDec C_BigDec_abs(const__C_BigDec number);
        int C_BigDec_isNegative(const__C_BigDec number);
        int C_BigDec_cmp(const__C_BigDec number1, const__C_BigDec number2);
        void C_BigDec_changeSign(C_BigDec *number1);

    }

    #else

        typedef char* C_BigDec;
        typedef const char* const__C_BigDec;

        C_BigDec C_BigDec_new(int sign, size_t digits);
        void C_BigDec_delete(C_BigDec number);

        C_BigDec C_BigDec_add(C_BigDec number1, C_BigDec number2);
        C_BigDec C_BigDec_sub(C_BigDec number1, C_BigDec number2);
        C_BigDec C_BigDec_mul(C_BigDec number1, C_BigDec number2);
        C_BigDec C_BigDec_div(C_BigDec number1, C_BigDec number2);
        C_BigDec C_BigDec_pow(C_BigDec base, unsigned long long exp);
        C_BigDec C_BigDec_mod(C_BigDec number1, C_BigDec number2);
        C_BigDec C_BigDec_findGreatestCommonDivision(C_BigDec number1, C_BigDec number2);
        C_BigDec C_BigDec_generateRandomFirstNumber(C_BigDec startNumber);
        C_BigDec C_BigDec_modularPower(C_BigDec number, C_BigDec exp, C_BigDec mod);

        C_BigDec C_BigDec_assign(C_BigDec *dest, C_BigDec source);
        C_BigDec C_BigDec_abs(C_BigDec number);
        int C_BigDec_isNegative(C_BigDec number);
        int C_BigDec_cmp(C_BigDec number1, C_BigDec number2);
        void C_BigDec_changeSign(C_BigDec *number1);

    #endif

#endif
