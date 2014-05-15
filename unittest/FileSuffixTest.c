#include "FileSuffixTest.h"
#include "../src/FileSuffix.h"

A_Test void FileSuffixTest_isCFileSuffix(void)
{
    assertTrue("", FileSuffix_isCFileSuffix("foo.c"));
    assertTrue("", FileSuffix_isCFileSuffix("foo.i"));
    assertFalse("", FileSuffix_isCFileSuffix("foo.s"));
    assertFalse("", FileSuffix_isCFileSuffix("foo.a51"));
    assertFalse("", FileSuffix_isCFileSuffix("foo.A51"));
    assertFalse("", FileSuffix_isCFileSuffix("foo.asm"));
    assertFalse("", FileSuffix_isCFileSuffix("foo.ASM"));
    assertFalse("", FileSuffix_isCFileSuffix("foo.o"));
    assertFalse("", FileSuffix_isCFileSuffix("foo.a"));
    assertFalse("", FileSuffix_isCFileSuffix("foo.obj"));
    assertFalse("", FileSuffix_isCFileSuffix("foo.OBJ"));
    assertFalse("", FileSuffix_isCFileSuffix("foo.lib"));
    assertFalse("", FileSuffix_isCFileSuffix("foo.LIB"));
}

A_Test void FileSuffixTest_isAsmFileSuffix(void)
{
    assertFalse("", FileSuffix_isAsmFileSuffix("foo.c"));
    assertFalse("", FileSuffix_isAsmFileSuffix("foo.i"));
    assertTrue("", FileSuffix_isAsmFileSuffix("foo.s"));
    assertTrue("", FileSuffix_isAsmFileSuffix("foo.a51"));
    assertTrue("", FileSuffix_isAsmFileSuffix("foo.A51"));
    assertTrue("", FileSuffix_isAsmFileSuffix("foo.asm"));
    assertTrue("", FileSuffix_isAsmFileSuffix("foo.ASM"));
    assertFalse("", FileSuffix_isAsmFileSuffix("foo.o"));
    assertFalse("", FileSuffix_isAsmFileSuffix("foo.a"));
    assertFalse("", FileSuffix_isAsmFileSuffix("foo.obj"));
    assertFalse("", FileSuffix_isAsmFileSuffix("foo.OBJ"));
    assertFalse("", FileSuffix_isAsmFileSuffix("foo.lib"));
    assertFalse("", FileSuffix_isAsmFileSuffix("foo.LIB"));
}

A_Test void FileSuffixTest_isLinkerFileSuffix(void)
{
    assertFalse("", FileSuffix_isLinkerFileSuffix("foo.c"));
    assertFalse("", FileSuffix_isLinkerFileSuffix("foo.i"));
    assertFalse("", FileSuffix_isLinkerFileSuffix("foo.s"));
    assertFalse("", FileSuffix_isLinkerFileSuffix("foo.a51"));
    assertFalse("", FileSuffix_isLinkerFileSuffix("foo.A51"));
    assertFalse("", FileSuffix_isLinkerFileSuffix("foo.asm"));
    assertFalse("", FileSuffix_isLinkerFileSuffix("foo.ASM"));
    assertTrue("", FileSuffix_isLinkerFileSuffix("foo.o"));
    assertTrue("", FileSuffix_isLinkerFileSuffix("foo.a"));
    assertTrue("", FileSuffix_isLinkerFileSuffix("foo.obj"));
    assertTrue("", FileSuffix_isLinkerFileSuffix("foo.OBJ"));
    assertTrue("", FileSuffix_isLinkerFileSuffix("foo.lib"));
    assertTrue("", FileSuffix_isLinkerFileSuffix("foo.LIB"));
}
