#include"SingleCycleProcessorEmulation/uArch.h"

int main()
{
    store_program("SingleCycleProcessorEmulation/example/add.asm");
    inst_proccess_cycle();
    return 0;
}