#include "Entity.hpp"
#include "EntityManager.hpp"

#include <iostream>

Entity::Entity(EntityManager* manager) : mManager(manager)
{
    mLife = 100;
    mMaxLife = mLife;
    mSpeed = 60;
    mDamage = 10;
    mDirection = Direction::S;
    mMovingTime = sf::Time::Zero;
    mCooldownTimer = sf::seconds(0.4f);
}

void Entity::update(sf::Time dt)
{
}

void Entity::handleEvent(sf::Event const& event)
{
}

int Entity::getLife()
{
    return mLife;
}

int Entity::getMaxLife()
{
    return mMaxLife;
}

int Entity::getSpeed()
{
    return mSpeed;
}

int Entity::getDamage()
{
    return mDamage;
}

void Entity::setLife(int life)
{
    mLife = std::min(life,mMaxLife);
}

void Entity::setMaxLife(int maxLife)
{
    mMaxLife = maxLife;
}

void Entity::setSpeed(int speed)
{
    mSpeed = speed;
}

void Entity::setDamage(int damage)
{
    mDamage = damage;
}

void Entity::inflige(int damage)
{
    mLife -= damage;
    mLife = std::max(mLife,0);
    mLife = std::min(mLife,mMaxLife);
}

void Entity::heal(int heal)
{
    mLife += heal;
    mLife = std::min(mLife,mMaxLife);
    mLife = std::max(mLife,0);
}

bool Entity::isDead()
{
    return mLife <= 0;
}

bool Entity::isAttacking()
{
    return mCooldownTimer != sf::seconds(0.4f);
}

sf::FloatRect Entity::getBounds() const
{
    return sf::FloatRect(getPosition().x - getOrigin().x, getPosition().y - getOrigin().y, mSprite.getGlobalBounds().width,mSprite.getGlobalBounds().height);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    if (mDirection == Direction::N)
    {
        target.draw(mWeapon);
    }

    target.draw(mSprite,states);

    if (mDirection != Direction::N)
    {
        target.draw(mWeapon);
    }

    if (mLife < mMaxLife)
    {
        sf::RectangleShape bg;
        bg.setPosition(mSprite.getGlobalBounds().width/2 - 15,0);
        bg.setSize(sf::Vector2f(30,7));
        bg.setFillColor(sf::Color::Red);
        bg.setOutlineThickness(1);
        bg.setOutlineColor(sf::Color::Black);
        target.draw(bg,states);
        sf::RectangleShape l;
        l.setPosition(mSprite.getGlobalBounds().width/2 - 15,0);
        l.setSize(sf::Vector2f(30.f * static_cast<float>(mLife) / static_cast<float>(mMaxLife),7));
        l.setFillColor(sf::Color::Green);
        target.draw(l,states);
    }
}

void Entity::attack(Entity* entity)
{
    if (!isAttacking())
    {
        if (entity != nullptr)
        {

            entity->inflige(mDamage + mWeapon.getDamage());

            mCooldownTimer = sf::seconds(0);

        }
    }
}

void Entity::updateDirection(sf::Vector2f goTo)
{
    sf::Vector2f diff = goTo - getPosition();
    float angle = - atan2(diff.y,diff.x) * 180 / 3.14159265;
    while(angle >= 360)
        angle -= 360;
    while(angle < 0)
        angle += 360;
    if((angle > 0 && angle < 45) || (angle >= 315 && angle < 360))
        mDirection = Direction::E;
    else if(angle >= 45 && angle < 135)
        mDirection = Direction::N;
    else if(angle >= 135 && angle < 225)
        mDirection = Direction::W;
    else if (angle >= 225 && angle < 315)
        mDirection = Direction::S;
}

void Entity::updateMovement(sf::Vector2f goTo, sf::Time dt)
{
    sf::Vector2f movement;
    sf::Vector2f diff = goTo - getPosition();
    float angle = atan2(diff.y,diff.x);
    movement = sf::Vector2f(std::cos(angle),std::sin(angle));
    movement.x *= mSpeed;
    movement.y *= mSpeed;
    movement *= dt.asSeconds();
    move(movement);
}

void Entity::updateAnimation(sf::Time dt)
{
    mMovingTime += dt;

    if (mMovingTime >= sf::seconds(0.8))
    {
        mMovingTime -= sf::seconds(0.8);
    }

    int value = 0;
    if ((mMovingTime >= sf::seconds(0) && mMovingTime < sf::seconds(0.1))
    || (mMovingTime >= sf::seconds(0.35) && mMovingTime < sf::seconds(0.45))
    || (mMovingTime >= sf::seconds(0.7) && mMovingTime < sf::seconds(0.8)))
    {
        value = 0;
    }
    else if (mMovingTime >= sf::seconds(0.1) && mMovingTime < sf::seconds(0.35))
    {
        value = 1;
    }
    else if (mMovingTime >= sf::seconds(0.45) && mMovingTime < sf::seconds(0.7))
    {
        value = 2;
    }

    mSprite.setTextureRect(sf::IntRect(mSprite.getGlobalBounds().width * value,mSprite.getGlobalBounds().height * static_cast<int>(mDirection),mSprite.getGlobalBounds().width,mSprite.getGlobalBounds().height));
}

