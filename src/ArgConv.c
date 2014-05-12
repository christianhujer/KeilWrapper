#include "ArgConv.h"
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
    this->array = malloc(sizeof(const char *) + 1);
}

void StringArray_add(struct StringArray *this, const char *string)
{
    this->array[this->length] = string;
    this->length++;
    this->array = realloc(this->array, this->length + 1);
}

struct ProgramListAndFlags {
    struct StringArray files;
    struct StringArray flags;
};

void ProgramListAndFlags_new(struct ProgramListAndFlags *this)
{
    StringArray_new(&this->files);
    StringArray_new(&this->flags);
}

void ProgramListAndFlags_addFile(struct ProgramListAndFlags *this, const char *file)
{
    StringArray_add(&this->files, file);
}

void ProgramListAndFlags_addToProgramCalls(struct ProgramListAndFlags *this, const char ****ptrToProgramCalls)
{
    for (const char **files = this->files.array; *files; files++) {
        *ptrToProgramCalls = realloc(*ptrToProgramCalls, ptrCount((const void **) *ptrToProgramCalls) + 1);
    }
}

struct ResultArguments {
    struct ProgramListAndFlags cc;
    struct ProgramListAndFlags as;
    struct ProgramListAndFlags ld;
};

void ResultArguments_new(struct ResultArguments *this)
{
    ProgramListAndFlags_new(&this->cc);
    ProgramListAndFlags_new(&this->as);
    ProgramListAndFlags_new(&this->ld);
}

void ResultArguments_parseInputArguments(struct ResultArguments *this, const char **argv)
{
    for (const char *arg; (arg = *argv); argv++) {
        if (endswith(arg, ".c")) {
            ProgramListAndFlags_addFile(&this->cc, arg);
        }
        if (endswith(arg, ".s")) {
            ProgramListAndFlags_addFile(&this->cc, arg);
        }
    }
}

const char ***ResultArguments_toProgramCalls(struct ResultArguments *this)
{
    const char ***programCalls = malloc(sizeof(const char **));
    ProgramListAndFlags_addToProgramCalls(&this->cc, &programCalls);
    ProgramListAndFlags_addToProgramCalls(&this->as, &programCalls);
    ProgramListAndFlags_addToProgramCalls(&this->ld, &programCalls);
    return programCalls;
}

const char ***ArgConv_convert(const char **argv)
{
    struct ResultArguments resultArguments;
    ResultArguments_new(&resultArguments);
    ResultArguments_parseInputArguments(&resultArguments, argv);
    return ResultArguments_toProgramCalls(&resultArguments);
}
