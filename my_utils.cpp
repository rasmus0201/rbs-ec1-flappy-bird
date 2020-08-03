#include "mbed.h"
#include "my_utils.h"

unsigned number_of_digits(unsigned i)
{
    return i > 0 ? (int) log10((double) i) + 1 : 1;
}