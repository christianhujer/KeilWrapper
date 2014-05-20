#include "PathTest.h"
#include "../src/Path.h"
#include <stdio.h>
#include <string.h>

static const struct ExpectedDetectionEntry {
    enum Arch arch;
    const char *expectedName;
} expectedDetectionMap[] = {
    { ARCH_C251, "KEIL_C251_HOME" },
    { ARCH_C166, "KEIL_C166_HOME" },
    { ARCH_C51, "KEIL_C51_HOME" },
    { 0, NULL },
};

static void assertNameImpl(const char *file, int line, const char *expectedName, enum Arch arch)
{
    const char *actualName = Path_getEnvName(arch);
    if (strcmp(actualName, expectedName)) {
        fprintf(stderr, "%s:%d: error: Expected %s to have environment name %s but was %s.\n", file, line, Arch_toString(arch), expectedName, actualName);
        fail("");
    }
}

#define assertName(expectedName, arch) assertNameImpl(__FILE__, __LINE__, expectedName, arch)

A_Test void PathTest_getEnvName(void)
{
    for (const struct ExpectedDetectionEntry *entry = expectedDetectionMap; entry->arch; entry++)
        assertName(entry->expectedName, entry->arch);
}
