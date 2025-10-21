#include<stdio.h>

typedef struct 
{
    int connected : 1;
    float gate;
    int source : 1;
    int drain : 1;
}ntrans_t;

void ntrans_connect(ntrans_t* t, float input)
{
    if(input >= 0.3f && input <= 3.0f)
    {
        t->connected = 1;
    }
}

void ntrans_set(ntrans_t* t,int value)
{
    if(t->connected)
    {
        t->drain = value;  
    }
}