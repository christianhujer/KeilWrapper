#include "../src/Tool.h"
#include "ToolTest.h"
#include <stdio.h>

static const struct ExpectedDetectionEntry {
    const char *toolname;
    enum Tool expectedTool;
} expectedDetectionMap[] = {
    { "kwccX", TOOL_COMPILER },
    { "kwasX", TOOL_ASSEMBLER },
    { "kwarX", TOOL_ARCHIVER },
    { "kwldX", TOOL_LINKER },
    { "kwobjcopyX", TOOL_OBJCOPY },
    { "cc", TOOL_COMPILER },
    { "as", TOOL_ASSEMBLER },
    { "ar", TOOL_ARCHIVER },
    { "ld", TOOL_LINKER },
    { "objcopy", TOOL_OBJCOPY },
    { "kwcc", TOOL_COMPILER },
    { "kwas", TOOL_ASSEMBLER },
    { "kwar", TOOL_ARCHIVER },
    { "kwld", TOOL_LINKER },
    { "kwobjcopy", TOOL_OBJCOPY },
    { "ccX", TOOL_COMPILER },
    { "asX", TOOL_ASSEMBLER },
    { "arX", TOOL_ARCHIVER },
    { "ldX", TOOL_LINKER },
    { "objcopyX", TOOL_OBJCOPY },
    { "cc251", TOOL_COMPILER },
    { "as251", TOOL_ASSEMBLER },
    { "ar251", TOOL_ARCHIVER },
    { "ld251", TOOL_LINKER },
    { "objcopy251", TOOL_OBJCOPY },
    { "cc51", TOOL_COMPILER },
    { "as51", TOOL_ASSEMBLER },
    { "ar51", TOOL_ARCHIVER },
    { "ld51", TOOL_LINKER },
    { "objcopy51", TOOL_OBJCOPY },
    { "cc166", TOOL_COMPILER },
    { "as166", TOOL_ASSEMBLER },
    { "ar166", TOOL_ARCHIVER },
    { "ld166", TOOL_LINKER },
    { "objcopy166", TOOL_OBJCOPY },
    { "kwC251", TOOL_COMPILER },
    { "kwA251", TOOL_ASSEMBLER },
    { "kwLIB251", TOOL_ARCHIVER },
    { "kwL251", TOOL_LINKER },
    { "kwOH251", TOOL_OBJCOPY },
    { "kwC51", TOOL_COMPILER },
    { "kwA51", TOOL_ASSEMBLER },
    { "kwLIB51", TOOL_ARCHIVER },
    { "kwL51", TOOL_LINKER },
    { "kwOH51", TOOL_OBJCOPY },
    { "kwC166", TOOL_COMPILER },
    { "kwA166", TOOL_ASSEMBLER },
    { "kwLIB166", TOOL_ARCHIVER },
    { "kwL166", TOOL_LINKER },
    { "kwOH166", TOOL_OBJCOPY },
    { NULL, 0 },
};

static void assertToolNameImpl(const char *file, int line, enum Tool expectedTool, const char *toolname)
{
    enum Tool actualTool = Tool_getFromCommandName(toolname);
    if (actualTool != expectedTool) {
        fprintf(stderr, "%s:%d: error: Expected \"%s\" to be detected as %s but was %s\n", file, line, toolname, Tool_toString(expectedTool), Tool_toString(actualTool));
        fail();
    }
}

#define assertToolName(expectedTool, toolname) assertToolNameImpl(__FILE__, __LINE__, expectedTool, toolname)

A_Test void ToolTest_testGetFromCommandName(void)
{
    for (const struct ExpectedDetectionEntry *entry = expectedDetectionMap; entry->toolname; entry++)
        assertToolName(entry->expectedTool, entry->toolname);
}
