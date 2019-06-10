#include "C_BigDec.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

static void C_BigDec_swapNumbers(C_BigDec *number1, C_BigDec *number2)
{
    C_BigDec hlpPtr;


    hlpPtr=*number1;
    *number1=*number2;
    *number2=hlpPtr;
}

static void C_BigDec_swapLengths(size_t *number1_length, size_t *number2_length)
{
    *number1_length^=*number2_length;
    *number2_length^=*number1_length;
    *number1_length^=*number2_length;
}

static size_t C_BigDec_len(C_BigDec number1)
{
    return strlen(number1);
}

static C_BigDec C_BigDec_deleteZeroes(C_BigDec number, size_t length)
{
    C_BigDec returnNumber;

    if(number[0] == '0')
    {
        size_t counter;
        counter=0;

        while(number[counter] == '0' && counter != length-1)
        {
            counter++;
        }

        returnNumber=C_BigDec_new(-1, length-counter);

        C_BigDec_assign(&returnNumber, number+counter);


        if(!strcmp(returnNumber, ""))
        {
            C_BigDec_delete(returnNumber);

            returnNumber=C_BigDec_new(-1, 1);
            C_BigDec_assign(&number, "0");
        }

        return returnNumber;
    }
    else
    {
        returnNumber=C_BigDec_new(-1, length);
        C_BigDec_assign(&returnNumber, number);

        return returnNumber;
    }
}

static C_BigDec C_BigDec_powRes(C_BigDec base, unsigned long long exp)
{
    if(exp == 0)
    {
        C_BigDec a;

        a=C_BigDec_new(-1, 1);
        C_BigDec_assign(&a, "1");

        return a;
    }
    else if(exp%2 == 0)
    {
        C_BigDec a, b;

        a=C_BigDec_powRes(base, exp/2);
        b=C_BigDec_mul(a, a);
        C_BigDec_delete(a);

        return b;
    }
    else
    {
        C_BigDec a, b;

        a=C_BigDec_powRes(base, exp-1);
        b=C_BigDec_mul(a, base);
        C_BigDec_delete(a);

        return b;
    }
}

C_BigDec C_BigDec_modularPower(C_BigDec number, C_BigDec exp, C_BigDec mod)
{
    if(C_BigDec_cmp(exp, "1") == 0)
    {
        return number;
    }
    else
    {
        C_BigDec val, aux, tmp, delPtr;
        val=C_BigDec_mod(exp, "2");


        if(C_BigDec_cmp(val, "0") == 0)
        {
            C_BigDec_delete(val);

            tmp=C_BigDec_div(exp, "2");
            aux=C_BigDec_modularPower(number, tmp, mod);

            C_BigDec_delete(tmp);

            tmp=C_BigDec_mul(aux, aux);



            if(aux != number)
            {
                C_BigDec_delete(aux);
            }



            delPtr=tmp;
            tmp=C_BigDec_mod(tmp, mod);

            C_BigDec_delete(delPtr);

            return tmp;
        }
        else
        {
            C_BigDec_delete(val);


            tmp=C_BigDec_div(exp, "2");
            aux=C_BigDec_modularPower(number, tmp, mod);

            C_BigDec_delete(tmp);

            delPtr=aux;
            aux=C_BigDec_mul(aux, aux);



            if(delPtr != number)
            {
                C_BigDec_delete(delPtr);
            }



            delPtr=aux;
            aux=C_BigDec_mul(aux, number);

            C_BigDec_delete(delPtr);

            delPtr=aux;
            aux=C_BigDec_mod(aux, mod);

            C_BigDec_delete(delPtr);

            return aux;
        }
    }
}

C_BigDec C_BigDec_new(int sign, size_t digits)
{
    C_BigDec number = NULL;
    size_t size;

    size=(sign == 0? 1:0) + digits + 1;
    number=(C_BigDec)malloc(sizeof(char) * size);

    if(number == NULL)
    {
        perror(strerror(errno));
        abort();
    }

    if(sign == 0)
    {
        number[0]='-';
    }

    number[size-1]='\0';

    return number;
}

