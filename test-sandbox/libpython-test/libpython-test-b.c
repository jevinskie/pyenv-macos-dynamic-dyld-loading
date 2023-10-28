#include "libpython-test.h"

#include <stdio.h>

__attribute__((constructor)) void libpython_test_a_ctor() {
    printf("libpython-test-a ctor\n");
}

const char *get_python_test_version(void) {
    return "I'm libpython-test-b!";
}
