#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "error.h"
#include "acegames/acegames.h"

static char* s_lastError = NULL;

namespace Error {
void SetError(const char* format, ...) {
    // Prevent multiple errors
    if (s_lastError) return;

    // Allocate and write error
    s_lastError = (char*)malloc(1024);
    va_list args;
    va_start(args, format);
    vsprintf(s_lastError, format, args);
    va_end(args);
}
}

/**
 * @return const char* Error string if an error had occurred.
 *         NULL if no errors were found.
 */
ACEGAMES const char* Ace_GetErrorString() {
    char* err = s_lastError;
    s_lastError = NULL;
    return err;
}
