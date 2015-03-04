#include "Entity.hpp"
#include "World.hpp"

Entity::Entity(Targetable::Team team)
{
    mTeam = team;
    if (mTeam == Targetable::Blue)
    {
        mSprite.setTexture(cf::Application::getResources().getTexture("Assets/Textures/playerblue.png"));
    }
    else
    {
        mSprite.setTexture(cf::Application::getResources().getTexture("Assets/Textures/playerred.png"));
    }
    mDirection = Entity::S;
    mSprite.setTextureRect(sf::IntRect(0,mDirection*121,61,121));
    mSprite.setOrigin(sf::Vector2f(30.5,121));
    mSpeed = 100.f;
    mWeapon = nullptr;
    mCollision->setPointCount(4);
    mCollision->setPoint(0,sf::Vector2f(-20,-20));
    mCollision->setPoint(1,sf::Vector2f(20,-20));
    mCollision->setPoint(2,sf::Vector2f(20,10));
    mCollision->setPoint(3,sf::Vector2f(-20,10));
}

void Entity::setWeapon(Weapon* weapon)
{
    mWeapon = weapon;
}

Weapon* Entity::getWeapon() const
{
    return mWeapon;
}

void Entity::handleEvent(sf::Event const& event)
{
}

void Entity::update(sf::Time dt)
{
    if (mTarget != nullptr)
        if (mTarget->isDead())
            mTarget = nullptr;

    if (mTarget == nullptr && mWorld != nullptr)
        mTarget = mWorld->findNearestTarget(this);

    if (mTarget != nullptr && mWorld != nullptr)
    {
        sf::Vector2f movement = sf::Vector2f(0,0);

        sf::Vector2f diff = mTarget->getPosition() - getPosition();
        float angle = - cf::atan2(diff.y,diff.x);
        while(angle >= 360)
            angle -= 360;
        while(angle < 0)
            angle += 360;
        if((angle > 0 && angle < 22.5) || (angle >= 337.5 && angle < 360))
            mDirection = Entity::E;
        else if(angle >= 22.5 && angle < 67.5)
            mDirection = Entity::NE;
        else if(angle >= 67.5 && angle < 112.5)
            mDirection = Entity::N;
        else if(angle >= 112.5 && angle < 157.5)
            mDirection = Entity::NW;
        else if(angle >= 157.5 && angle < 202.5)
            mDirection = Entity::W;
        else if(angle >= 202.5 && angle < 247.5)
            mDirection = Entity::SW;
        else if(angle >= 247.5 && angle < 292.5)
            mDirection = Entity::S;
        else if(angle >= 292.5 && angle < 337.5)
            mDirection = Entity::SE;

        movement.x = cf::cos(angle) * mSpeed * dt.asSeconds();
        movement.y = cf::sin(-angle) * mSpeed * dt.asSeconds();

        if (mWeapon != nullptr)
            if (cf::distance(mTarget->getPosition(),getPosition()) < mWeapon->getRange())
                movement = sf::Vector2f(0,0);
        if (mWeapon == nullptr)
            if (cf::distance(mTarget->getPosition(),getPosition()) < 50)
                movement = sf::Vector2f(0,0);

        // TODO : handle Collisions
        if (movement != sf::Vector2f(0,0))
        {
            mCollision->setPosition(getPosition());
            mWorld->getCollisionManager().movementCorrection(mCollision,movement);
            move(movement);
            mMovingTime += dt;
        }
        else
        {
            mMovingTime = sf::Time::Zero;
            // TODO : PLAY SOUND ?
        }

        if (mMovingTime > sf::seconds(0.8f))
            mMovingTime = sf::Time::Zero;

        if (mWeapon != nullptr)
        {
            if (mLastAttack.getElapsedTime() > sf::seconds(1) && cf::distance(mTarget->getPosition(),getPosition()) < mWeapon->getRange())
            {
                mTarget->inflige(mWeapon->getForce());
                mLastAttack.restart();
                // TODO : ANIMATION
                // TODO : PLAY SOUND ?
            }
        }
        else
        {
            if (mLastAttack.getElapsedTime() > sf::seconds(1) && cf::distance(mTarget->getPosition(),getPosition()) < 50)
            {
                mTarget->inflige(20);
                mLastAttack.restart();
                // TODO : ANIMATION
                // TODO : PLAY SOUND ?
            }
        }

        if (mTarget->isDead()) // On l'a kill
        {
            // TODO : PLAY SOUND ?
            // TODO : EFFECT ?
            mTarget = nullptr;
        }

    }
    else
    {
        mMovingTime = sf::Time::Zero;
    }

    sf::IntRect tRect = sf::IntRect(0,0,61,121);
    tRect.top = mDirection * 121;
    tRect.left = static_cast<int>(mMovingTime.asSeconds() * 10) * 61;
    mSprite.setTextureRect(tRect);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    if (mWeapon != nullptr && (mDirection == Entity::N || mDirection == Entity::NW))
    {
        target.draw(*mWeapon,states);
    }

    target.draw(mSprite,states);

    if (mWeapon != nullptr && mDirection != Entity::N && mDirection != Entity::NW)
    {
        target.draw(*mWeapon,states);
    }

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
