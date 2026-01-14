#include"src/kodc.h"

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
    fprintf(stream, "Usage: %s <input.dasm>\n", program);
}

int main(int argc, char **argv)
{
    const char *shifted = shift(&argc, &argv);
    if (argc == 0) {
        usage(stderr, shifted);
        fprintf(stderr, "ERROR: expected input\n");
        exit(1);
    }
    const char *input_file_path = shift(&argc, &argv);
    Err err = execute(input_file_path);

    if(err != ERR_OK)
    {
       printf("\n***ERROR DURING EXECUTING*** CAUSE: %s \n\n", err_as_cstr(err));
    }

    return 0;
}