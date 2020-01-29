#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "platform/Time.h"
#include "Log.h"

static LONGLONG s_frequency;
static double s_lastTime, s_elapsedSeconds;

namespace Clock {
    void Init() {
        if (!QueryPerformanceFrequency((LARGE_INTEGER*)&s_frequency))
            Log::LogWinApi(Log::FATAL);
        s_lastTime = GetTime();
    }

    void Update() {
        double newTime = GetTime();
        s_elapsedSeconds = (double)(newTime - s_lastTime);
        s_lastTime = newTime;
    }

    double GetTime() {
        LONGLONG ticks;
        QueryPerformanceCounter((LARGE_INTEGER*)&ticks);
        return ticks / (double)s_frequency;
    }

    double GetElapsedSeconds() {
        return s_elapsedSeconds * 2.0f; // @FIXME: ANIMATION FIX
    }
}
