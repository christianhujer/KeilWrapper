#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "AceUnit.h"
#include "ExpectWrapTest.h"

/** Returns the index at which the NULL-terminated string arrays \p array1 and \p array2 differ, or -1 in case they are equal.
 * Compares the string arrays \p array1 and \p array2 for equality.
 * The strings themselves are compared using <code>strcmp</code>.
 *
 * @param array1
 *      First NULL-terminated string array to compare.
 *
 * @param array2
 *      Second NULL-terminated string array to compare.
 *
 * @return index at which \p array1 and \p array2 differ.
 * @retval -1 in case \p array1 and \p array2 are equal.
 */
static int strarrcmp(const char *array1[], const char *array2[])
{
    for (int index = 0; (array1[index] != NULL) || (array2[index] != NULL); index++)
        if (array1[index] == NULL || array2[index] == NULL || strcmp(array1[index], array2[index]))
            return index;
    return -1;
}

void assertStringArrayEquals(const char *array1[], const char *array2[])
{
    assertEquals("", -1, strarrcmp(array1, array2));
}

void assertStringArrayNotEquals(const char *array1[], const char *array2[])
{
    assertNotEquals("", -1, strarrcmp(array1, array2));
}

A_Test void twoEmptyStringArrays_areEqual(void)
{
    const char *emptyArray[] = { NULL };
    assertStringArrayEquals(emptyArray, emptyArray);
}

A_Test void emptyAndNonEmptyArray_areNotEqual(void)
{
    const char *emptyArray[] = { NULL };
    const char *nonEmptyArray[] = { "foo", NULL };
    assertStringArrayNotEquals(emptyArray, nonEmptyArray);
}

A_Test void equalElementArraysOfSameLength_areEqual(void)
{
    const char *nonEmptyArray[] = { "foo", NULL };
    assertStringArrayEquals(nonEmptyArray, nonEmptyArray);
}

A_Test void differentElementArraysOfSameLength_areDifferent(void)
{
    const char *nonEmptyArray1[] = { "foo", NULL };
    const char *nonEmptyArray2[] = { "bar", NULL };
    assertStringArrayNotEquals(nonEmptyArray1, nonEmptyArray2);
}

A_Test void longerEqualArray(void)
{
    const char *longerArray1[] = { "foo", "bar", "quux", NULL };
    const char *longerArray2[] = { "foo", "bar", "quux", NULL };
    assert(longerArray1 != longerArray2);
    assertStringArrayEquals(longerArray1, longerArray2);
}
