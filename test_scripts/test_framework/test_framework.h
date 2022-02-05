#include <stdarg.h>
#define LOG_FILE "log2.txt"

typedef void(*setup_t)();
typedef void(*test_t)();
typedef void(*func_t)();
typedef void(*destroy_t)();

typedef struct {
    setup_t setup;          // pointer to the function that sets up variables
    func_t function;        // pointer to the function to be tested
    destroy_t destroy;      // pointer to the function that cleans up every test
    test_t *test;           // the tests that will be done in the test case
    int numTest;
} testcase_t;

void addTestCase(
    testcase_t *testcase,
    setup_t setup,
    destroy_t destroy,
    int numberOfTests,
    ...
);

void addTest(testcase_t *testcase, test_t test);
void runTestCase(testcase_t testcase, char *title);

void assertEqualInt(int expected, int actual);
void assertEqualStr(char *expected, char *actual);
void assertNull(void *ptr);
void assertNotNull(void *ptr);
