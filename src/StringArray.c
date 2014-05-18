#include "StringArray.h"
#include <stdlib.h>

const char **StringArray_add(const char **array, const char *string)
{
    size_t length = StringArray_getLength(array);
    array = realloc(array, sizeof(const char *) * (length + 2)); // existing elements + new element + NULL
    array[length] = string;
    array[length + 1] = NULL;
    return array;
}

size_t StringArray_getLength(const char **array)
{
    int length = 0;
    if (array) while (*array++)
        length++;
    return length;
}
