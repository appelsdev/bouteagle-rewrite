#pragma once

namespace Clock {
    void Init();
    void Update();
    double GetTime();
    double GetElapsedSeconds();
}

namespace DeltaTime {
    void Calculate();
    double Get();
}
