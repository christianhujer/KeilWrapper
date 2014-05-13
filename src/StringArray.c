#include "StringArray.h"
#include <stdlib.h>

void StringArray_new(struct StringArray *this)
{
    this->length = 0;
    this->array = malloc(sizeof(const char *));
}

void StringArray_add(struct StringArray *this, const char *string)
{
    this->array[this->length] = string;
    this->length++;
    this->array = realloc(this->array, sizeof(const char *) * (this->length + 1));
}