void C_BigDec_delete(C_BigDec number)
{
    free(number);
}

C_BigDec C_BigDec_add(C_BigDec number1, C_BigDec number2)
{
    C_BigDec hlpPtr, returnNumber;
    int aux, isNegativeNumber;

    isNegativeNumber= -1;



    if(!C_BigDec_isNegative(number1) && !C_BigDec_isNegative(number2) )
    {
        number1=number1+1;
        number2=number2+1;

        isNegativeNumber=0;
    }
    else if(!C_BigDec_isNegative(number1))
    {
        return C_BigDec_sub(number2, number1+1);
    }
    else if(!C_BigDec_isNegative(number2))
    {
        return C_BigDec_sub(number1, number2+1);
    }




    size_t number1_length, number2_length;
    number1_length=C_BigDec_len(number1);
    number2_length=C_BigDec_len(number2);

    if(number1_length < number2_length)
    {
        C_BigDec_swapNumbers(&number1, &number2);

        C_BigDec_swapLengths(&number1_length, &number2_length);
    }



    returnNumber=C_BigDec_new(-1, number1_length+2);
    returnNumber[number1_length+1]='\0';
    aux=0;



    for(int i=(int)number1_length-1, j=(int)number2_length-1; i >= 0; i--)
    {
        if(j >= 0)
        {
            aux+=(number1[i]-'0')+(number2[j]-'0');
            j--;
        }
        else
        {
            aux+=number1[i]-'0';
        }

        returnNumber[i+1]=aux%10+'0';
        aux/=10;
    }



    returnNumber[0]=(char)aux+'0';

    hlpPtr=returnNumber;
    returnNumber=C_BigDec_deleteZeroes(returnNumber, number1_length+2);

    C_BigDec_delete(hlpPtr);


    if(!isNegativeNumber)
    {
        hlpPtr=C_BigDec_new(0, C_BigDec_len(returnNumber));

        memcpy(hlpPtr+1, returnNumber, sizeof(char) * strlen(returnNumber));


        C_BigDec_delete(returnNumber);
        returnNumber=hlpPtr;
    }



    return returnNumber;
}

C_BigDec C_BigDec_sub(C_BigDec number1, C_BigDec number2)
{
    C_BigDec hlpPtr, returnNumber;
    size_t number1_length, number2_length, returnNumber_length;
    int isNumber1Negative, isNumber2Negative, isReturnNumberNegative;
    int eq, rest;


    isReturnNumberNegative= -1;



    if(!C_BigDec_isNegative(number1))
    {
        isNumber1Negative=0;
        number1=number1+1;
    }
    else
    {
        isNumber1Negative= -1;
    }


    if(!C_BigDec_isNegative(number2))
    {
        isNumber2Negative=0;
        number2=number2+1;
    }
    else
    {
        isNumber2Negative= -1;
    }




    if(isNumber1Negative == -1 && isNumber2Negative == 0)
    {
        return C_BigDec_add(number1, number2);
    }
    else if(isNumber1Negative == 0 && isNumber2Negative == 0)
    {
        C_BigDec_swapNumbers(&number1, &number2);
    }
    else if(isNumber1Negative == 0 && isNumber2Negative == -1)
    {
        hlpPtr=C_BigDec_add(number1, number2);

        returnNumber=C_BigDec_new(0, C_BigDec_len(hlpPtr));

        memcpy(returnNumber+1, hlpPtr, sizeof(char) * strlen(returnNumber));

        return returnNumber;
    }





    number1_length=C_BigDec_len(number1);
    number2_length=C_BigDec_len(number2);


    //Now there is only unsigned numbers
    //First will be always positive
    //Second will be always negative

    if(number1_length < number2_length)
    {
        C_BigDec_swapNumbers(&number1, &number2);

        C_BigDec_swapLengths(&number1_length, &number2_length);

        isReturnNumberNegative=0;
    }
    else if(number1_length == number2_length)
    {
        for(int i=0; number1[i] != '\0'; i++)
        {
            if(number1[i] > number2[i])
            {
                break;
            }

            if(number1[i] < number2[i])
            {
                C_BigDec_swapNumbers(&number1, &number2);

                C_BigDec_swapLengths(&number1_length, &number2_length);

                isReturnNumberNegative=0;
                break;
            }
        }
    }




    returnNumber=C_BigDec_new(-1, number1_length);


    rest=0;


    for(int i=(int)number1_length-1, j=(int)number2_length-1, z=(int)number1_length-1; i >= 0; i--, z--)
    {
        if(j >= 0)
        {
            eq=(number1[i]-'0')-(number2[j]-'0')+rest;
            j--;
        }
        else
        {
            eq=number1[i]-'0'+rest;
        }

        rest=0;

        if(eq < 0)
        {
            eq+=10;
            rest--;
        }

        returnNumber[z]=(char)eq+'0';
    }



    returnNumber_length=C_BigDec_len(returnNumber);

    hlpPtr=returnNumber;
    returnNumber=C_BigDec_deleteZeroes(returnNumber, returnNumber_length);

    C_BigDec_delete(hlpPtr);


    if(!isReturnNumberNegative)
    {
        hlpPtr=C_BigDec_new(0, C_BigDec_len(returnNumber));

        memcpy(hlpPtr+1, returnNumber, sizeof(char) * strlen(returnNumber));

        C_BigDec_delete(returnNumber);
        returnNumber=hlpPtr;
    }


    return returnNumber;
}

