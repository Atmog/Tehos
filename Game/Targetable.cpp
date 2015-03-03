#include "Targetable.hpp"

Targetable::Targetable()
{
    mTeam = Targetable::None;
}

void Targetable::setTeam(Team team)
{
    mTeam = team;
}

Targetable::Team Targetable::getTeam() const
{
    return mTeam;
}

void Targetable::setLife(int life)
{
    mLife = life;
}

int Targetable::getLife() const
{
    return mLife;
}

void Targetable::setMaxLife(int maxLife)
{
    mMaxLife = maxLife;
}

int Targetable::getMaxLife() const
{
    return mMaxLife;
}

void Targetable::inflige(int amount)
{
    mLife -= amount;
    mLife = std::max(0,mLife);
}

void Targetable::restore(int amount)
{
    mLife += amount;
    mLife = std::min(mMaxLife,mLife);
}

bool Targetable::isAlive() const
{
    return mLife > 0;
}

bool Targetable::isDead() const
{
    return mLife <= 0;
}

void Targetable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite,states);

    if (mLife < mMaxLife)
    {
        sf::RectangleShape bg;
        bg.setSize(sf::Vector2f(30,7));
        bg.setPosition(sf::Vector2f(-15,-105));
        bg.setFillColor(sf::Color::Red);
        bg.setOutlineThickness(1);
        bg.setOutlineColor(sf::Color::Black);
        target.draw(bg,states);

        sf::RectangleShape l;
        l.setSize(sf::Vector2f(30.f * static_cast<float>(mLife) / static_cast<float>(mMaxLife),7));
        l.setPosition(sf::Vector2f(-15,-105));
        l.setFillColor(sf::Color::Green);
        target.draw(l,states);
    }
}

bool Targetable::remove() const
{
    return isDead();
}
