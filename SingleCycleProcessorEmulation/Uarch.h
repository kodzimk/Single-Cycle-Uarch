#include<stdint.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

#define INST_MEMORY_CAPACITY 256

uint32_t from_text_to_binary(char inst[32])
{
    uint32_t binary = 0;
    for(int i = 0; i < 32;i++)
    {
        uint32_t temp = 0;
        temp = temp << (30 - i);
        temp = temp | (inst[i] - '0');
        binary = binary | temp;
    
    }

    printf("%d\n",binary);
    return binary;
}

typedef enum {
    R_TYPE,
    I_TYPE,
    J_TYPE
}INST_TYPE;


uint32_t* pc = NULL;
uint32_t inst_memory[INST_MEMORY_CAPACITY];

uint32_t encode_inst(char inst[32],char* opcode,INST_TYPE type,uint8_t startOperand);

void store_program(const char* file_name);
void inst_proccess_cycle();


uint32_t encode_inst(char inst[32],char* opcode,INST_TYPE type,uint8_t startOperand)
{
    uint32_t encoded_inst = 0;
    int r = 0;

    if(type == R_TYPE)
    {
        char trimS = ',';
        uint8_t curS = startOperand;
        while(inst[curS] != '\n' && inst[curS] != '\0' && r != 3)
        {
            char* operand = (char*)calloc(32,sizeof(char));
            while(inst[curS] != trimS)
            {
                operand[curS] = inst[curS];
                curS++;
            }
            curS++;

            if(r == 0)
            {
                
            }
            else if(r == 1)
            {
                encoded_inst += operand[1] - '0';
                encoded_inst = encoded_inst << 21;
            }

            r++;

        }
    }

    return encode_inst;
}

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
        printf("%s\n",inst);
        inst_memory[0] = 0b0 + atoi(inst);
        pc = &inst_memory;
    }

}


void inst_proccess_cycle()
{

}