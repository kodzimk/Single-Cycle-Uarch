#include<stdio.h>

typedef struct 
{
    int Sum;
    int cOut;
}fullAdder_output;

int getBit(int num, int i)
{
    return ((num & (1 << i)) != 0);
}

int setBit(int num, int i,int setV)
{
    return num | (setV << i);
}

int multiplaxer(int A, int B, int F)
{
    if(getBit(F,2))
    {
        return A;
    }
    
    return B;
}

fullAdder_output fullAdder(int A,int B,int cIn)
{
    int sum = 0;
    for(int i = 0; i < 31;i++)
    {
        
        int aB = getBit(A,i);
        int bB = getBit(B,i);
        if(aB && bB)
        {
            cIn = 1;
        }
        
        sum = setBit(sum,i,(getBit(A,i) | getBit(B,i)));
    }

    fullAdder_output adder;
    adder.cOut = 0;
    adder.Sum = sum;

    return adder;
}

int alu(int A,int B, int F)
{
    int bComplementory = ~B;
    int secondvalue = multiplaxer(bComplementory,B,F);

    return secondvalue;
}