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
        fail("");
    }
}

#define assertStringArrayEquals(expected, actual) assertStringArrayEqualsImpl(__FILE__, __LINE__, expected, actual)

#define assertConversion(input, expected) assertConversionImpl(__FILE__, __LINE__, expected, ArgConv_convert(input))

static void assertConversionImpl(const char *file, int line, const char **expected[], const char **actual[])
{
    int index;
    for (index = 0; (expected[index] != NULL) && (actual[index] != NULL); index++)
        assertStringArrayEqualsImpl(file, line, expected[index], actual[index]);
    if (expected[index] != NULL) {
        fprintf(stderr, "%s:%d: error: Expected more input at index %d starting with \"%s\".\n", file, line, index, expected[index][0]);
        fail("");
    }
    if (actual[index] != NULL) {
        fprintf(stderr, "%s:%d: error: Actual has additional output at index %d starting with \"%s\".\n", file, line, index, actual[index][0]);
        fail("");
    }
}


// TODO:2014-04-29:cher:3: Use a three-dimensional expected array instead of a two-dimensional.
// The outermost dimension is for checking the driver.

A_Test void compileSimple(void)
{
    const char *input[] = { "cc251", "foo.c", NULL };
    const char *expected1[] = { "C251", "foo.c", "NOPRINT", "OBJECT(foo.o)", NULL };
    const char *expected2[] = { "L251", "foo.o", NULL };
    const char **expected[] = { expected1, expected2, NULL };
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
    const char *input[] = { "cc251", "-S", "foo.c", NULL };
    const char *expected1[] = { "C251", "foo.c", "SRC(foo.s)", NULL };
    const char **expected[] = { expected1, NULL };
    assertConversion(input, expected);
}

A_Test void compileButDoNotAssembleToFile(void)
{
    const char *input[] = { "cc251", "-S", "foo.c", "-o", "foo.X", NULL };
    const char *expected1[] = { "C251", "foo.c", "SRC(foo.X)", NULL };
    const char **expected[] = { expected1, NULL };
    assertConversion(input, expected);
}

A_Test void preprocessOnly(void)
{
    const char *input[] = { "cc251", "-E", "foo.c", NULL };
    // TODO:2014-04-27:cher:3:Preprocessing should happen to stdout.
    const char *expected1[] = { "C251", "foo.c", "PREPRINTONLY(foo.i)", NULL };
    const char **expected[] = { expected1, NULL };
    assertConversion(input, expected);
}

A_Test void preprocessOnlyToFile(void)
{
    const char *input[] = { "cc251", "-E", "foo.c", "-o", "foo2.i", NULL };
    const char *expected1[] = { "C251", "foo.c", "PREPRINTONLY(foo2.i)", NULL };
    const char **expected[] = { expected1, NULL };
    assertConversion(input, expected);
}

A_Test void emptyTest(void)
{
    const char *input[] = { "cc251", "-I", "inc1", "-D", "macro1", "-I", "inc2", "-D", "macro2=foo", "-c", "-o", "foo.o", "foo.c", NULL };
    const char *expected1[] = { "C251", "foo.c", "NOPRINT", "INCDIR(inc1,inc2)", "DEFINE(macro1,macro2=foo)", "OBJECT(foo.o)", NULL };
    const char **expected[] = { expected1, NULL };
    assertConversion(input, expected);
}

A_Test void compileMultipleFiles(void)
{
    const char *input[] = { "cc251", "-c", "foo.c", "bar.c", NULL };
    const char *expected1[] = { "C251", "foo.c", "OBJECT(foo.o)", NULL };
    const char *expected2[] = { "C251", "bar.c", "OBJECT(bar.o)", NULL };
    const char **expected[] = { expected1, expected2, NULL };
    assertConversion(input, expected);
}

