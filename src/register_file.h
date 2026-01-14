#ifndef REGFILE_H_
#define REGFILE_H_

#include<stdint.h>

#include"sv.h"
#include<math.h>

#define SV_H_

#define REGISTER_FILE_SIZE 32

typedef struct
{
   int32_t register_file[32];
}file_t;

int8_t dest_to_addr(String_View view)
{
    int8_t addr = 0;
    for(int i = (int)(view.count - 1);i >= 0 ;i--)
    {
        if(view.data[i] == '1')
            addr += pow(2, 4 - i);
    }

    return addr;
}

int32_t read_register(file_t* file, String_View dest)
{
    int8_t addr = dest_to_addr(dest);
    return file->register_file[addr];
}

void write_register(file_t* file, String_View dest, int32_t value)
{
    int8_t addr = dest_to_addr(dest);
    file->register_file[addr] = value;
}

#endif // REGISTER FILE IMPLEMENTATION