#include"src/kodt.h"

static char *shift(int *argc, char ***argv)
{
    assert(*argc > 0);
    char *result = **argv;
    *argv += 1;
    *argc -= 1;
    return result;
}

static void usage(FILE *stream, const char *program)
{
    fprintf(stream, "Usage: %s <input.kasm> <output.dasm>\n", program);
}

int main(int argc, char **argv)
{
    const char *translator = shift(&argc, &argv);

    if (argc == 0) {
        usage(stderr, translator);
        fprintf(stderr, "ERROR: expected input\n");
        exit(1);
    }
    const char *input_file_path = shift(&argc, &argv);

    if (argc == 0) {
        usage(stderr, translator);
        fprintf(stderr, "ERROR: expected output\n");
        exit(1);
    }
    
    const char *output_file_path = shift(&argc, &argv);
    err_t err = translate_file(input_file_path,output_file_path);
    
    if(err.error == ERR_OK)
    {
        printf("\n***SUCCEFULLY TRANSLATED***, CHECK FILE: add.kasm for binary code!!!\n\n");
    }
    else{
        printf("\n***ERROR***, CAUSE: %s , at row: %d;\n\n", err_as_cstr(err.error),err.codeRow);
    }

    
    return 0;
}