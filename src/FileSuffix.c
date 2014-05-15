#include "FileSuffix.h"

extern bool endswith(const char *input, const char *suffix);

bool FileSuffix_isCFileSuffix(const char *arg)
{
    return false
        || endswith(arg, ".c")
        || endswith(arg, ".i")
        ;
}

bool FileSuffix_isAsmFileSuffix(const char *arg)
{
    return false
        || endswith(arg, ".s")
        || endswith(arg, ".a51")
        || endswith(arg, ".A51")
        || endswith(arg, ".asm")
        || endswith(arg, ".ASM")
        ;
}

bool FileSuffix_isLinkerFileSuffix(const char *arg)
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

bool FileSuffix_isHandledFileSuffix(const char *arg)
{
    return false
        || FileSuffix_isCFileSuffix(arg)
        || FileSuffix_isAsmFileSuffix(arg)
        || FileSuffix_isLinkerFileSuffix(arg)
        ;
}
