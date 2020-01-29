#pragma once
class ViewMatrix {
private:
    float distance;
    float scale;
    float tiltAngle;
    float twistAngle;
    float camheight;
public:
    ViewMatrix();
    void calcAndApply();
};
