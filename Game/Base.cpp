#include "Base.hpp"

Base::Base(Targetable::Team team)
{
    mTeam = team;
    if (mTeam == Targetable::Red)
        mSprite.setTexture(cf::Application::getResources().getTexture("Assets/Textures/basered.png"));
    if (mTeam == Targetable::Blue)
        mSprite.setTexture(cf::Application::getResources().getTexture("Assets/Textures/baseblue.png"));
    mSprite.setOrigin(25,200);
    mLife = 1000.f;
    mMaxLife = 1000.f;
    mSpawnRadius = 500.f;
}

void Base::drawSpawnZone(sf::RenderTarget& target) const
{
    sf::CircleShape c;
    c.setPosition(getPosition());
    c.setRadius(mSpawnRadius);
    c.setPointCount(256);
    c.setOrigin(mSpawnRadius,mSpawnRadius);
    c.setOutlineThickness(1);
    sf::Color color;
    if (mTeam == Targetable::Red)
        color = sf::Color::Red;
    if (mTeam == Targetable::Blue)
        color = sf::Color::Blue;
    c.setOutlineColor(color);
    color.a = 16.f;
    c.setFillColor(color);
    target.draw(c);
}

void Base::draw(sf::RenderTarget& target, sf::RenderStates states) const
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

void Base::setSpawnRadius(float radius)
{
    mSpawnRadius = radius;
}

float Base::getSpawnRadius() const
{
    return mSpawnRadius;
}

void Base::transparence(bool transparent)
{
    if (transparent)
    {
        sf::Color c = sf::Color::White;
        c.a = 160.f;
        mSprite.setColor(c);
    }
    else
    {
        mSprite.setColor(sf::Color::White);
    }
}
