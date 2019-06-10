#ifndef BIGDEC_H
#define BIGDEC_H
#include "C_BigDec.h"
#include <string>

namespace BigDec_NS
{
    class BigDec;

    BigDec findGreatestCommonDivision(const BigDec &number1, const BigDec &number2) noexcept;
    BigDec findGreatestCommonDivision(const BigDec &number1, const__C_BigDec number2);
    BigDec findGreatestCommonDivision(BigDec &&number1, const BigDec &number2);
    BigDec findGreatestCommonDivision(BigDec &&number1, const__C_BigDec number2);
    BigDec findGreatestCommonDivision(const__C_BigDec number, const__C_BigDec number2);

    BigDec generateRandomFirstNumber(const BigDec &number);
    BigDec generateRandomFirstNumber(BigDec &&number);
    BigDec generateRandomFirstNumber(const__C_BigDec number);

    BigDec modularPower(const BigDec &number, const BigDec &exp, const BigDec &mod) noexcept;
    BigDec modularPower(const BigDec &number, const BigDec &exp, BigDec &&mod);
    BigDec modularPower(const BigDec &number, const BigDec &exp, const__C_BigDec mod);

    BigDec modularPower(const BigDec &number, BigDec &&exp, const BigDec &mod);
    BigDec modularPower(const BigDec &number, BigDec &&exp, BigDec &&mod);
    BigDec modularPower(const BigDec &number, BigDec &&exp, const__C_BigDec mod);

    BigDec modularPower(const BigDec &number, const__C_BigDec exp, const BigDec &mod);
    BigDec modularPower(const BigDec &number, const__C_BigDec exp, BigDec &&mod);
    BigDec modularPower(const BigDec &number, const__C_BigDec exp, const__C_BigDec mod);

    BigDec modularPower(BigDec &&number, const BigDec &exp, const BigDec &mod);
    BigDec modularPower(BigDec &&number, const BigDec &exp, BigDec &&mod);
    BigDec modularPower(BigDec &&number, const BigDec &exp, const__C_BigDec mod);

    BigDec modularPower(BigDec &&number, BigDec &&exp,const  BigDec &mod);
    BigDec modularPower(BigDec &&number, BigDec &&exp, BigDec &&mod);
    BigDec modularPower(BigDec &&number, BigDec &&exp, const__C_BigDec mod);

    BigDec modularPower(BigDec &&number, const__C_BigDec exp, const BigDec &mod);
    BigDec modularPower(BigDec &&number, const__C_BigDec exp, BigDec &&mod);
    BigDec modularPower(BigDec &&number, const__C_BigDec exp, const__C_BigDec mod);

    BigDec modularPower(const__C_BigDec number, const BigDec &exp, const BigDec &mod);
    BigDec modularPower(const__C_BigDec number, const BigDec &exp, BigDec &&mod);
    BigDec modularPower(const__C_BigDec number, const BigDec &exp, const__C_BigDec mod);

    BigDec modularPower(const__C_BigDec number, BigDec &&exp, const BigDec &mod);
    BigDec modularPower(const__C_BigDec number, BigDec &&exp, BigDec &&mod);
    BigDec modularPower(const__C_BigDec number, BigDec &&exp, const__C_BigDec mod);

    BigDec modularPower(const__C_BigDec number, const__C_BigDec exp, const BigDec &mod);
    BigDec modularPower(const__C_BigDec number, const__C_BigDec exp, BigDec &&mod);
    BigDec modularPower(const__C_BigDec number, const__C_BigDec exp, const__C_BigDec mod);

    BigDec modularPower(const__C_BigDec number, const BigDec &exp, const BigDec &mod);
    BigDec modularPower(const__C_BigDec number, const BigDec &exp, const__C_BigDec mod);
    BigDec modularPower(const__C_BigDec number, const__C_BigDec exp, const BigDec &mod);
    BigDec modularPower(const__C_BigDec number, const__C_BigDec exp, const__C_BigDec mod);

    BigDec abs(const BigDec &number) noexcept;
    BigDec abs(BigDec &&number);
    BigDec abs(const__C_BigDec number);



