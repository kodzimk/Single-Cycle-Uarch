#ifndef KODT_H_
#define KODT_H_

#include"sv.h"

#define INST_LENGTH 255
#define INST_BITS 32

void translate_file(const char* file_name);
String_View decode_instruction(String_View inst);
FILE* load_file(const char* file_name);


String_View decode_instruction(String_View inst)
{
    inst = sv_trim(inst);

    String_View opcode = sv_chop_by_delim(&inst,' '); 
    char decoded_inst[INST_BITS];

    if(sv_eq(opcode,sv_from_cstr("addi")))
    {
        
    }
    else if(sv_eq(opcode,sv_from_cstr("subi")))
    {
        
    }

    String_View result = sv_from_cstr(decoded_inst);

    return result;
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

void translate_file(const char* file_name)
{
    FILE* reading_file = load_file(file_name);
    FILE* writing_file = open_file("temp.dasm");
    char inst[INST_LENGTH];

    while(fgets(inst, INST_LENGTH, reading_file)) {
        String_View decoded_inst = decode_instruction(sv_from_cstr(inst));
        fprintf(writing_file, decoded_inst.data);
    }
  
    fclose(reading_file);
    fclose(writing_file);
}

#endif