int multiplaxer(int A, int B, int F)
{
    int temp = F;
    temp = ((temp >> 2) == 1);
    if(temp)
    {
        return A;
    }
    
    return B;
}

int alu(int A,int B, int F)
{
    int bComplementory = ~B;
    int secondvalue = multiplaxer(bComplementory,B,F);

    return secondvalue;
}