#include "FileSuffixTest.h"
#include "../src/FileSuffix.h"

A_Test void FileSuffixTest_hasCFileSuffix(void)
{
    assertTrue("", FileSuffix_hasCFileSuffix("foo.c"));
    assertTrue("", FileSuffix_hasCFileSuffix("foo.i"));
    assertFalse("", FileSuffix_hasCFileSuffix("foo.s"));
    assertFalse("", FileSuffix_hasCFileSuffix("foo.a51"));
    assertFalse("", FileSuffix_hasCFileSuffix("foo.A51"));
    assertFalse("", FileSuffix_hasCFileSuffix("foo.asm"));
    assertFalse("", FileSuffix_hasCFileSuffix("foo.ASM"));
    assertFalse("", FileSuffix_hasCFileSuffix("foo.o"));
    assertFalse("", FileSuffix_hasCFileSuffix("foo.a"));
    assertFalse("", FileSuffix_hasCFileSuffix("foo.obj"));
    assertFalse("", FileSuffix_hasCFileSuffix("foo.OBJ"));
    assertFalse("", FileSuffix_hasCFileSuffix("foo.lib"));
    assertFalse("", FileSuffix_hasCFileSuffix("foo.LIB"));
}

A_Test void FileSuffixTest_hasAsmFileSuffix(void)
{
    assertFalse("", FileSuffix_hasAsmFileSuffix("foo.c"));
    assertFalse("", FileSuffix_hasAsmFileSuffix("foo.i"));
    assertTrue("", FileSuffix_hasAsmFileSuffix("foo.s"));
    assertTrue("", FileSuffix_hasAsmFileSuffix("foo.a51"));
    assertTrue("", FileSuffix_hasAsmFileSuffix("foo.A51"));
    assertTrue("", FileSuffix_hasAsmFileSuffix("foo.asm"));
    assertTrue("", FileSuffix_hasAsmFileSuffix("foo.ASM"));
    assertFalse("", FileSuffix_hasAsmFileSuffix("foo.o"));
    assertFalse("", FileSuffix_hasAsmFileSuffix("foo.a"));
    assertFalse("", FileSuffix_hasAsmFileSuffix("foo.obj"));
    assertFalse("", FileSuffix_hasAsmFileSuffix("foo.OBJ"));
    assertFalse("", FileSuffix_hasAsmFileSuffix("foo.lib"));
    assertFalse("", FileSuffix_hasAsmFileSuffix("foo.LIB"));
}

A_Test void FileSuffixTest_hasLinkerFileSuffix(void)
{
    assertFalse("", FileSuffix_hasLinkerFileSuffix("foo.c"));
    assertFalse("", FileSuffix_hasLinkerFileSuffix("foo.i"));
    assertFalse("", FileSuffix_hasLinkerFileSuffix("foo.s"));
    assertFalse("", FileSuffix_hasLinkerFileSuffix("foo.a51"));
    assertFalse("", FileSuffix_hasLinkerFileSuffix("foo.A51"));
    assertFalse("", FileSuffix_hasLinkerFileSuffix("foo.asm"));
    assertFalse("", FileSuffix_hasLinkerFileSuffix("foo.ASM"));
    assertTrue("", FileSuffix_hasLinkerFileSuffix("foo.o"));
    assertTrue("", FileSuffix_hasLinkerFileSuffix("foo.a"));
    assertTrue("", FileSuffix_hasLinkerFileSuffix("foo.obj"));
    assertTrue("", FileSuffix_hasLinkerFileSuffix("foo.OBJ"));
    assertTrue("", FileSuffix_hasLinkerFileSuffix("foo.lib"));
    assertTrue("", FileSuffix_hasLinkerFileSuffix("foo.LIB"));
}
