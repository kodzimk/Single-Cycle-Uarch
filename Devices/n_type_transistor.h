#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
    int connected : 1;
    int source : 1;
    int drain : 1;
    void* next;
}ntrans_t;

ntrans_t* ntrans_init()
{
    ntrans_t* ntrans = (ntrans_t*)malloc(sizeof(ntrans_t));
    ntrans->connected = 0;
    ntrans->drain = 0;
    ntrans->next = NULL;
    ntrans->source = 0;
    return ntrans;
}

void ntrans_free(ntrans_t* ntrans)
{
    free(ntrans->next);
    free(ntrans);
}

void ntrans_connect(ntrans_t* t, int input)
{
    if(input == 1)
    {
        t->connected = 1;
    }
}