C_BigDec C_BigDec_mul(C_BigDec number1, C_BigDec number2)
{
    C_BigDec returnNumber, hlpPtr;
    size_t number1_length, number2_length, returnNumber_length, lastNr1, lastNr2, lastNr3;
    int aux, isReturnNumberNegative;



    number1_length=C_BigDec_len(number1);
    number2_length=C_BigDec_len(number2);
    returnNumber_length=number1_length + number2_length;

    isReturnNumberNegative= -1;


    if(!C_BigDec_isNegative(number1) && !C_BigDec_isNegative(number2))
    {
        number1=number1+1;
        number1_length--;

        number2=number2+1;
        number2_length--;

        returnNumber_length--;
        returnNumber_length--;
    }
    else if(!C_BigDec_isNegative(number1))
    {
        number1=number1+1;
        number1_length--;
        returnNumber_length--;
        isReturnNumberNegative=0;
    }
    else if(!C_BigDec_isNegative(number2))
    {
        number2=number2+1;
        number2_length--;
        returnNumber_length--;
        isReturnNumberNegative=0;
    }





    if(C_BigDec_len(number1) < C_BigDec_len(number2))
    {
        C_BigDec_swapNumbers(&number1, &number2);

        C_BigDec_swapLengths(&number1_length, &number2_length);
    }





    returnNumber=C_BigDec_new(-1, returnNumber_length);


    for(int i=0; i < (int)returnNumber_length; i++)
    {
        returnNumber[i]='0';
    }


    lastNr1=number1_length-1;
    lastNr2=number2_length-1;
    lastNr3=returnNumber_length-1;



    for(int i=(int)lastNr2, j; i >= 0; i--)
    {
        aux=0;



        for(j=(int)lastNr1; j >= 0; j--)
        {
            aux=aux+(number2[i]-'0')*(number1[j]-'0');
            returnNumber[lastNr3    -   (lastNr2-(size_t)i)    -   (lastNr1-(size_t)j)] += aux%10;

            aux/=10;

            if(returnNumber[lastNr3 -   (lastNr2-(size_t)i) -   (lastNr1-(size_t)j)]    -'0' > 9)
            {
                aux+=(returnNumber[lastNr3  -   (lastNr2-(size_t)i) -   (lastNr1-(size_t)j)]    -   '0')/10;


                returnNumber[lastNr3    -   (lastNr2-(size_t)i) -   (lastNr1-(size_t)j)]=
                        (returnNumber[lastNr3   -   (lastNr2-(size_t)i) -   (lastNr1-(size_t)j)]    -   '0')%10+'0';
            }
        }



        if(aux)
        {
            returnNumber[lastNr3-(lastNr2-(size_t)i)-(lastNr1-(size_t)j)]+=aux;
        }
    }



    hlpPtr=returnNumber;
    returnNumber=C_BigDec_deleteZeroes(returnNumber, returnNumber_length);

    C_BigDec_delete(hlpPtr);



    if(!isReturnNumberNegative)
    {
        if(returnNumber[0] == '0')
        {
            returnNumber[0]='-';
        }
        else
        {
            hlpPtr=C_BigDec_new(0, strlen(returnNumber));

            memcpy(hlpPtr+1, returnNumber, sizeof(char) * strlen(returnNumber));

            C_BigDec_delete(returnNumber);
            returnNumber=hlpPtr;
        }
    }


    return returnNumber;
}

