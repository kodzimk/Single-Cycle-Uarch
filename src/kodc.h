#ifndef KODC_H_
#define KODC_H_

#include"sv.h"
#include"err.h"

#include<stdint.h>

#define SV_H_
#define ERR_H_

#define INST_BITS 33

typedef enum
{
    UNKOWN = 0,
    I_TYPE,
} INST_TYPE;

typedef struct 
{
    int value : 21;
}int21_t;

typedef struct 
{
    unsigned int aluOP : 3;
    unsigned int RegWrite : 1;
    INST_TYPE inst_type;
}controlsignal_t;

typedef struct 
{
    controlsignal_t signal;
    Err err;
}ret_t;

typedef struct 
{
    String_View RegDest1;
    String_View RegDest2;
    int21_t immidiate;
}data_t;

ret_t decode_inst(String_View* inst);
Err decode_operands(String_View* inst, INST_TYPE inst_type, data_t* data);
Err execute(const char* binary_file_path);
FILE* load_file(const char* file_name);

int21_t sv_to_int21(String_View view)
{
    int21_t value = {.value = 0};
    for(int i = 0 ;i < view.count;i++)
    {
    }

    return value;
}

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

ret_t decode_inst(String_View* inst)
{
    controlsignal_t signal = {.aluOP = 0, .RegWrite = 0, .inst_type = UNKOWN};
    *inst = sv_trim(*inst);

    String_View opcode = sv_chop_by_index(inst, 0, 6);
    if(sv_eq(opcode,sv_from_cstr("000001")))
    {
        signal.aluOP = 1;
        signal.RegWrite = 1;
        signal.inst_type = I_TYPE;
        printf("addi\n");
    }

    return (ret_t) {.err = ERR_OK, .signal = signal};
}

Err decode_operands(String_View* inst, INST_TYPE inst_type, data_t* data)
{
    switch (inst_type)
    {
    case UNKOWN:
        return ERR_RUNTIME_ERROR;
    case I_TYPE:
    {
        String_View reg_dest = sv_chop_by_index(inst,6,11);
        String_View immidiate = sv_chop_by_index(inst,11,32);
        data->RegDest1 = reg_dest;
        data->immidiate = sv_to_int21(immidiate);
    }
    
    default:
        return ERR_RUNTIME_ERROR;
    }

    return ERR_OK;
}

Err execute(const char* binary_file_path)
{
    data_t data = { .immidiate = 0, .RegDest1 = sv_from_cstr(""), .RegDest2 = sv_from_cstr("") };
    FILE* file = load_file(binary_file_path);
    char inst[INST_BITS];
    uint64_t pc = 1;

    while(fgets(inst, INST_BITS, file)) {
        if(isspace(inst[0]))
            continue;

        String_View view = sv_from_cstr(inst);
        ret_t ret = decode_inst(&view);
        if(ret.err != ERR_OK)
           return ERR_RUNTIME_ERROR;

        Err err = decode_operands(&view, ret.signal.inst_type, &data);
        if(err != ERR_OK)
           return ERR_RUNTIME_ERROR;

        pc++;
    }

    return ERR_OK;
}

#endif // KODC_IMPLEMENTATION