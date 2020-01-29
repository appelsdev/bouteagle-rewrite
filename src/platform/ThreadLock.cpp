#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Log.h"
#include "platform/Thread.h"

ThreadLock::ThreadLock() {
    HANDLE h = CreateEvent(0, FALSE, FALSE, 0);
    if (!h)
        Log::LogWinApi(Log::FATAL);
    this->handle = h;
}

ThreadLock::~ThreadLock() {
    if (!CloseHandle(this->handle))
        Log::LogWinApi(Log::WARNING);
}

void ThreadLock::release() {
    if (!SetEvent(this->handle))
        Log::LogWinApi(Log::FATAL);
}

void ThreadLock::waitForRelease() {
    switch (WaitForSingleObject(this->handle, INFINITE)) {
    case WAIT_OBJECT_0:
        break;
    case WAIT_FAILED:
        Log::LogWinApi(Log::WARNING);
    }
}