C_BigDec C_BigDec_div(C_BigDec number1, C_BigDec number2)
{
    C_BigDec hlpPtr, returnNumber, delPtr, q, pop;
    C_BigDec absNumber1, absNumber2;
    size_t number1_length, number2_length, returnNumber_length;
    int ans, isNumber1Negative, isNumber2Negative;
    char buff[2];

    pop=NULL;

    if(!C_BigDec_cmp(number2, "0"))
    {
        fprintf(stderr,"[ERROR] Division by 0.");
        return NULL;
    }
    else
    {
        if(!C_BigDec_isNegative(number1))
        {
            isNumber1Negative=0;
            number1=number1+1;
        }
        else
        {
            isNumber1Negative= -1;
        }




        if(!C_BigDec_isNegative(number2))
        {
            isNumber2Negative=0;
            number2=number2+1;
        }
        else
        {
            isNumber2Negative= -1;
        }




        absNumber1=C_BigDec_abs(number1);
        absNumber2=C_BigDec_abs(number2);

        ans=C_BigDec_cmp(absNumber1, absNumber2);

        C_BigDec_delete(absNumber1);
        C_BigDec_delete(absNumber2);




        if(ans == -1)
        {
            hlpPtr=C_BigDec_new(-1, 1);
            C_BigDec_assign(&hlpPtr, "0");
            return hlpPtr;
        }
        else if(ans == 0 && ((isNumber1Negative && !isNumber2Negative) || (!isNumber1Negative && isNumber2Negative)))
        {
            hlpPtr=C_BigDec_new(0, 1);
            C_BigDec_assign(&hlpPtr, "-1");
            return hlpPtr;
        }
        else if(ans == 0 && ((isNumber1Negative && isNumber2Negative) || (!isNumber1Negative && !isNumber2Negative)))
        {
            hlpPtr=C_BigDec_new(0, 1);
            C_BigDec_assign(&hlpPtr, "1");
            return hlpPtr;
        }
        else
        {
            number1_length=C_BigDec_len(number1);
            number2_length=C_BigDec_len(number2);
            returnNumber_length=number1_length;



            hlpPtr=C_BigDec_new(-1, number2_length);
            returnNumber=C_BigDec_new(-1, returnNumber_length);


            memset(returnNumber, '0', returnNumber_length);




            for(int i=0, j=0; i < (int)number1_length; i++)
            {
                hlpPtr[j]=number1[i];
                hlpPtr[j+1]='\0';

                if(j+1 < (int)number2_length)
                {
                    returnNumber[i]='0';
                    j++;
                    continue;
                }
                else if(C_BigDec_cmp(hlpPtr, number2) == -1)
                {
                    returnNumber[i]='0';
                    j++;
                    continue;
                }
                else
                {
                    for(int z=1; z <= 9; z++)
                    {
                        delPtr=hlpPtr;
                        hlpPtr=C_BigDec_deleteZeroes(hlpPtr, C_BigDec_len(hlpPtr));

                        C_BigDec_delete(delPtr); //Kernel issue?


                        sprintf(buff, "%d", z);

                        q=C_BigDec_mul(number2, buff);

                        if(C_BigDec_cmp(hlpPtr, q) == 0)
                        {
                            returnNumber[i]=(char)z+'0';

                            C_BigDec_delete(q);
                            j=0;

                            break;
                        }
                        else if(z == 9 && C_BigDec_cmp(hlpPtr, q) == 1)
                        {
                            returnNumber[i]=(char)z+'0';

                            delPtr=q;
                            q=C_BigDec_sub(hlpPtr, q);
                            C_BigDec_delete(delPtr);



                            C_BigDec_assign(&hlpPtr, q);
                            j=(int)C_BigDec_len(q);
                        }
                        else if(z > 1 && C_BigDec_cmp(hlpPtr, pop) == 1 && C_BigDec_cmp(hlpPtr, q) == -1)
                        {
                            returnNumber[i]=(char)(z-1)+'0';

                            delPtr=q;
                            q=C_BigDec_sub(hlpPtr, pop);
                            C_BigDec_delete(delPtr);

                            C_BigDec_assign(&hlpPtr, q);
                            j=(int)C_BigDec_len(q);

                            C_BigDec_delete(q);
                            break;
                        }


                        if(pop != NULL)
                        {
                            C_BigDec_delete(pop);
                        }

                        pop=q;
                    }
                }
            }






            if(pop != NULL)
            {
                C_BigDec_delete(pop);
            }

            C_BigDec_delete(hlpPtr);


            delPtr=returnNumber;
            returnNumber=C_BigDec_deleteZeroes(returnNumber,returnNumber_length);

            C_BigDec_delete(delPtr);



            if((!isNumber1Negative && isNumber2Negative) || (isNumber1Negative && !isNumber2Negative))
            {
                hlpPtr=C_BigDec_new(0, C_BigDec_len(returnNumber));
                memcpy(hlpPtr+1, returnNumber, sizeof(char) * strlen(returnNumber));


                C_BigDec_delete(returnNumber);
                returnNumber=hlpPtr;
            }


            return returnNumber;
        }
    }
}

