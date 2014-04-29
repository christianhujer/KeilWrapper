#include "ArgConvTest.h"
#include "../src/ArgConv.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

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

#define assertConversion(input, expected) assertConversionImpl(__FILE__, __LINE__, expected, ArgConv_convert(input))

static void assertConversionImpl(const char *file, int line, const char **expected[], const char **actual[])
{
    int index;
    for (index = 0; (expected[index] != NULL) && (actual[index] != NULL); index++)
        assertStringArrayEqualsImpl(file, line, expected[index], actual[index]);
    if (expected[index] != NULL)
        fprintf(stderr, "%s:%d: error: Expected more input at index %d starting with \"%s\".\n", file, line, index, expected[index][0]);
    if (actual[index] != NULL)
        fprintf(stderr, "%s:%d: error: Actual has additional output at index %d starting with \"%s\".\n", file, line, index, actual[index][0]);
}


// TODO:2014-04-29:cher:3: Use a three-dimensional expected array instead of a two-dimensional.
// The outermost dimension is for checking the driver.

A_Test void compileSimple(void)
{
    const char *input[] = { "cc251", "foo.c", NULL };
    const char *expected1[] = { "C251", "foo.c", "NOPRINT", "OBJECT(foo.o)", NULL };
    const char **expected[] = { expected1, NULL };
    assertConversion(input, expected);
}

A_Test void compileAndAssemble(void)
{
    const char *input[] = { "cc251", "-c", "foo.c", NULL };
    const char *expected1[] = { "C251", "foo.c", "NOPRINT", "OBJECT(foo.o)", NULL };
    const char **expected[] = { expected1, NULL };
    assertConversion(input, expected);
}

A_Test void compileButDoNotAssemble(void)
{
    const char *input[] = { "-S", "foo.c", NULL };
    const char *expected1[] = { "foo.c", "SRC(foo.s)", NULL };
    const char **expected[] = { expected1, NULL };
    assertConversion(input, expected);
}

A_Test void compileButDoNotAssembleToFile(void)
{
    const char *input[] = { "-S", "foo.c", "-o", "foo.X", NULL };
    const char *expected1[] = { "foo.c", "SRC(foo.X)", NULL };
    const char **expected[] = { expected1, NULL };
    assertConversion(input, expected);
}

A_Test void preprocessOnly(void)
{
    const char *input[] = { "-E", "foo.c", NULL };
    // TODO:2014-04-27:cher:3:Preprocessing should happen to stdout.
    const char *expected1[] = { "foo.c", "PREPRINTONLY(foo.i)", NULL };
    const char **expected[] = { expected1, NULL };
    assertConversion(input, expected);
}

A_Test void preprocessOnlyToFile(void)
{
    const char *input[] = { "-E", "foo.c", "-o", "foo2.i", NULL };
    const char *expected1[] = { "foo.c", "PREPRINTONLY(foo2.i)", NULL };
    const char **expected[] = { expected1, NULL };
    assertConversion(input, expected);
}

A_Test void emptyTest(void)
{
    const char *input[] = { "-I", "inc1", "-D", "macro1", "-I", "inc2", "-D", "macro2=foo", "-c", "-o", "foo.o", "foo.c", NULL };
    const char *expected1[] = { "foo.c", "NOPRINT", "INCDIR(inc1,inc2)", "DEFINE(macro1,macro2=foo)", "OBJECT(foo.o)", NULL };
    const char **expected[] = { expected1, NULL };
    assertConversion(input, expected);
}

A_Test void multipleFiles(void)
{
    const char *input[] = { "cc251", "-c", "bar.c", "foo.c", NULL };
    const char *expected1[] = { "C251", "foo.c", "OBJECT(foo.o)", "NULL" };
    const char *expected2[] = { "C251", "bar.c", "OBJECT(bar.o)", "NULL" };
    const char **expected[] = { expected1, expected2, NULL };
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
