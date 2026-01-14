#ifndef KODT_H_
#define KODT_H_

#include "sv.h"
#include "err.h"

#define SV_H_
#define ERR_H_

#define INST_LENGTH 255
#define INST_BITS 32
#define IMMIDIATE_BIT_COUNT 21
#define IMMIDIATE_MAX_VALUE 2097151

typedef struct 
{
    char* data;
    Err err;
}ret_t;

typedef struct
{
    Err error;
    int codeRow;
}err_t;

err_t translate_file(const char* reading_file_path,const char* writing_file_path);
void insert_text(char* array, const char* text, int start, int end);

Err decode_instruction(String_View inst, FILE* file);
ret_t decode_immidiate(String_View immidiate);
ret_t decode_reg(String_View reg);

FILE* load_file(const char* file_name);
FILE* open_file(const char* file_name);

void insert_text(char* array, const char* text, int start, int end)
{
    for(int i = start;i < end;i++)
    {
        array[i] = text[i - start];
    } 
}

ret_t decode_reg(String_View reg)
{
    if(sv_eq(reg,sv_from_cstr("$s0")))
    {
        return (ret_t) {.data = "00000",.err = ERR_OK};
    }

    return (ret_t) {.data = NULL,.err = ERR_UNKOWN_REGISTER};
}

ret_t decode_immidiate(String_View immidiate)
{
    char* decoded_immidiate = (char*)malloc(sizeof(char) * IMMIDIATE_BIT_COUNT);
    memset(decoded_immidiate,'0',sizeof(char) * IMMIDIATE_BIT_COUNT);

    int index = 0;
    int value = atoi(immidiate.data);

    if(value > IMMIDIATE_MAX_VALUE)
    {
       return (ret_t) {.data = NULL, .err = ERR_IMMIDIATE_OVERFLOW};
    }

    while(value > 0)
    {
        decoded_immidiate[index] = (value % 2) + '0';

        index++;
        value /= 2;
    }

    return (ret_t) {.data = decoded_immidiate, .err = ERR_OK};
}

Err decode_instruction(String_View inst, FILE* file)
{
    inst = sv_trim(inst);

    String_View opcode = sv_trim(sv_chop_by_delim(&inst,' ')); 
    char* decoded_inst = (char*)calloc(INST_BITS,sizeof(char));

    if(sv_eq(opcode,sv_from_cstr("addi")))
    {        
        String_View reg = sv_trim(sv_chop_by_delim(&inst,',')); 
        inst = sv_trim(inst);

        ret_t decoded_immidiate = decode_immidiate(inst);
        ret_t decoded_reg = decode_reg(reg);

        if(decoded_immidiate.err != ERR_OK)
           return decoded_immidiate.err;
        else if(decoded_reg.err != ERR_OK)
           return decoded_reg.err;

        insert_text(decoded_inst,"000001",0,6);
        insert_text(decoded_inst, decoded_reg.data,6,11);
        insert_text(decoded_inst, decoded_immidiate.data, 11,32);
            
        free(decoded_immidiate.data);
    }
    else
    {
        free(decoded_inst);
        return ERR_UNKOWN_OPCODE;
    }


    fputs(decoded_inst,file);
    fputc('\n',file);
    free(decoded_inst);

    return ERR_OK;
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

FILE* open_file(const char* file_name)
{
   FILE *file;
   file = fopen(file_name, "w");

   return file;
}

err_t translate_file(const char* reading_file_path,const char* writing_file_path)
{
    FILE* reading_file = load_file(reading_file_path);
    if(reading_file == NULL)
        return (err_t) {.codeRow = -1, .error = ERR_INCORRECT_FILE_PATH};

    FILE* writing_file = open_file(writing_file_path);
    if(writing_file == NULL)
        return (err_t) {.codeRow = -1, .error = ERR_INCORRECT_FILE_PATH};


    char inst[INST_LENGTH];
    int codeRow = 1;

    while(fgets(inst, INST_LENGTH, reading_file)) {
        Err err = decode_instruction(sv_from_cstr(inst),writing_file);
        if(err != ERR_OK)
        {
            fclose(writing_file);
            fclose(fopen("temp.dasm", "w"));
            fclose(reading_file);
            
            return (err_t) {.codeRow = codeRow, .error = err};
        }
        codeRow++;
    }
  
    fclose(reading_file);
    fclose(writing_file);
    return (err_t) {.codeRow = -1, .error = ERR_OK};
}

#endif // KODT IMPLEMENTATION