    class BigDec
    {
    private:
        bool isValueMalloc;
        C_BigDec value;

        void deleteValue();
        static void checkValue(const__C_BigDec number, int functionLine);
        static void checkValue(const BigDec &number, int functionLine);
        static void checkValue(BigDec &&number, int functionLine);

    public:
        BigDec() noexcept;
        BigDec(std::string value);
        BigDec(C_BigDec value);
        BigDec(const__C_BigDec value);
        BigDec(const BigDec &number) noexcept;
        ~BigDec() noexcept;

        //----------------------------------------------------

        BigDec& operator=(const BigDec &number) noexcept;
        BigDec& operator=(const__C_BigDec number);

        void operator+=(const BigDec &number) noexcept;
        void operator+=(const__C_BigDec number);

        BigDec& operator++() noexcept;
        BigDec operator++(int) noexcept;

        BigDec operator+(const BigDec &number) noexcept;
        BigDec operator+(const__C_BigDec number);
        friend BigDec operator+(const__C_BigDec number1, const BigDec &number2);

        friend std::ostream& operator<<(std::ostream &os, const BigDec &number);
        friend std::istream& operator>>(std::istream &os, BigDec &number);

        friend std::ostream& operator<<(std::ostream &os, BigDec &&number);
        friend std::istream& operator>>(std::istream &os, BigDec &&number);

        BigDec operator-(BigDec &number) noexcept;
        BigDec operator-(const__C_BigDec number);
        friend BigDec operator-(const__C_BigDec number1, const BigDec &number2);

        void operator-=(const BigDec &number) noexcept;
        void operator-=(const__C_BigDec number);

        BigDec operator*(const BigDec &number) noexcept;
        BigDec operator*(const__C_BigDec number);
        friend BigDec operator*(const__C_BigDec number1, const BigDec &number2);

        void operator*=(const BigDec &number) noexcept;
        void operator*=(const__C_BigDec number);

        BigDec operator/(const BigDec &number) noexcept;
        BigDec operator/(const__C_BigDec number);
        friend BigDec operator/(const__C_BigDec number1, const BigDec &number2);

        void operator/=(const BigDec &number) noexcept;
        void operator/=(const__C_BigDec number);

        BigDec operator^(unsigned long long exp) noexcept;

        void operator^=(unsigned long long exp) noexcept;

        BigDec operator%(const BigDec &number) noexcept;
        BigDec operator%(const__C_BigDec number);
        friend BigDec operator%(const__C_BigDec number1, const BigDec &number2);

        void operator%=(const BigDec &number) noexcept;
        void operator%=(const__C_BigDec number);

        bool operator>(const BigDec &number) noexcept;
        bool operator>(const__C_BigDec number);
        friend bool operator>(const__C_BigDec number1, const BigDec &number2);

        bool operator>=(const BigDec &number) noexcept;
        bool operator>=(const__C_BigDec number);
        friend bool operator>=(const__C_BigDec number1, const BigDec &number2);

        bool operator==(const BigDec &number) noexcept;
        bool operator==(const__C_BigDec number);
        friend bool operator==(const__C_BigDec number1, const BigDec &number2);

        bool operator!=(const BigDec &number) noexcept;
        bool operator!=(const__C_BigDec number);
        friend bool operator!=(const__C_BigDec number1, const BigDec &number2);

        bool operator<(const BigDec &number) noexcept;
        bool operator<(const__C_BigDec number);
        friend bool operator<(const__C_BigDec number1, const BigDec &number2);

        bool operator<=(const BigDec &number) noexcept;
        bool operator<=(const__C_BigDec number);
        friend bool operator<=(const__C_BigDec number1, const BigDec &number2);

        //----------------------------------------------------

        friend BigDec findGreatestCommonDivision(const BigDec &number1, const BigDec &number2) noexcept;
        friend BigDec findGreatestCommonDivision(const BigDec &number1, const__C_BigDec number2);
        friend BigDec findGreatestCommonDivision(BigDec &&number1, const BigDec &number2);
        friend BigDec findGreatestCommonDivision(BigDec &&number1, const__C_BigDec number2);
        friend BigDec findGreatestCommonDivision(const__C_BigDec number, const__C_BigDec number2);

