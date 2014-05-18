#include "ArgConv.h"
#include "FileSuffix.h"
#include "StringArray.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

size_t ptrCount(const void **ptr)
{
    size_t result = 0;
    if (ptr) while (*ptr++)
        result++;
    return result;
}

bool endswith(const char *input, const char *suffix)
{
    const char *hit = strstr(input, suffix);
    return (hit != NULL) && (strlen(hit) == strlen(suffix));
}

struct ResultArguments {
    const char **files;
    const char **ccFlags;
    const char **asFlags;
    const char **ldFlags;
};

void ResultArguments_new(struct ResultArguments *this)
{
    this->files = NULL;
    this->ccFlags = NULL;
    this->asFlags = NULL;
    this->ldFlags = NULL;
}

void ResultArguments_parseInputArguments(struct ResultArguments *this, const char **argv)
{
    for (const char *arg; (arg = *argv); argv++) {
        if (FileSuffix_hasHandledFileSuffix(arg)) {
            this->files = StringArray_add(this->files, arg);
        }
    }
}

const char **ResultArguments_getFlagsFromSuffix(const struct ResultArguments *this, const char *file)
{
    if (FileSuffix_hasCFileSuffix(file))
        return this->ccFlags;
    if (FileSuffix_hasAsmFileSuffix(file))
        return this->asFlags;
    if (FileSuffix_hasLinkerFileSuffix(file))
        return this->ldFlags;
    abort();
}

const char **ResultArguments_toProgramCall(const struct ResultArguments *this, const char *file)
{
    const char **flags = ResultArguments_getFlagsFromSuffix(this, file);
    const int numberOfFlags = StringArray_getLength(flags);
    const int length = 2 + numberOfFlags + 1; // PROGRAM_NAME FILE FLAGS NULL
    const char **programCall = malloc(sizeof(const char *) * length);

    programCall[0] = "FOO";
    programCall[1] = file;
    memcpy(&programCall[2], flags, StringArray_getLength(flags) * sizeof(const char *));
    return programCall;
}

const char ***ResultArguments_toProgramCalls(struct ResultArguments *this)
{
    const char ***programCalls = malloc(sizeof(const char **));
    int callIndex = 0;
    for (const char **files = this->files; *files; files++) {
        programCalls = realloc(programCalls, sizeof(const char **) * (ptrCount((const void **) programCalls) + 1));
        programCalls[callIndex++] = ResultArguments_toProgramCall(this, *files);
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
