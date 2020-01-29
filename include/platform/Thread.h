#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class Thread {
private:
    HANDLE handle;
public:
    Thread(void* proc, void* param, bool start);
    ~Thread();
    void waitUntilDone();
    void start();
    void stop();
    void pause();
};

class ThreadLock {
private:
    HANDLE handle;
public:
    ThreadLock();
    ~ThreadLock();
    void release();
    void waitForRelease();
};
