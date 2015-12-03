#include "Enemy.hpp"
#include "Soldier.hpp"

Enemy::Enemy(EntityManager* manager) : Entity(manager)
{
    mSprite.setTexture(app::System::getResources().getTexture("Skeleton"));

    stopMoving();

    setOrigin(sf::Vector2f(mSprite.getGlobalBounds().width/2,mSprite.getGlobalBounds().height/2));

    mHasGiveMoney = false;

    mWeapon.setType(Weapon::Nothing);
}

void Enemy::update(sf::Time dt)
{
    updateWeapon(dt);

    mTarget = mManager->getNearestSoldier(this);
    if (hasTarget())
    {
        if (app::Math::distance(mTarget->getPosition(),getPosition()) > app::Math::distance(sf::Vector2f(400,490),getPosition()))
        {
            mTarget = nullptr;
        }
    }


    if (!hasTarget())
    {
        if (getBounds().intersects(sf::FloatRect(315,495,170,105)))
        {
            stopMoving();
            if (!isAttacking())
            {
                Game::attackBase(mDamage + mWeapon.getDamage());
                mCooldownTimer = sf::seconds(0);
            }
        }
        else
        {
            updateDirection(sf::Vector2f(400,520));
            updateMovement(sf::Vector2f(400,520),dt);
            updateAnimation(dt);
        }
    }
    if (hasTarget() && mTarget->isDead())
    {
        mTarget = nullptr;
    }
    if (hasTarget())
    {
        if (app::Math::distance(getPosition(),mTarget->getPosition()) >= 20)
        {
            updateDirection(mTarget->getPosition());
            updateMovement(mTarget->getPosition(),dt);
            updateAnimation(dt);
        }
        else
        {
            stopMoving();
            attack(mTarget.get());
            if (mTarget->isDead())
            {
                Weapon::Type soldierWeapon = mTarget->getWeaponType();
                if (static_cast<int>(soldierWeapon) > static_cast<int>(mWeapon.getType()))
                {
                    setWeaponType(soldierWeapon);
                    mTarget->setWeaponType(Weapon::Nothing);
                }
                mTarget = nullptr;
            }
        }
    }
}

void Enemy::handleEvent(sf::Event const& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right && getBounds().contains(app::System::getWindow().getMousePosition()))
    {
        // TODO : Adjust PLAYER damage
        inflige(10);
        if (isDead())
        {
            giveMoney();
        }
    }
}

std::shared_ptr<Soldier> Enemy::getTarget()
{
    return mTarget;
}

void Enemy::setTarget(std::shared_ptr<Soldier> e)
{
    mTarget = e;
}

bool Enemy::hasTarget()
{
    return mTarget != nullptr;
}

bool Enemy::hasGiveMoney()
{
    return mHasGiveMoney;
}

void Enemy::giveMoney()
{
    if (!hasGiveMoney())
    {
        Game::earnMoney(100);
        mHasGiveMoney = true;
    }
}

void Enemy::stopMoving()
{
    mMovingTime = sf::Time::Zero;
    mSprite.setTextureRect(sf::IntRect(0,32 * static_cast<int>(mDirection),32,32));
}
