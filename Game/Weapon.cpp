#include "Weapon.hpp"

Weapon::Weapon()
{
    mSprite.setTexture(app::System::getResources().getTexture("Weapons"));
    setType(Weapon::Nothing);
    mSprite.setOrigin(mSprite.getGlobalBounds().width/2,mSprite.getGlobalBounds().height/2);
}

Weapon::Weapon(Type type)
{
    mSprite.setTexture(app::System::getResources().getTexture("Weapons"));
    setType(mType);
    mSprite.setOrigin(mSprite.getGlobalBounds().width/2,mSprite.getGlobalBounds().height/2);
}

void Weapon::setType(int type)
{
    switch (type)
    {
        case 0: setType(Nothing); break;
        case 1: setType(Stick); break;
        case 2: setType(Baton); break;
        case 3: setType(Sword); break;
        case 4: setType(LightSaber); break;
        default: app::System::getLog() << "Unknown Weapon";
    }
    mSprite.setScale(2,2);
    mSprite.setOrigin(mSprite.getGlobalBounds().width/4,mSprite.getGlobalBounds().height/4);
}

void Weapon::setType(Type type)
{
    mType = type;

    mSprite.setTextureRect(sf::IntRect(7 * static_cast<int>(mType),0,7,48));
}

Weapon::Type Weapon::getType()
{
    return mType;
}

int Weapon::getPrice()
{
    switch (mType)
    {
        case Nothing: return 0; break;
        case Stick: return 10; break;
        case Baton: return 25; break;
        case Sword: return 50; break;
        case LightSaber: return 100; break;
        default: app::System::getLog() << "Unknown weapon"; break;
    }
    return 0;
}

int Weapon::getDamage()
{
    switch (mType)
    {
        case Nothing: return 0; break;
        case Stick: return 5; break;
        case Baton: return 13; break;
        case Sword: return 25; break;
        case LightSaber: return 50; break;
        default: app::System::getLog() << "Unknown weapon"; break;
    }
    return 0;
}

float Weapon::getCooldown()
{
    switch (mType)
    {
        case Nothing: return 0.4f; break;
        case Stick: return 0.4f; break;
        case Baton: return 0.4f; break;
        case Sword: return 0.4f; break;
        case LightSaber: return 0.4f; break;
        default: app::System::getLog() << "Unknown weapon"; break;
    }
    return 0.4f;
}

void Weapon::setRotation(float angle)
{
    mSprite.setRotation(angle);
}

void Weapon::setPosition(sf::Vector2f position)
{
    mSprite.setPosition(position);
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite);
}
