#include "Arch.h"
#include <stddef.h>
#include <string.h>

static const struct DetectionEntry {
    const char *substring;
    enum Arch arch;
} detectionMap[] = {
    { "251", ARCH_C251 },
    { "51", ARCH_C51 },
    { "166", ARCH_C166 },
    { NULL, 0 },
};

static const char *toString[] = {
    // Sequence MUST match enum Arch.
    "Unknown",
    "C51",
    "C166",
    "C251",
};

enum Arch Arch_getFromCommandName(const char *commandName)
{
    for (const struct DetectionEntry *entry = detectionMap; entry->substring; entry++)
        if (strstr(commandName, entry->substring))
            return entry->arch;
    return ARCH_UNKNOWN;
}

const char *Arch_toString(enum Arch arch)
{
    if (arch < 0 || arch >= sizeof(toString) / sizeof(toString[0]))
        return "Invalid";
    else
        return toString[arch];
}
