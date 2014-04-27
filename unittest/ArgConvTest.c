#include "ArgConvTest.h"
#include "../src/ArgConv.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

extern void assertStringArrayEquals(const char *array1[], const char *array2[]);

static int strarrcmp(const char *array1[], const char *array2[])
{
    for (int index = 0; (array1[index] != NULL) || (array2[index] != NULL); index++)
        if (array1[index] == NULL || array2[index] == NULL || strcmp(array1[index], array2[index]))
            return index;
    return -1;
}

void assertStringArrayEqualsImpl(const char *file, int line, const char *expected[], const char *actual[])
{
    int pos = strarrcmp(expected, actual);
    if (-1 != pos) {
        fprintf(stderr, "%s:%d: error: Arrays differ in position %d, expected \"%s\" but got \"%s\".\n", file, line, pos, expected[pos], actual[pos]);
        // TODO:2014-04-28:cher:3:Enable fail.
        //fail("");
    }
}

#define assertStringArrayEquals(expected, actual) assertStringArrayEqualsImpl(__FILE__, __LINE__, expected, actual)

#define assertConversion(input, expected) assertStringArrayEquals((expected), ArgConv_convert(input));

A_Test void compileSimple(void)
{
    const char *input[] = { "foo.c", NULL };
    const char *expected[] = { "foo.c", "NOPRINT", "OBJECT(foo.o)", NULL };
    assertConversion(input, expected);
}

A_Test void compileAndAssemble(void)
{
    const char *input[] = { "-c", "foo.c", NULL };
    const char *expected[] = { "foo.c", "NOPRINT", "OBJECT(foo.o)", NULL };
    assertConversion(input, expected);
}

A_Test void compileButDoNotAssemble(void)
{
    const char *input[] = { "-S", "foo.c", NULL };
    const char *expected[] = { "foo.c", "SRC(foo.s)", NULL };
    assertConversion(input, expected);
}

A_Test void compileButDoNotAssembleToFile(void)
{
    const char *input[] = { "-S", "foo.c", "-o", "foo.X", NULL };
    const char *expected[] = { "foo.c", "SRC(foo.X)", NULL };
    assertConversion(input, expected);
}

A_Test void preprocessOnly(void)
{
    const char *input[] = { "-E", "foo.c", NULL };
    // TODO:2014-04-27:cher:3:Preprocessing should happen to stdout.
    const char *expected[] = { "foo.c", "PREPRINTONLY(foo.i)", NULL };
    assertConversion(input, expected);
}

A_Test void preprocessOnlyToFile(void)
{
    const char *input[] = { "-E", "foo.c", "-o", "foo2.i", NULL };
    const char *expected[] = { "foo.c", "PREPRINTONLY(foo2.i)", NULL };
    assertConversion(input, expected);
}

A_Test void emptyTest(void)
{
    const char *input[] = { "-I", "inc1", "-D", "macro1", "-I", "inc2", "-D", "macro2=foo", "-c", "-o", "foo.o", "foo.c", NULL };
    const char *expected[] = { "foo.c", "NOPRINT", "INCDIR(inc1,inc2)", "DEFINE(macro1,macro2=foo)", "OBJECT(foo.o)", NULL };
    assertConversion(input, expected);
}

// Options for gcc preprocessor
// See http://www.keil.com/support/man/docs/c251/c251_pp_predefmacroconst.htm to find out what must be set.
// -ffreestanding -undef -D__C251__ -D __DATE2__=mm/dd/yy
// SMALL -> -D __MODEL__=0
// LARGE -> -D __MODEL__=2
// TINY -> -D __MODEL__=3
// XTINY -> -D __MODEL__=4
// XSMALL -> -D __MODEL__=5
// FLOAT64 -> -D __FLOAT64__=1 else -D __FLOAT64__=0
