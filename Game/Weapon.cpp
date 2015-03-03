#include "Weapon.hpp"

Weapon::Weapon()
{
    mSprite.setTexture(cf::Application::getResources().getTexture("Assets/Textures/weapons.png"));
    mForce = 60;
    mRange = 60;
}

void Weapon::setForce(int force)
{
    mForce = force;
}

int Weapon::getForce() const
{
    return mForce;
}

std::string Weapon::getName() const
{
    return " ";
}

void Weapon::setRange(float range)
{
    mRange = range;
}

float Weapon::getRange() const
{
    return mRange;
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite,states);
}
