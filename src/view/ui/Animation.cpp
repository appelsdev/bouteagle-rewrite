#include "platform/Time.h"
#include "view/ui/UIElement.h"

using namespace UI;
Animation::Animation() {
    type = IMAGE_ANIMATED;
}

void Animation::update() {
    index += Clock::GetElapsedSeconds();
    if ((int)index > frames) {
        index = 0;
    }
}

int Animation::getFrames() {
    return frames;
}

int Animation::getIndex() {
    return (int)index;
}

void Animation::setFrames(int frames) {
    this->frames = frames;
}
