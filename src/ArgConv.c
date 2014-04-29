#include "ArgConv.h"
#include <stddef.h>
#include <stdlib.h>

const char ***ArgConv_convert(const char **input)
{
    const char ***data = malloc(sizeof(void *) * 2);
    data[0] = input;
    data[1] = NULL;
    return data;
}
