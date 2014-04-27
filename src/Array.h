#ifndef ARRAY_H
#define ARRAY_H

#define Array_getLength(array) (sizeof(array) / sizeof((array)[0]))

#define Array_isIndexValid(array, index) (((index) >= 0) && ((index) < Array_getLength(array)))

#endif
