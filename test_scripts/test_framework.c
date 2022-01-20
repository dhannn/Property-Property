#include <stdarg.h>
#include "testFramework.h"

struct test {
    void (*setup)(va_list);
    void (*testFunc)(va_list);
    void (*destroy)(va_list);
};
