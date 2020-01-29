#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Log.h"
#include "platform/Thread.h"

Thread::Thread(void* proc, void* param, bool start) {
    HANDLE h = CreateThread(
        NULL, // default security descriptor
        0, // default stack size
        (LPTHREAD_START_ROUTINE)proc, // thread procedure
        param, // no thread procedure parameters
        start ? 0 : CREATE_SUSPENDED, // decide auto-launch
        NULL // no need to obtain the thread identifier
    );
    if (!h)
        Log::LogWinApi(Log::WARNING);
    this->handle = h;
}

Thread::~Thread() {
    if (this->handle && !CloseHandle(this->handle))
        Log::LogWinApi(Log::WARNING);
}

void Thread::waitUntilDone() {
    switch (WaitForSingleObject(this->handle, INFINITE)) {
    case WAIT_OBJECT_0:
        Log::Log(Log::INFO, "Thread wait success.");
        break;
    case WAIT_FAILED:
        Log::LogWinApi(Log::WARNING);
    }
}

void Thread::start() {
    if (-1 == ResumeThread(this->handle))
        Log::LogWinApi(Log::FATAL);
}

void Thread::pause() {
    if (-1 == SuspendThread(this->handle))
        Log::LogWinApi(Log::FATAL);
}
