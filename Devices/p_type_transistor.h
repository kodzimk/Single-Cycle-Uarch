#include<stdio.h>

typedef struct 
{
    int connected : 1;
    float gate;
    int source : 1;
    int drain : 1;
}ptrans_t;

void ptrans_connect(ptrans_t* t, float input)
{
    if(input== 0.0f)
    {
        t->connected = 1;
    }
}

void ntrans_set(ptrans_t* t,int value)
{
    if(t->connected)
    {
        t->source = value;  
    }
}