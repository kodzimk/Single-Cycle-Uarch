#ifndef KODT_H_
#define KODT_H_

#include "sv.h"
#include "err.h"

#define SV_H_
#define ERR_H_

#define INST_LENGTH 255
#define INST_BITS 32
#define IMMIDIATE_BIT_COUNT 21

Err translate_file(const char* file_name);
void insert_text(char* array, const char* text, int start, int end);

char* decode_instruction(String_View inst);
char* decode_immidiate(String_View immidiate);
const char* decode_reg(String_View reg);

FILE* load_file(const char* file_name);
FILE* open_file(const char* file_name);

void insert_text(char* array, const char* text, int start, int end)
{
    for(int i = start;i < end;i++)
    {
        array[i] = text[i - start];
    } 
}

const char* decode_reg(String_View reg)
{
    if(sv_eq(reg,sv_from_cstr("$s0")))
    {
        return "00000";
    }

    return "";
}

char* decode_immidiate(String_View immidiate)
{
    char* decoded_immidiate = (char*)malloc(sizeof(char) * IMMIDIATE_BIT_COUNT);
    int value = atoi(immidiate.data);
    int index = 0;
    
    while(value > 0)
    {
        decoded_immidiate[index] = (value % 2) + '0';

        index++;
        value /= 2;
    }

    for(int i = index;i < 21;i++)
    {
        decoded_immidiate[i] = '0';
    }

    return decoded_immidiate;
}

char* decode_instruction(String_View inst)
{
    inst = sv_trim(inst);

    String_View opcode = sv_trim(sv_chop_by_delim(&inst,' ')); 
    char* decoded_inst = (char*)calloc(INST_BITS,sizeof(char));

    if(sv_eq(opcode,sv_from_cstr("addi")))
    {        
        String_View reg = sv_trim(sv_chop_by_delim(&inst,',')); 
        inst = sv_trim(inst);

        char* decoded_immidiate = decode_immidiate(inst);

        insert_text(decoded_inst,"000001",0,6);
        insert_text(decoded_inst, decode_reg(reg),6,11);
        insert_text(decoded_inst, decoded_immidiate, 11,32);
            
        free(decoded_immidiate);
    }

    return decoded_inst;
}

FILE* load_file(const char* file_name)
{
    FILE *file;
    char inst[INST_LENGTH];

    file = fopen(file_name, "r");

     if (file == NULL) {
        printf("Error: Could not open file %s.\n", file_name);
        exit(1); 
    }

    return file;
}

FILE* open_file(const char* file_name)
{
   FILE *file;
   file = fopen(file_name, "w");

   return file;
}

Err translate_file(const char* file_name)
{
    FILE* reading_file = load_file(file_name);
    FILE* writing_file = open_file("temp.dasm");
    char inst[INST_LENGTH];

    while(fgets(inst, INST_LENGTH, reading_file)) {
        char* decoded_inst = decode_instruction(sv_from_cstr(inst));
        fputs(decoded_inst,writing_file);
        free(decoded_inst);
    }
  
    fclose(reading_file);
    fclose(writing_file);

    return ERR_OK;
}

#endif // KODT IMPLEMENTATION