A_Test void compileAndLinkMultipleFilesWithPathsAndMacros(void)
{
    const char *input[] = { "cc251", "-I", "inc1", "-Iinc2", "-D", "FOO", "-DBAR=10", "foo.c", "bar.c", NULL };
    const char *expected1[] = { "C251", "foo.c", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(foo.o)", NULL };
    const char *expected2[] = { "C251", "bar.c", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(bar.o)", NULL };
    const char *expected3[] = { "L251", "foo.o", "bar.o", NULL };
    const char **expected[] = { expected1, expected2, expected3, NULL };
    assertConversion(input, expected);
}

A_Test void compileOrAssembleAndLinkMultipleFilesWithPathsAndMacros(void)
{
    // TODO:2014-05-03:cher:3:Define a behavior in case extracting a file from an archive would overwrite an existing file.
    const char *input[] = { "cc251", "-I", "inc1", "-Iinc2", "-D", "FOO", "-DBAR=10", "foo.c", "bar.s", "baz.o", "qux.i", "quux.lib", "corge.a", "grault.c", "NULL" };
    const char *expected1[] = { "C251", "foo.c", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(foo.o)", NULL };
    const char *expected2[] = { "A251", "bar.s", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(bar.o)", NULL };
    const char *expected3[] = { "C251", "qux.i", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(qux.o)", NULL };
    const char *expected4[] = { "C251", "grault.c", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(grault.o)", NULL };
    const char *expected5[] = { "ar", "x", "corge.a", "corge.lib", NULL };
    const char *expected6[] = { "L251", "foo.o", "bar.o", "baz.o", "qux.o", "quux.lib", "corge.lib", "grault.o", NULL };
    const char *expected7[] = { "rm", "corge.lib", NULL };
    const char **expected[] = { expected1, expected2, expected3, expected4, expected5, expected6, expected7, NULL };
    assertConversion(input, expected);
}

A_Test void usingMarch8051SelectsC51Toolchain(void)
{
    const char *input[] = { "cc", "-I", "inc1", "-Iinc2", "-D", "FOO", "-DBAR=10", "-march=8051", "foo.c", "bar.s", "baz.o", "qux.i", "quux.lib", "corge.a", "grault.c", "NULL" };
    const char *expected1[] = { "C51", "foo.c", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(foo.o)", NULL };
    const char *expected2[] = { "A51", "bar.s", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(bar.o)", NULL };
    const char *expected3[] = { "C51", "qux.i", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(qux.o)", NULL };
    const char *expected4[] = { "C51", "grault.c", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(grault.o)", NULL };
    const char *expected5[] = { "ar", "x", "corge.a", "corge.lib", NULL };
    const char *expected6[] = { "L51", "foo.o", "bar.o", "baz.o", "qux.o", "quux.lib", "corge.lib", "grault.o", NULL };
    const char *expected7[] = { "rm", "corge.lib", NULL };
    const char **expected[] = { expected1, expected2, expected3, expected4, expected5, expected6, expected7, NULL };
    assertConversion(input, expected);
}

A_Test void usingMarch80251SelectsC251Toolchain(void)
{
    const char *input[] = { "cc", "-I", "inc1", "-Iinc2", "-D", "FOO", "-DBAR=10", "-march=80251", "foo.c", "bar.s", "baz.o", "qux.i", "quux.lib", "corge.a", "grault.c", "NULL" };
    const char *expected1[] = { "C251", "foo.c", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(foo.o)", NULL };
    const char *expected2[] = { "A251", "bar.s", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(bar.o)", NULL };
    const char *expected3[] = { "C251", "qux.i", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(qux.o)", NULL };
    const char *expected4[] = { "C251", "grault.c", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(grault.o)", NULL };
    const char *expected5[] = { "ar", "x", "corge.a", "corge.lib", NULL };
    const char *expected6[] = { "L251", "foo.o", "bar.o", "baz.o", "qux.o", "quux.lib", "corge.lib", "grault.o", NULL };
    const char *expected7[] = { "rm", "corge.lib", NULL };
    const char **expected[] = { expected1, expected2, expected3, expected4, expected5, expected6, expected7, NULL };
    assertConversion(input, expected);
}

A_Test void usingMarchC166SelectsC166Toolchain(void)
{
    const char *input[] = { "cc", "-I", "inc1", "-Iinc2", "-D", "FOO", "-DBAR=10", "-march=80251", "foo.c", "bar.s", "baz.o", "qux.i", "quux.lib", "corge.a", "grault.c", "NULL" };
    const char *expected1[] = { "C166", "foo.c", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(foo.o)", NULL };
    const char *expected2[] = { "A166", "bar.s", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(bar.o)", NULL };
    const char *expected3[] = { "C166", "qux.i", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(qux.o)", NULL };
    const char *expected4[] = { "C166", "grault.c", "INCDIR(inc1,inc2)", "DEFINE(FOO,BAR=10)", "OBJECT(grault.o)", NULL };
    const char *expected5[] = { "ar", "x", "corge.a", "corge.lib", NULL };
    const char *expected6[] = { "L166", "foo.o", "bar.o", "baz.o", "qux.o", "quux.lib", "corge.lib", "grault.o", NULL };
    const char *expected7[] = { "rm", "corge.lib", NULL };
    const char **expected[] = { expected1, expected2, expected3, expected4, expected5, expected6, expected7, NULL };
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
