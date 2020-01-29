#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <cal3d.h>
#include "Log.h"

const char* s_levelStrings[] = { "[INFO] %s\n", "[WARNING] %s\n", "[ERROR] %s\n" };

namespace Log {
    void Log(LogLevel level, const char* format, ...) {
        char finalFormat[1024];
        sprintf(finalFormat, s_levelStrings[level], format);
        va_list args;
        va_start(args, format);
        if (FATAL == level) {
            vfprintf(stderr, finalFormat, args);
        } else
            vfprintf(stdout, finalFormat, args);
        va_end(args);
    }

    void LogWinApi(LogLevel level) {
        // retrieve the error message from the Windows API
        char* errorBuffer = NULL;
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,                 // no optional lpSource
            GetLastError(),       // error ID
            0,                    // language
            (LPTSTR)&errorBuffer, // error string pointer
            0,                    // minimum buffer size
            NULL                  // no optional va_list
        );
        // write the error string to the console
        Log(level, errorBuffer);
        // free Windows API error string
        LocalFree(errorBuffer);
    }

    void LogCal3d(LogLevel level) {
        cal3d::CalError::printLastError();
    }

    void PrintBuffer(char* buffer, int size) {
        // printf("Printing buffer of length %i...", size);
        for (int i = 0; i < size; i++) {
            printf("%02Xh ", (char)buffer[i]);
        }
        printf("\n");
    }
}
