#include "ArgConv.h"
#include "FileSuffix.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

size_t ptrCount(const void **ptr)
{
    size_t result = 0;
    while (*ptr++)
        result++;
    return result;
}

bool endswith(const char *input, const char *suffix)
{
    const char *hit = strstr(input, suffix);
    return (hit != NULL) && (strlen(hit) == strlen(suffix));
}

struct StringArray {
    int length;
    const char **array;
};

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

struct ProgramListAndFlags {
    struct StringArray files;
    struct StringArray flags;
};

struct ResultArguments {
    struct StringArray files;
    struct StringArray ccFlags;
    struct StringArray asFlags;
    struct StringArray ldFlags;
};

void ResultArguments_new(struct ResultArguments *this)
{
    StringArray_new(&this->files);
    StringArray_new(&this->ccFlags);
    StringArray_new(&this->asFlags);
    StringArray_new(&this->ldFlags);
}

void ResultArguments_parseInputArguments(struct ResultArguments *this, const char **argv)
{
    for (const char *arg; (arg = *argv); argv++) {
        if (FileSuffix_isHandledFileSuffix(arg)) {
            StringArray_add(&this->files, arg);
        }
    }
}

const char ***ResultArguments_toProgramCalls(struct ResultArguments *this)
{
    const char ***programCalls = malloc(sizeof(const char **));
    for (const char **files = this->files.array; *files; files++) {
        programCalls = realloc(programCalls, sizeof(const char **) * (ptrCount((const void **) programCalls) + 1));
    }
    return programCalls;
}

const char ***ArgConv_convert(const char **argv)
{
    struct ResultArguments resultArguments;
    ResultArguments_new(&resultArguments);
    ResultArguments_parseInputArguments(&resultArguments, argv);
    return ResultArguments_toProgramCalls(&resultArguments);
}
