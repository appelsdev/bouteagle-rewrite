#include "platform/Time.h"

static double s_deltaTime = 1.0, s_timeStart, s_timeStartOld;

namespace DeltaTime {
    void Calculate() {
        s_timeStart = Clock::GetTime();
        s_deltaTime = s_timeStart - s_timeStartOld;
        s_timeStartOld = s_timeStart;
    }

    double Get() {
        return s_deltaTime;
    }
}
