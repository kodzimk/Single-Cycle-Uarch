#include<stdint.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

#define INST_MEMORY_CAPACITY 256

typedef enum {
    R_TYPE,
    I_TYPE,
    J_TYPE
}INST_TYPE;


uint32_t pc;
uint32_t inst_memory[INST_MEMORY_CAPACITY];

void store_program(const char* file_name);
void inst_proccess_cycle();


void store_program(const char* file_name)
{
    FILE *program;
    program = fopen(file_name, "r");

    if(program == NULL)
    {
        printf("Can't open code\n");
    }

    uint8_t ir = 0;
    char inst[33];
    while(fgets(inst,33,program)){
        /*uint8_t curI = 0;
        //char* inst_op = (char*)calloc(32,sizeof(char));
  
        while(!isblank(inst[curI]))
        {
            inst_op[curI] = inst[curI];
            curI++;
        }

        if(strcmp(inst_op,"add") == 0 || strcmp(inst_op,"sub") == 0)
        {
            inst_memory[ir] = encode_inst(inst,inst_op,R_TYPE,curI + 1);
        }
        
        free(inst_op);*/
        
        inst_memory[0] = strtol(inst, NULL, 2);;
        pc = 0;
    }
}

typedef struct 
{
    uint8_t MemToReq : 1;
    uint8_t MemWrite : 1;
    uint8_t Branch : 1;
    uint8_t ALUControl: 3;
    uint8_t ALUSrc : 1;
    uint8_t RegDst : 1;
    uint8_t RegWrite: 1;
}control_unit;

typedef struct 
{
   uint32_t func;
   INST_TYPE type;
}inst_t;



uint32_t get_bit(uint32_t number, int bit_position) {
    return (number >> bit_position) & 1;
}

inst_t decode_inst_op(uint32_t inst)
{
    inst_t t;
    uint32_t temp = 0;
    for(int i = 25;i <= 32;i++)
    {
            temp += pow(2,i - 25) * get_bit(inst,i);
    }
    t.type = I_TYPE;

    if(temp == 0)
    {
     for(int i = 0;i <= 5 ;i++)
     {
            temp += pow(2,i) * get_bit(inst,i);
     }
     t.type = R_TYPE;
    }
    
    t.func = temp;
    return t;
}

control_unit decode_inst(uint32_t inst)
{
    control_unit control;
    inst_t opcode = decode_inst_op(inst);
    
    if(opcode.type == R_TYPE)
    {
        if(opcode.func == 32)
        {
         control.Branch = 0;
         control.ALUControl = 3;
         control.ALUSrc = 0;
         control.MemWrite = 0;
         control.RegWrite = 1;
         control.RegDst = 0;
         control.MemToReq = 0;
        }
    }

    return control;
}


void inst_proccess_cycle()
{
    while(inst_memory[pc] != 0)
    {
        uint32_t ir = inst_memory[pc];
        pc++;
        control_unit control = decode_inst(ir);
    }
}