#include"src/kodc.h"

int main()
{
    Err err = execute("temp.dasm");
    if(err != ERR_OK)
    {
        printf("\n***ERROR DURING EXECUTING***, \n\n");
    }
    
    return 0;
}