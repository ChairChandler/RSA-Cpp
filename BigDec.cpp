#include "BigDec.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>

namespace BigDec_NS
{
    BigDec::BigDec() noexcept
    {
        this->isValueMalloc=false;
        this->value=new char[2];
        this->value[0]='0';
        this->value[1]='\0';
    }

    BigDec::BigDec(std::string value)
    {
        try
        {
            BigDec::checkValue(value.c_str(), __LINE__);

            size_t len;
            len=value.size();

            this->isValueMalloc=false;
            this->value=new char[len+1];

            for(size_t i=0; i<len; i++)
            {
                this->value[i]=value[i];
            }

            this->value[len]='\0';
        }
        catch(BigDec::ExcWrongNumber)
        {
            this->isValueMalloc=false;
            this->value=new char[2];
            this->value[0]='0';
            this->value[1]='\0';

            throw;
        }
    }

    BigDec::BigDec(C_BigDec value)
    {
        try
        {
            BigDec::checkValue(value, __LINE__);


            size_t len;
            len=strlen(value);

            this->isValueMalloc=false;
            this->value=new char[len+1];

            for(size_t i=0;i<len;i++)
            {
                this->value[i]=value[i];
            }

            this->value[len]='\0';

            C_BigDec_delete(value);
        }
        catch(BigDec::ExcWrongNumber)
        {
            this->isValueMalloc=false;
            this->value=new char[2];
            this->value[0]='0';
            this->value[1]='\0';

            throw;
        }
    }

    BigDec::BigDec(const__C_BigDec value)
    {
        try
        {
            BigDec::checkValue(value, __LINE__);


            size_t len;
            len=strlen(value);

            this->isValueMalloc=false;
            this->value=new char[len+1];

            for(size_t i=0;i<len;i++)
            {
                this->value[i]=value[i];
            }

            this->value[len]='\0';
        }
        catch(BigDec::ExcWrongNumber)
        {
            this->isValueMalloc=false;
            this->value=new char[2];
            this->value[0]='0';
            this->value[1]='\0';

            throw;
        }
    }

    BigDec::~BigDec() noexcept
    {
        this->deleteValue();
    }

    BigDec::BigDec(const BigDec &number) noexcept
    {
        size_t nb_len;

        nb_len=strlen(number.value);

        this->isValueMalloc=number.isValueMalloc;
        this->value=new char[nb_len+1];

        strncpy_s(this->value, nb_len+1, number.value, nb_len+1);
    }

    //----------------------------------------------------

    BigDec BigDec::operator+(const BigDec &number) noexcept
    {
        return BigDec(C_BigDec_add(*this, const_cast<BigDec&>(number)));
    }

