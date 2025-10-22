#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
    int connected : 1;
    int source : 1;
    int drain : 1;
    void* next;
}ptrans_t;

ptrans_t* ptrans_init()
{
    ptrans_t* ptrans = (ptrans_t*)malloc(sizeof(ptrans_t));
    ptrans->connected = 0;
    ptrans->drain = 0;
    ptrans->next = NULL;
    ptrans->source = 0;
    return ptrans;
}

void ptrans_free(ptrans_t* ptrans)
{
    free(ptrans->next);
    free(ptrans);
}

void ptrans_connect(ptrans_t* t, int input)
{
    if(input == 0)
    {
        t->connected = 1;
    }
}
