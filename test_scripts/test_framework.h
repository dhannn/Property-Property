#include <stdarg.h>

typedef void(*setup_t)(va_list);
typedef void(*test_t)(va_list);
typedef void(*func_t)(va_list);
typedef void(*destroy_t)(va_list);

typedef struct {
    setup_t setup;          // pointer to the function that sets up variables
    func_t function;        // pointer to the function to be tested
    destroy_t destroy;      // pointer to the function that cleans up every test
    int numTest;
    test_t *test;           // the tests that will be done in the test case
} testcase_t;

void addTestCase(testcase_t *testcase, setup_t setup, destroy_t destroy, int numberOfTests);
void addTest(testcase_t *testcase, test_t test);
void runTestCase(testcase_t testcase, char *title);

int assertEqualInt(int expected, int actual);
