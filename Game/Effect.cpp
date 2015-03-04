#include "Effect.hpp"

Effect::Effect()
{
    mLimit = sf::Time::Zero;
}

sf::Sprite& Effect::getSprite()
{
    return mSprite;
}

void Effect::setLimit(sf::Time limit)
{
    mLimit = limit;
}

sf::Time Effect::getLimit() const
{
    return mLimit;
}

sf::Time Effect::getActualTime() const
{
    return mClock.getElapsedTime();
}

bool Effect::remove() const
{
    return getActualTime() > getLimit();
}
