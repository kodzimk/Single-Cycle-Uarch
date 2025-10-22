#include"Devices/n_type_transistor.h"
#include"Devices/p_type_transistor.h"

int not(int input)
{
    ntrans_t* ntrans = ntrans_init();
    ptrans_t* ptrans = ptrans_init();

    ntrans_connect(ntrans,input);
    ptrans_connect(ptrans,input);

    if(ntrans->connected)
    {
        ntrans_free(ntrans);
        ptrans_free(ptrans);
        return 0;
    }

    ntrans_free(ntrans);
    ptrans_free(ptrans);
    return 1;
}