C_BigDec C_BigDec_pow(C_BigDec base, unsigned long long exp)
{
    if(!C_BigDec_isNegative(base))
    {
        C_BigDec number, returnNumber;
        size_t base_length, result_length;

        base_length=C_BigDec_len(base);
        number=C_BigDec_new(-1, base_length-1);


        C_BigDec_assign(&number, base+1);


        base=number;
        number=C_BigDec_powRes(base, exp);
        C_BigDec_delete(base);




        result_length=C_BigDec_len(number);


        if(exp%2 == 1)
        {
            returnNumber=C_BigDec_new(0, result_length);

            memcpy(returnNumber+1, number, sizeof(char) * strlen(number));
        }
        else
        {
            returnNumber=C_BigDec_new(-1, result_length);
            C_BigDec_assign(&returnNumber, number);
        }

        return returnNumber;
    }
    else
    {
        return C_BigDec_powRes(base, exp);
    }
}

C_BigDec C_BigDec_mod(C_BigDec number1, C_BigDec number2)
{
    C_BigDec absNumber1, absNumber2;
    C_BigDec remainder, divResult, mulResult;
    int isNumber1Negative, isNumber2Negative;
    int ans;


    absNumber1=C_BigDec_abs(number1);
    absNumber2=C_BigDec_abs(number2);

    ans=C_BigDec_cmp(absNumber1, absNumber2);

    isNumber1Negative=C_BigDec_isNegative(number1);
    isNumber2Negative=C_BigDec_isNegative(number2);

    if(ans == -1)
    {
        return absNumber1;
    }
    else if(ans == 0)
    {
        remainder=C_BigDec_new(-1, 1);
        C_BigDec_assign(&remainder, "0");

        return remainder;
    }


    divResult=C_BigDec_div(number1, number2);
    mulResult=C_BigDec_mul(divResult, number2);
    remainder=C_BigDec_sub(number1, mulResult);



    C_BigDec_delete(divResult);
    C_BigDec_delete(mulResult);
    C_BigDec_delete(absNumber1);
    C_BigDec_delete(absNumber2);

    absNumber1=C_BigDec_abs(remainder);
    C_BigDec_delete(remainder);

    remainder=absNumber1;
    return remainder;
}

