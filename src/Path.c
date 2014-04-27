#include "Path.h"
#include "Array.h"
#include <stddef.h>

static const char *getEnvName[] = {
    // Sequence MUST match enum Arch.
    "UNKNOWN",
    "KEIL_C51_HOME",
    "KEIL_C166_HOME",
    "KEIL_C251_HOME",
};

const char *Path_getEnvName(enum Arch arch)
{
    return Array_isIndexValid(getEnvName, arch) ? getEnvName[arch] : NULL;
}
