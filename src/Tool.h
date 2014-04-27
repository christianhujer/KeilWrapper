#ifndef TOOLDETECTION_H
#define TOOLDETECTION_H

enum Tool {
    TOOL_UNKNOWN = 0,
    TOOL_COMPILER = 1,
    TOOL_ASSEMBLER = 2,
    TOOL_ARCHIVER = 3,
    TOOL_LINKER = 4,
    TOOL_OBJCOPY = 5,
};

extern enum Tool Tool_getFromCommandName(const char *commandName);

extern const char *Tool_toString(enum Tool tool);

#endif
