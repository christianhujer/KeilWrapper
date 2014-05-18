#include "FileSuffix.h"

extern bool endswith(const char *input, const char *suffix);

bool FileSuffix_hasCFileSuffix(const char *arg)
{
    return false
        || endswith(arg, ".c")
        || endswith(arg, ".i")
        ;
}

bool FileSuffix_hasAsmFileSuffix(const char *arg)
{
    return false
        || endswith(arg, ".s")
        || endswith(arg, ".a51")
        || endswith(arg, ".A51")
        || endswith(arg, ".asm")
        || endswith(arg, ".ASM")
        ;
}

bool FileSuffix_hasLinkerFileSuffix(const char *arg)
{
    return false
        || endswith(arg, ".o")
        || endswith(arg, ".a")
        || endswith(arg, ".obj")
        || endswith(arg, ".OBJ")
        || endswith(arg, ".lib")
        || endswith(arg, ".LIB")
        ;
}

bool FileSuffix_hasHandledFileSuffix(const char *arg)
{
    return false
        || FileSuffix_hasCFileSuffix(arg)
        || FileSuffix_hasAsmFileSuffix(arg)
        || FileSuffix_hasLinkerFileSuffix(arg)
        ;
}
