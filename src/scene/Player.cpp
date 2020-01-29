#include "platform/InputRouter.h"
#include "platform/Time.h" // FIXME
#include "scene/Player.h"
#include "Log.h" // FIXME

Player::Player() : Entity() {
    this->animId = 0;
    // this->animTimeLeft = 0.0f;
}

Player::~Player() {

}

void Player::walkLeft() {
    /* this->animTimeLeft -= Clock::GetElapsedSeconds();
    if (this->animTimeLeft <= 0.5f) {
        this->animId = (this->animId + 1) % this->calModel->getCoreModel()->getCoreAnimationCount();
        this->calModel->getMixer()->executeAction(this->animId, this->animTimeLeft, 0.5f);
        this->animTimeLeft = this->calModel->getCoreModel()->getCoreAnimation(this->animId)->getDuration() - 0.5f;
    }
    Log::Log(Log::INFO, "Frame %i", this->animId); */
    x -= .1f;
}

void Player::walkRight() {
    x += .1f;
}

void Player::walkUp() {
    z -= .1f;
}

void Player::walkDown() {
    z += .1f;
}
/*
// update the model if not paused
if (!m_bPaused) {
    // check if the time has come to blend to the next animation
    if (m_calCoreModel->getCoreAnimationCount() > 1) {
        m_leftAnimationTime -= elapsedSeconds;
        if (m_leftAnimationTime <= m_blendTime) {
            // get the next animation
            m_currentAnimationId = (m_currentAnimationId + 1) % m_calCoreModel->getCoreAnimationCount();

            // fade in the new animation
            m_calModel->getMixer()->executeAction(m_currentAnimationId, m_leftAnimationTime, m_blendTime);

            // adjust the animation time left until next animation flip
            m_leftAnimationTime = m_calCoreModel->getCoreAnimation(m_currentAnimationId)->getDuration() - m_blendTime;
        }
    }
    m_calModel->update(elapsedSeconds);
}
// current tick will be last tick next round
m_lastTick = tick;*/
