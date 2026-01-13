#ifndef KODC_H_
#define KODC_H_

#include"sv.h"
#include"err.h"

#include<stdint.h>

#define SV_H_
#define ERR_H_

#define INST_BITS 32

typedef struct 
{
    unsigned int aluOP : 1;
    unsigned int RegWrite : 1;
    char* RegDest;
}controlsignal_t;

typedef struct 
{
    controlsignal_t signal;
    Err err;
}ret_t;

Err execute(const char* binary_file_path);
FILE* load_file(const char* file_name);

FILE* load_file(const char* file_name)
{
    FILE *file;
    file = fopen(file_name, "r");

     if (file == NULL) {
        printf("Error: Could not open file %s.\n", file_name);
        exit(1); 
    }

    return file;
}

ret_t decode_inst(String_View inst)
{
    controlsignal_t signal = {.aluOP = 0, .RegDest = "", .RegWrite = 0};
    inst = sv_trim(inst);

    return (ret_t) {.err = ERR_OK, .signal = signal};
}


Err execute(const char* binary_file_path)
{
    uint64_t pc = 0;
    char inst[INST_BITS];
    FILE* file = load_file(binary_file_path);

    while(fgets(inst, INST_BITS, file)) {
        ret_t ret = decode_inst(sv_from_cstr(inst));
        if(ret.err == ERR_OK)
           return ERR_RUNTIME_ERROR;
    }

    return ERR_OK;
}

#endif // KODC_IMPLEMENTATION