    BigDec BigDec::operator+(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            return BigDec(C_BigDec_add(*this, number));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec operator+(const__C_BigDec number1, const BigDec &number2)
    {
        try
        {
            BigDec::checkValue(number1, __LINE__);

            return BigDec(C_BigDec_add(number1, const_cast<BigDec&>(number2)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //----------------------------------------------------

    BigDec& BigDec::operator=(const BigDec &number) noexcept
    {
        if(this == &number)
        {
            return *this;
        }
        else
        {
            size_t nb_len;
            nb_len=strlen(number.value);

            this->deleteValue();

            this->isValueMalloc=number.isValueMalloc;
            this->value=new char[nb_len+1];

            strncpy_s(this->value, nb_len+1, number.value, nb_len+1);

            return *this;
        }
    }

    void BigDec::operator+=(const BigDec &number) noexcept
    {
        C_BigDec ptr;
        ptr=C_BigDec_add(*this, const_cast<BigDec&>(number));

        this->deleteValue();
        this->isValueMalloc=true;
        this->value=ptr;
    }

    BigDec& BigDec::operator=(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);


            size_t nb_len;
            nb_len=strlen(number);

            this->deleteValue();

            this->isValueMalloc=true;
            this->value=new char[nb_len+1];

            strncpy_s(this->value, nb_len+1, number, nb_len+1);

            return *this;
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    void BigDec::operator+=(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            C_BigDec ptr;
            ptr=C_BigDec_add(*this, number);

            this->deleteValue();
            this->isValueMalloc=true;
            this->value=ptr;
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //----------------------------------------------------

    BigDec& BigDec::operator++() noexcept
    {
        this->isValueMalloc=true;
        this->value=C_BigDec_add(*this, "1");
        return *this;
    }

    BigDec BigDec::operator++(int) noexcept
    {
        BigDec tmp(*this);
        ++(*this);
        return tmp;
    }

    //----------------------------------------------------

    std::ostream& operator<<(std::ostream &os, const BigDec &number)
    {
        try
        {
            os<<number.value;
            return os;
        }
        catch(...)
        {
            throw;
        }
    }

    std::istream& operator>>(std::istream &os, BigDec &number)
    {
        std::string tmp;
        size_t len;
        os>>tmp;

        try
        {
            BigDec::checkValue(tmp.c_str(), __LINE__);

            len=tmp.size();

            number.deleteValue();
            number.value=new char[len+1];
            number.isValueMalloc=false;

            for(size_t i=0; i<len; i++)
            {
                number.value[i]=tmp[i];
            }

            number.value[len]='\0';
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
        catch(...)
        {
            throw;
        }

        return os;
    }

    std::ostream& operator<<(std::ostream &os, BigDec &&number)
    {
        try
        {
            os<<number.value;
            return os;
        }
        catch(...)
        {
            throw;
        }
    }

    std::istream& operator>>(std::istream &os, BigDec &&number)
    {
        std::string tmp;
        size_t len;
        os>>tmp;

        try
        {
            BigDec::checkValue(tmp.c_str(), __LINE__);

            len=tmp.size();

            number.deleteValue();
            number.value=new char[len+1];
            number.isValueMalloc=false;

            for(size_t i=0; i<len; i++)
            {
                number.value[i]=tmp[i];
            }

            number.value[len]='\0';
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
        catch(...)
        {
            throw;
        }

        return os;
    }

    //----------------------------------------------------

    void BigDec::deleteValue()
    {
        if(this->isValueMalloc)
        {
            C_BigDec_delete(this->value);
        }
        else
        {
            delete[] this->value;
        }
    }

    //----------------------------------------------------

    BigDec BigDec::operator-(BigDec &number) noexcept
    {
        return BigDec(C_BigDec_sub(*this,number));
    }

    BigDec operator-(const__C_BigDec number1, const BigDec &number2)
    {
        try
        {
            BigDec::checkValue(number1, __LINE__);

            return BigDec(C_BigDec_sub(number1, const_cast<BigDec&>(number2)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec BigDec::operator-(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            return BigDec(C_BigDec_sub(*this, number));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //----------------------------------------------------

    void BigDec::operator-=(const BigDec &number) noexcept
    {
        C_BigDec ptr;
        ptr=C_BigDec_sub(*this, const_cast<BigDec&>(number));

        this->deleteValue();
        this->isValueMalloc=true;
        this->value=ptr;
    }

    void BigDec::operator-=(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            C_BigDec ptr;
            ptr=C_BigDec_sub(*this, number);

            this->deleteValue();
            this->isValueMalloc=true;
            this->value=ptr;
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //----------------------------------------------------

    BigDec BigDec::operator*(const BigDec &number) noexcept
    {
        return BigDec(C_BigDec_mul(*this, const_cast<BigDec&>(number)));
    }

    BigDec BigDec::operator*(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            return BigDec(C_BigDec_mul(*this, number));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec operator*(const__C_BigDec number1, const BigDec &number2)
    {
        try
        {
            BigDec::checkValue(number1, __LINE__);

            return BigDec(C_BigDec_mul(number1, const_cast<BigDec&>(number2)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //----------------------------------------------------

    void BigDec::operator*=(const BigDec &number) noexcept
    {
        C_BigDec ptr;
        ptr=C_BigDec_mul(*this, const_cast<BigDec&>(number));

        deleteValue();
        this->isValueMalloc=true;
        this->value=ptr;
    }

    void BigDec::operator*=(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            C_BigDec ptr;
            ptr=C_BigDec_mul(*this, number);

            this->deleteValue();
            this->isValueMalloc=true;
            this->value=ptr;
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //----------------------------------------------------

    BigDec BigDec::operator/(const BigDec &number) noexcept
    {
        return BigDec(C_BigDec_div(*this, const_cast<BigDec&>(number)));
    }

    BigDec BigDec::operator/(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            return BigDec(C_BigDec_div(*this, number));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec operator/(const__C_BigDec number1, const BigDec &number2)
    {
        try
        {
            BigDec::checkValue(number1, __LINE__);

            return BigDec(C_BigDec_div(number1, const_cast<BigDec&>(number2)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //----------------------------------------------------

    void BigDec::operator/=(const BigDec &number) noexcept
    {
        C_BigDec ptr;
        ptr=C_BigDec_div(*this, const_cast<BigDec&>(number));

        this->deleteValue();
        this->isValueMalloc=true;
        this->value=ptr;
    }

    //----------------------------------------------------

    void BigDec::operator/=(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            C_BigDec ptr;
            ptr=C_BigDec_div(*this, number);

            this->deleteValue();
            this->isValueMalloc=true;
            this->value=ptr;
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //----------------------------------------------------

    BigDec BigDec::operator^(unsigned long long exp) noexcept
    {
        return BigDec(C_BigDec_pow(*this, exp));
    }

    //----------------------------------------------------

    void BigDec::operator^=(unsigned long long exp) noexcept
    {
        C_BigDec ptr;
        ptr=C_BigDec_pow(*this, exp);

        this->deleteValue();
        this->isValueMalloc=true;
        this->value=ptr;
    }

    //----------------------------------------------------

    BigDec BigDec::operator%(const BigDec &number) noexcept
    {
        return BigDec(C_BigDec_mod(*this, const_cast<BigDec&>(number)));
    }

    BigDec BigDec::operator%(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            return BigDec(C_BigDec_mod(*this, number));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec operator%(const__C_BigDec number1, const BigDec &number2)
    {
        try
        {
            BigDec::checkValue(number1, __LINE__);

            return BigDec(C_BigDec_mod(number1, const_cast<BigDec&>(number2)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //----------------------------------------------------

    void BigDec::operator%=(const BigDec &number) noexcept
    {
        C_BigDec ptr;
        ptr=C_BigDec_mod(*this, const_cast<BigDec&>(number));

        this->deleteValue();
        this->isValueMalloc=true;
        this->value=ptr;
    }

    void BigDec::operator%=(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            C_BigDec ptr;
            ptr=C_BigDec_mod(*this, number);

            this->deleteValue();
            this->isValueMalloc=true;
            this->value=ptr;
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //----------------------------------------------------

    bool BigDec::operator>(const BigDec &number) noexcept
    {
        if(C_BigDec_isNegative(*this) && !C_BigDec_isNegative(const_cast<BigDec&>(number)))
        {
            return true;
        }
        else
        {
            return C_BigDec_cmp(*this, const_cast<BigDec&>(number)) == 1? true : false;
        }
    }

    bool BigDec::operator>(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            return C_BigDec_cmp(*this, number)  == 1? true : false;
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    bool operator>(const__C_BigDec number1, const BigDec &number2)
    {
        try
        {
            BigDec::checkValue(number1, __LINE__);

            return C_BigDec_cmp(number1, const_cast<BigDec&>(number2))  == 1? true : false;
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //----------------------------------------------------

    bool BigDec::operator>=(const BigDec &number) noexcept
    {
        if(*this > number)
        {
            return true;
        }
        else
        {
            return *this == number;
        }
    }

    bool BigDec::operator>=(const__C_BigDec number)
    {
        if(*this > number)
        {
            return true;
        }
        else
        {
            return *this == number;
        }
    }

    bool operator>=(const__C_BigDec number1, BigDec &number2)
    {
        if(number1 > number2)
        {
            return true;
        }
        else
        {
            return number1 == number2;
        }
    }

    //----------------------------------------------------

    bool BigDec::operator==(const BigDec &number) noexcept
    {
        if(C_BigDec_cmp(*this, const_cast<BigDec&>(number)) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool BigDec::operator==(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            if(C_BigDec_cmp(*this, number) == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    bool operator==(const__C_BigDec number1, const BigDec &number2)
    {
        try
        {
            BigDec::checkValue(number1, __LINE__);

            if(C_BigDec_cmp(number1, const_cast<BigDec&>(number2)) == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //----------------------------------------------------

    bool BigDec::operator!=(const BigDec &number) noexcept
    {
        if(*this == number)
            return false;
        else
            return true;
    }

    bool BigDec::operator!=(const__C_BigDec number)
    {
        if(*this == number)
            return false;
        else
            return true;
    }

    bool operator!=(const__C_BigDec number1, BigDec &number2)
    {
        if(number1 == number2)
            return false;
        else
            return true;
    }

    //----------------------------------------------------

    bool BigDec::operator<(const BigDec &number) noexcept
    {
        if(*this >= number)
            return false;
        else
            return true;
    }

    bool BigDec::operator<(const__C_BigDec number)
    {
        if(*this >= number)
            return false;
        else
            return true;
    }

    bool operator<(const__C_BigDec number1, BigDec &number2)
    {
        if(number1 >= number2)
            return false;
        else
            return true;
    }

    //----------------------------------------------------

    bool BigDec::operator<=(const BigDec &number) noexcept
    {
        if(*this > number)
            return false;
        else
            return true;
    }

    bool BigDec::operator<=(const__C_BigDec number)
    {
        if(*this > number)
            return false;
        else
            return true;
    }

    bool operator<=(const__C_BigDec number1, BigDec &number2)
    {
        if(number1 > number2)
            return false;
        else
            return true;
    }

    //----------------------------------------------------

    BigDec findGreatestCommonDivision(const BigDec &number1, const BigDec &number2) noexcept
    {
        try
        {
            BigDec::checkValue(number1, __LINE__);
            BigDec::checkValue(number2, __LINE__);

            return BigDec(C_BigDec_findGreatestCommonDivision(const_cast<BigDec&>(number1), const_cast<BigDec&>(number2)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec findGreatestCommonDivision(const BigDec &number1, const__C_BigDec number2)
    {
        try
        {
            BigDec::checkValue(number1, __LINE__);
            BigDec::checkValue(number2, __LINE__);

            return BigDec(C_BigDec_findGreatestCommonDivision(const_cast<BigDec&>(number1), number2));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec findGreatestCommonDivision(BigDec &&number1, const BigDec &number2)
    {
        try
        {
            BigDec::checkValue(number1, __LINE__);
            BigDec::checkValue(number2, __LINE__);

            return BigDec(C_BigDec_findGreatestCommonDivision(number1, const_cast<BigDec&>(number2)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec findGreatestCommonDivision(BigDec &&number1, const__C_BigDec number2)
    {
        try
        {
            BigDec::checkValue(number1, __LINE__);
            BigDec::checkValue(number2, __LINE__);

            return BigDec(C_BigDec_findGreatestCommonDivision(number1, number2));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec findGreatestCommonDivision(const__C_BigDec number1, const__C_BigDec number2)
    {
        try
        {
            BigDec::checkValue(number1, __LINE__);
            BigDec::checkValue(number2, __LINE__);

            return BigDec(C_BigDec_findGreatestCommonDivision(number1, number2));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //-------------------------------------------------

    BigDec generateRandomFirstNumber(const BigDec &number)
    {
        if(const_cast<BigDec&>(number) > "1")
        {
            BigDec::checkValue(number, __LINE__);

            return BigDec(C_BigDec_generateRandomFirstNumber(const_cast<BigDec&>(number)));
        }
        else
        {
            throw BigDec::ExcWrongNumber(number.value, __LINE__);
        }
    }

    BigDec generateRandomFirstNumber(BigDec &&number)
    {
        if(number > "1")
        {
            BigDec::checkValue(number, __LINE__);

            return BigDec(C_BigDec_generateRandomFirstNumber(number));
        }
        else
        {
            throw BigDec::ExcWrongNumber(number.value, __LINE__);
        }
    }

    BigDec generateRandomFirstNumber(const__C_BigDec number)
    {
        if(number > BigDec(const_cast<C_BigDec>("1")))
        {
            BigDec::checkValue(number, __LINE__);

            return BigDec(C_BigDec_generateRandomFirstNumber(number));
        }
        else
        {
            throw BigDec::ExcWrongNumber(number, __LINE__);
        }
    }

    //-------------------------------------------------

    BigDec modularPower(const BigDec &number, const BigDec &exp, const BigDec &mod) noexcept
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(const_cast<BigDec&>(number), const_cast<BigDec&>(exp), const_cast<BigDec&>(mod)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const BigDec &number, const BigDec &exp, const__C_BigDec mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(const_cast<BigDec&>(number), const_cast<BigDec&>(exp), mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const BigDec &number, const__C_BigDec exp, const BigDec &mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(const_cast<BigDec&>(number), exp, const_cast<BigDec&>(mod)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const BigDec &number, const__C_BigDec exp, const__C_BigDec mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(const_cast<BigDec&>(number), exp, mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //--------------------------------------------------


    BigDec modularPower(BigDec &&number, const BigDec &exp, const BigDec &mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, const_cast<BigDec&>(exp), const_cast<BigDec&>(mod)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(BigDec &&number, const BigDec &exp, const__C_BigDec mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, const_cast<BigDec&>(exp), mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(BigDec &&number, const__C_BigDec exp, const BigDec &mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, exp, const_cast<BigDec&>(mod)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(BigDec &&number, const__C_BigDec exp, const__C_BigDec mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, exp, mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //--------------------------------------------------


    BigDec modularPower(const__C_BigDec number, const BigDec &exp, const BigDec &mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, const_cast<BigDec&>(exp), const_cast<BigDec&>(mod)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const__C_BigDec number, const BigDec &exp, const__C_BigDec mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, const_cast<BigDec&>(exp), mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const__C_BigDec number, const__C_BigDec exp, const BigDec &mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, exp, const_cast<BigDec&>(mod)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const__C_BigDec number, const__C_BigDec exp, const__C_BigDec mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, exp, mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const BigDec &number, const BigDec &exp, BigDec &&mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(const_cast<BigDec&>(number), const_cast<BigDec&>(exp), mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const BigDec &number, BigDec &&exp, const BigDec &mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(const_cast<BigDec&>(number), exp, const_cast<BigDec&>(mod)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const BigDec &number, BigDec &&exp, BigDec &&mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(const_cast<BigDec&>(number), exp, mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const BigDec &number, BigDec &&exp, const__C_BigDec mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(const_cast<BigDec&>(number), exp, mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const BigDec &number, const__C_BigDec exp, BigDec &&mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(const_cast<BigDec&>(number), exp, mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(BigDec &&number, const BigDec &exp, BigDec &&mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, const_cast<BigDec&>(exp), mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(BigDec &&number, BigDec &&exp, const BigDec &mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, exp, const_cast<BigDec&>(mod)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(BigDec &&number, BigDec &&exp, BigDec &&mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, exp, mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(BigDec &&number, BigDec &&exp, const__C_BigDec mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, exp, mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(BigDec &&number, const__C_BigDec exp, BigDec &&mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, exp, mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const__C_BigDec number, const BigDec &exp, BigDec &&mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, const_cast<BigDec&>(exp), mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const__C_BigDec number, BigDec &&exp, const BigDec &mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, exp, const_cast<BigDec&>(mod)));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const__C_BigDec number, BigDec &&exp, BigDec &&mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, exp, mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const__C_BigDec number, BigDec &&exp, const__C_BigDec mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, exp, mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec modularPower(const__C_BigDec number, const__C_BigDec exp, BigDec &&mod)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);
            BigDec::checkValue(exp, __LINE__);
            BigDec::checkValue(mod, __LINE__);

            return BigDec(C_BigDec_modularPower(number, exp, mod));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }


    //--------------------------------------------------

    BigDec abs(BigDec &number) noexcept
    {
        return BigDec(C_BigDec_abs(number));
    }

    BigDec abs(BigDec &&number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            return BigDec(C_BigDec_abs(number));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    BigDec abs(const__C_BigDec number)
    {
        try
        {
            BigDec::checkValue(number, __LINE__);

            return BigDec(C_BigDec_abs(number));
        }
        catch(BigDec::ExcWrongNumber)
        {
            throw;
        }
    }

    //--------------------------------------------------
    void BigDec::checkValue(const__C_BigDec number, int functionLine)
    {
        for(size_t i=0; i<strlen(number); i++)
        {
            if(!((number[i] == '-' && i==0) || (number[i] >= '0' && number[i] <= '9') ))
            {
                throw BigDec::ExcWrongNumber(number, functionLine);
            }
        }
    }

    void BigDec::checkValue(const BigDec &number, int functionLine)
    {
        for(size_t i=0; i<strlen(number.value); i++)
        {
            if(!((number.value[i] == '-' && i==0) || (number.value[i] >= '0' && number.value[i] <= '9') ))
            {
                throw BigDec::ExcWrongNumber(number.value, functionLine);
            }
        }
    }

    void BigDec::checkValue(BigDec &&number, int functionLine)
    {
        for(size_t i=0; i<strlen(number.value); i++)
        {
            if(!((number.value[i] == '-' && i==0) || (number.value[i] >= '0' && number.value[i] <= '9') ))
            {
                throw BigDec::ExcWrongNumber(number.value, functionLine);
            }
        }
    }

    C_BigDec BigDec::c_BigDec() noexcept
    {
        C_BigDec copy;

        copy=C_BigDec_new(-1, strlen(*this));
        C_BigDec_assign(&copy, *this);

        return copy;
    }

    //----------------------------------------------------

    BigDec::ExcWrongNumber::ExcWrongNumber(const__C_BigDec value, int functionLine): std::exception ()
    {
        std::cerr<<"LINE "<<functionLine<<" : "<<value<<std::endl;
        std::cerr<<this->what()<<std::endl;
    }

    const char* BigDec::ExcWrongNumber::what() const noexcept
    {
        return "Wrong value ";
    }
}
