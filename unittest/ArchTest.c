#include "../src/Arch.h"
#include "ArchTest.h"
#include <stdio.h>

static const struct ExpectedDetectionEntry {
    const char *toolname;
    enum Arch expectedArch;
} expectedDetectionMap[] = {
    { "cc251", ARCH_C251 },
    { "as251", ARCH_C251 },
    { "ar251", ARCH_C251 },
    { "ld251", ARCH_C251 },
    { "objcopy251", ARCH_C251 },
    { "cc51", ARCH_C51 },
    { "as51", ARCH_C51 },
    { "ar51", ARCH_C51 },
    { "ld51", ARCH_C51 },
    { "objcopy51", ARCH_C51 },
    { "cc166", ARCH_C166 },
    { "as166", ARCH_C166 },
    { "ar166", ARCH_C166 },
    { "ld166", ARCH_C166 },
    { "objcopy166", ARCH_C166 },
    { "kwC251", ARCH_C251 },
    { "kwA251", ARCH_C251 },
    { "kwLIB251", ARCH_C251 },
    { "kwL251", ARCH_C251 },
    { "kwOH251", ARCH_C251 },
    { "kwC51", ARCH_C51 },
    { "kwA51", ARCH_C51 },
    { "kwLIB51", ARCH_C51 },
    { "kwL51", ARCH_C51 },
    { "kwOH51", ARCH_C51 },
    { "kwC166", ARCH_C166 },
    { "kwA166", ARCH_C166 },
    { "kwLIB166", ARCH_C166 },
    { "kwL166", ARCH_C166 },
    { "kwOH166", ARCH_C166 },
    { NULL, 0 },
};

static void assertArchImpl(const char *file, int line, enum Arch expectedArch, const char *toolname)
{
    enum Arch actualArch = Arch_getFromCommandName(toolname);
    if (actualArch != expectedArch) {
        fprintf(stderr, "%s:%d: error: Expected \"%s\" to be detected as %s but was %s\n", file, line, toolname, Arch_toString(expectedArch), Arch_toString(actualArch));
        fail("");
    }
}

#define assertArch(expectedArch, toolname) assertArchImpl(__FILE__, __LINE__, expectedArch, toolname)

A_Test void ArchTest_testGetFromCommandName(void)
{
    for (const struct ExpectedDetectionEntry *entry = expectedDetectionMap; entry->toolname; entry++)
        assertArch(entry->expectedArch, entry->toolname);
}
