#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "thread.h"

Thread::Thread(void* proc, void* param, bool start) {
    HANDLE h = CreateThread(
        NULL, // default security descriptor
        0, // default stack size
        (LPTHREAD_START_ROUTINE)proc, // thread procedure
        param, // no thread procedure parameters
        start ? 0 : CREATE_SUSPENDED, // decide auto-launch
        NULL // no need to obtain the thread identifier
    );
    this->handle = h;
}

Thread::~Thread() {
    if (this->handle)
        CloseHandle(this->handle);
}

void Thread::waitUntilDone() {
    WaitForSingleObject(this->handle, INFINITE);
}

void Thread::start() {
    ResumeThread(this->handle);
}

void Thread::pause() {
    SuspendThread(this->handle);
}
