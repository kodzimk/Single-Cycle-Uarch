#ifndef ERR_H_
#define ERR_H_

#include <assert.h>
#include <stdlib.h>

typedef enum {
    ERR_OK = 0,
    ERR_SYNTAX_ERROR,
    ERR_UNKOWN_REGISTER,
    ERR_IMMIDIATE_OVERFLOW,
} Err;

const char *err_as_cstr(Err err);

const char *err_as_cstr(Err err)
{
    switch (err) {
    case ERR_OK:
        return "ERR_OK";
    case ERR_SYNTAX_ERROR:
        return "ERR_SYNTAX_ERROR";
    case ERR_UNKOWN_REGISTER:
        return "ERR_UNKOWN_REGISTER";
    case ERR_IMMIDIATE_OVERFLOW:
        return "ERR_IMMIDIATE_OVERFLOW";

    default:
        assert(false && "err_as_cstr: Unreachable");
        exit(1);
    }
}

#endif // ERR IMPLEMENTATION