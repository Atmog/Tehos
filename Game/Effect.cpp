#include "Effect.hpp"

Effect::Effect(sf::Int64 frames, sf::Time timePerFrame)
: mFrames(frames)
, mTimePerFrame(timePerFrame)
{
}

void Effect::update(sf::Time dt)
{
    mSprite.setTextureRect(sf::IntRect(
    sf::Vector2i(static_cast<int>(mClock.getElapsedTime()/mTimePerFrame) * mFrameSize.x,0),
    mFrameSize));
}

bool Effect::remove() const
{
    return mClock.getElapsedTime() > mFrames * mTimePerFrame;
}