void Entity::stopMoving()
{
    mMovingTime = sf::Time::Zero;
    mSprite.setTextureRect(sf::IntRect(0,mSprite.getGlobalBounds().height * static_cast<int>(mDirection),mSprite.getGlobalBounds().width,mSprite.getGlobalBounds().height));
}

void Entity::updateWeapon(sf::Time dt)
{
    if (isAttacking())
    {
        mCooldownTimer += dt;
        if (mCooldownTimer > sf::seconds(0.4))
        {
            mCooldownTimer = sf::seconds(0.4);
        }
    }

    if (mWeapon.getType() == Weapon::Nothing)
        return;

    sf::Vector2f pos = sf::Vector2f(0,0);
    float angle = 0.f;
    if (mMovingTime != sf::Time::Zero) // Moving
    {
        if ((mMovingTime >= sf::seconds(0) && mMovingTime < sf::seconds(0.1))
        || (mMovingTime >= sf::seconds(0.35) && mMovingTime < sf::seconds(0.45))
        || (mMovingTime >= sf::seconds(0.7) && mMovingTime < sf::seconds(0.8)))
        {
            switch (mDirection)
            {
                case E: pos = sf::Vector2f(12-13.5,7); angle = 45; break;
                case N: pos = sf::Vector2f(24-13.5,4); angle = 30; break;
                case W: pos = sf::Vector2f(10-13.5,3); angle = -45; break;
                case S: pos = sf::Vector2f(2-13.5,4); angle = -30; break;
                default: app::System::getLog() << "Unknown direction"; break;
            }
        }
        else if (mMovingTime >= sf::seconds(0.1) && mMovingTime < sf::seconds(0.35))
        {
            switch (mDirection)
            {
                case E: pos = sf::Vector2f(0.5,4); angle = 60; break;
                case N: pos = sf::Vector2f(9.5,4); angle = 20; break;
                case W: pos = sf::Vector2f(-2.5,3); angle = -60; break;
                case S: pos = sf::Vector2f(-9.5,3); angle = -20; break;
                default: app::System::getLog() << "Unknown direction"; break;
            }
        }
        else if (mMovingTime >= sf::seconds(0.45) && mMovingTime < sf::seconds(0.7))
        {
            switch (mDirection)
            {
                case E: pos = sf::Vector2f(-5.5,6); angle = 60; break;
                case N: pos = sf::Vector2f(-9.5,2); angle = 20; break;
                case W: pos = sf::Vector2f(-1.5,4); angle = -60; break;
                case S: pos = sf::Vector2f(-9.5,4);angle = -20; break;
                default: app::System::getLog() << "Unknown direction"; break;
            }
        }
    }
    else if (isAttacking()) // Attack
    {
        if (mCooldownTimer < sf::seconds(0.2f))
        {
            switch (mDirection)
            {
                case E: pos = sf::Vector2f(-1.5,7); angle = 45 + std::min(45 * mCooldownTimer.asSeconds()/0.1f,45.f); break;
                case N: pos = sf::Vector2f(10.5,4); angle = 30 + std::min(45 * mCooldownTimer.asSeconds()/0.1f,45.f); break;
                case W: pos = sf::Vector2f(-3.5,3); angle = -45 - std::min(45 * mCooldownTimer.asSeconds()/0.1f,45.f); break;
                case S: pos = sf::Vector2f(-11.5,4); angle = -30 - std::min(45 * mCooldownTimer.asSeconds()/0.1f,45.f); break;
                default: app::System::getLog() << "Unknown direction"; break;
            }
        }
        else
        {
            switch (mDirection)
            {
                case E: pos = sf::Vector2f(-1.5,7); angle = 45 - std::min(45 * mCooldownTimer.asSeconds()/0.1f,45.f); break;
                case N: pos = sf::Vector2f(10.5,4); angle = 30 - std::min(45 * mCooldownTimer.asSeconds()/0.1f,45.f); break;
                case W: pos = sf::Vector2f(-3.5,3); angle = -45 + std::min(45 * mCooldownTimer.asSeconds()/0.1f,45.f); break;
                case S: pos = sf::Vector2f(-11.5,4); angle = -30 + std::min(45 * mCooldownTimer.asSeconds()/0.1f,45.f); break;
                default: app::System::getLog() << "Unknown direction"; break;
            }
        }
    }
    else // Standing
    {
        switch (mDirection)
        {
            case E: pos = sf::Vector2f(-1.5,7); angle = 45; break;
            case N: pos = sf::Vector2f(10.5,4); angle = 30; break;
            case W: pos = sf::Vector2f(-3.5,3); angle = -45; break;
            case S: pos = sf::Vector2f(-11.5,4); angle = -30; break;
            default: app::System::getLog() << "Unknown direction"; break;
        }
    }

    mWeapon.setPosition(getPosition() + pos);
    mWeapon.setRotation(angle);
}

void Entity::setWeaponType(Weapon::Type type)
{
    mWeapon.setType(type);
}

Weapon::Type Entity::getWeaponType()
{
    return mWeapon.getType();
}
