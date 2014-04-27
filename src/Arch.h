#ifndef ARCHDETECTION_H
#define ARCHDETECTION_H

enum Arch {
    ARCH_UNKNOWN = 0,
    ARCH_C51 = 1,
    ARCH_C166 = 2,
    ARCH_C251 = 3,
};

extern enum Arch Arch_getFromCommandName(const char *commandName);

extern const char *Arch_toString(enum Arch arch);

#endif
