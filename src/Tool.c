#include "Tool.h"
#include <stddef.h>
#include <string.h>

static const struct DetectionEntry {
    const char *substring;
    enum Tool tool;
} detectionMap[] = {
    { "cc", TOOL_COMPILER },
    { "as", TOOL_ASSEMBLER },
    { "ar", TOOL_ARCHIVER },
    { "ld", TOOL_LINKER },
    { "objcopy", TOOL_OBJCOPY },
    { "C", TOOL_COMPILER },
    { "A", TOOL_ASSEMBLER },
    { "LIB", TOOL_ARCHIVER },
    { "L", TOOL_LINKER },
    { "OH", TOOL_OBJCOPY },
    { "c", TOOL_COMPILER },
    { "a", TOOL_ASSEMBLER },
    { "lib", TOOL_ARCHIVER },
    { "l", TOOL_LINKER },
    { "oh", TOOL_OBJCOPY },
    { NULL, 0 },
};

static const char *toString[] = {
    "Unknown",
    "Compiler",
    "Assembler",
    "Archiver",
    "Linker",
    "Object Copy",
};

enum Tool Tool_getFromCommandName(const char *commandName)
{
    for (const struct DetectionEntry *entry = detectionMap; entry->substring; entry++)
        if (strstr(commandName, entry->substring))
            return entry->tool;
    return TOOL_UNKNOWN;
}

const char *Tool_toString(enum Tool tool)
{
    if (tool < 0 || tool >= sizeof(toString) / sizeof(toString[0]))
        return "Invalid";
    else
        return toString[tool];
}
