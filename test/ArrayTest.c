#include "../src/Array.h"
#include "ArrayTest.h"
#include <stdint.h>

const uint32_t testArray[] = {1, 2, 3};

A_Test void ArrayTest_getLength(void)
{
    assertEquals("", 3, Array_getLength(testArray));
}

A_Test void ArrayTest_isIndexValid(void)
{
    assertFalse("", Array_isIndexValid(testArray, -1));
    assertTrue("", Array_isIndexValid(testArray, 0));
    assertTrue("", Array_isIndexValid(testArray, 1));
    assertTrue("", Array_isIndexValid(testArray, 2));
    assertFalse("", Array_isIndexValid(testArray, 3));
}