        friend BigDec generateRandomFirstNumber(const BigDec &number);
        friend BigDec generateRandomFirstNumber(BigDec &&number);
        friend BigDec generateRandomFirstNumber(const__C_BigDec number);

        friend BigDec modularPower(const BigDec &number, const BigDec &exp, const BigDec &mod) noexcept;
        friend BigDec modularPower(const BigDec &number, const BigDec &exp, BigDec &&mod);
        friend BigDec modularPower(const BigDec &number, const BigDec &exp, const__C_BigDec mod);

        friend BigDec modularPower(const BigDec &number, BigDec &&exp, const BigDec &mod);
        friend BigDec modularPower(const BigDec &number, BigDec &&exp, BigDec &&mod);
        friend BigDec modularPower(const BigDec &number, BigDec &&exp, const__C_BigDec mod);

        friend BigDec modularPower(const BigDec &number, const__C_BigDec exp, const BigDec &mod);
        friend BigDec modularPower(const BigDec &number, const__C_BigDec exp, BigDec &&mod);
        friend BigDec modularPower(const BigDec &number, const__C_BigDec exp, const__C_BigDec mod);

        friend BigDec modularPower(BigDec &&number, const BigDec &exp, const BigDec &mod);
        friend BigDec modularPower(BigDec &&number, const BigDec &exp, BigDec &&mod);
        friend BigDec modularPower(BigDec &&number, const BigDec &exp, const__C_BigDec mod);

        friend BigDec modularPower(BigDec &&number, BigDec &&exp, const BigDec &mod);
        friend BigDec modularPower(BigDec &&number, BigDec &&exp, BigDec &&mod);
        friend BigDec modularPower(BigDec &&number, BigDec &&exp, const__C_BigDec mod);

        friend BigDec modularPower(BigDec &&number, const__C_BigDec exp, const BigDec &mod);
        friend BigDec modularPower(BigDec &&number, const__C_BigDec exp, BigDec &&mod);
        friend BigDec modularPower(BigDec &&number, const__C_BigDec exp, const__C_BigDec mod);

        friend BigDec modularPower(const__C_BigDec number, const BigDec &exp, const BigDec &mod);
        friend BigDec modularPower(const__C_BigDec number, const BigDec &exp, BigDec &&mod);
        friend BigDec modularPower(const__C_BigDec number, const BigDec &exp, const__C_BigDec mod);

        friend BigDec modularPower(const__C_BigDec number, BigDec &&exp, const BigDec &mod);
        friend BigDec modularPower(const__C_BigDec number, BigDec &&exp, BigDec &&mod);
        friend BigDec modularPower(const__C_BigDec number, BigDec &&exp, const__C_BigDec mod);

        friend BigDec modularPower(const__C_BigDec number, const__C_BigDec exp, const BigDec &mod);
        friend BigDec modularPower(const__C_BigDec number, const__C_BigDec exp, BigDec &&mod);
        friend BigDec modularPower(const__C_BigDec number, const__C_BigDec exp, const__C_BigDec mod);

        friend BigDec modularPower(const__C_BigDec number, const BigDec &exp, const BigDec &mod);
        friend BigDec modularPower(const__C_BigDec number, const BigDec &exp, const__C_BigDec mod);
        friend BigDec modularPower(const__C_BigDec number, const__C_BigDec exp, const BigDec &mod);
        friend BigDec modularPower(const__C_BigDec number, const__C_BigDec exp, const__C_BigDec mod);

        friend BigDec abs(const BigDec &number) noexcept;
        friend BigDec abs(BigDec &&number);
        friend BigDec abs(const__C_BigDec number);

        //----------------------------------------------------

        template <class T>
        operator T*()
        {
            return static_cast<T*>(value);
        }

        C_BigDec c_BigDec() noexcept;

        class ExcWrongNumber: public std::exception
        {
        public:
            ExcWrongNumber(const__C_BigDec value, int functionLine);
            const char* what() const noexcept;

        };
    };
}

#endif