C_BigDec C_BigDec_findGreatestCommonDivision(C_BigDec number1, C_BigDec number2)
{
    C_BigDec a, b, c;

    a=C_BigDec_new(-1, C_BigDec_len(number1));
    b=C_BigDec_new(-1, C_BigDec_len(number2));
    c=NULL;


    C_BigDec_assign(&a, number1);
    C_BigDec_assign(&b, number2);




    while(C_BigDec_cmp(b, "0"))
    {
        c=C_BigDec_mod(a, b);
        C_BigDec_delete(a);
        a=b;
        b=c;
    }



    C_BigDec_delete(b);
    return a;
}

C_BigDec C_BigDec_generateRandomFirstNumber(C_BigDec startNumber)
{
    C_BigDec returnNumber, gcd, delPtr;

    gcd=NULL;
    returnNumber=C_BigDec_new(-1, 1);
    C_BigDec_assign(&returnNumber, "3");



    while(C_BigDec_cmp(startNumber, returnNumber))
    {
        if(gcd != NULL)
        {
            C_BigDec_delete(gcd);
        }

        gcd=C_BigDec_findGreatestCommonDivision(startNumber, returnNumber);

        if(!C_BigDec_cmp(gcd, "1"))
        {
            break;
        }
        else
        {
            delPtr=returnNumber;
            returnNumber=C_BigDec_add(returnNumber, "1");
            C_BigDec_delete(delPtr);
        }
    }



    C_BigDec_delete(gcd);
    return returnNumber;
}

int C_BigDec_cmp(C_BigDec number1, C_BigDec number2)
{
    size_t number1_length, number2_length;

    number1_length=C_BigDec_len(number1);
    number2_length=C_BigDec_len(number2);



    if(!C_BigDec_isNegative(number1) && C_BigDec_isNegative(number2))
    {
        //number1 is negative
        //number2 is positive
        return -1;
    }
    else if(C_BigDec_isNegative(number1) && !C_BigDec_isNegative(number2))
    {
        //number1 is positive
        //number2 is negative
        return 1;
    }
    else
    {
        if(number1_length > number2_length)
        {
            return 1;
        }
        else if(number1_length < number2_length)
        {
            return -1;
        }
        else
        {
            for(size_t i=0; i<number1_length; i++)
            {
                if(number1[i] > number2[i])
                {
                    return 1;
                }
                else if(number1[i] < number2[i])
                {
                    return -1;
                }
            }

            return 0;
        }
    }
}

int C_BigDec_isNegative(C_BigDec number)
{
    if(number[0] == '-')
        return 0;
    else
        return -1;
}

C_BigDec C_BigDec_assign(C_BigDec *dest, C_BigDec source)
{
    if(strlen(*dest) < strlen(source))
    {
        C_BigDec_delete(*dest);
        *dest=C_BigDec_new(-1, strlen(source));
    }

    return strcpy(*dest, source);
}

C_BigDec C_BigDec_abs(C_BigDec number)
{
    C_BigDec newNumber;

    if(!C_BigDec_isNegative(number))
    {
        newNumber=C_BigDec_new(0, strlen(number)-1);
        strcpy(newNumber, number+1);
    }
    else
    {
        newNumber=C_BigDec_new(-1, strlen(number));
        strcpy(newNumber, number);
    }

    return newNumber;
}

void C_BigDec_changeSign(C_BigDec *number1)
{
    if(!C_BigDec_isNegative(*number1))
    {
        *number1=C_BigDec_abs(*number1);
    }
    else
    {
        C_BigDec aux;
        size_t size;

        size=C_BigDec_len(*number1);

        aux=C_BigDec_new(0, size);
        memcpy(aux+1, number1, sizeof(char) * size);
    }
}
