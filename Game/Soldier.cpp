#include "Soldier.hpp"
#include "Enemy.hpp"

Soldier::Soldier(EntityManager* manager) : Entity(manager)
{
    mSprite.setTexture(app::System::getResources().getTexture("Soldier"));

    stopMoving();

    setOrigin(sf::Vector2f(mSprite.getGlobalBounds().width/2,mSprite.getGlobalBounds().height/2));

    mPatrolPos = sf::Vector2f(400,300);

    mWeapon.setType(Weapon::Nothing);
}

void Soldier::update(sf::Time dt)
{
    updateWeapon(dt);

    if (!hasTarget())
    {
        mTarget = mManager->getNearestEnemy(this);
        if (getBounds().intersects(sf::FloatRect(320,495,160,105)))
        {
            //
        }
        else
        {
            mTarget = mManager->getNearestEnemy(this);
            if (!hasTarget())
            {
                if (app::Math::distance(mPatrolPos,getPosition()) > 30)
                {
                    updateDirection(mPatrolPos);
                    updateMovement(mPatrolPos,dt);
                    updateAnimation(dt);
                }
                else
                {
                    mPatrolPos.x = app::Math::random<float>(0.f,800.f);
                    mPatrolPos.y = app::Math::random<float>(0.f,420.f);
                }
            }
        }
    }
    if (hasTarget() && mTarget->isDead())
    {
        mTarget = nullptr;
        mPatrolPos.x = app::Math::random<float>(0.f,800.f);
        mPatrolPos.y = app::Math::random<float>(0.f,420.f);
    }
    if (hasTarget())
    {
        if (getBounds().intersects(sf::FloatRect(320,495,160,105)))
        {
            // try to move
        }
        else if (app::Math::distance(getPosition(),mTarget->getPosition()) >= 20)
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
                mTarget = nullptr;
                mPatrolPos.x = app::Math::random<float>(0.f,800.f);
                mPatrolPos.y = app::Math::random<float>(0.f,420.f);
            }
        }
    }
}

void Soldier::handleEvent(sf::Event const& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right && getBounds().contains(app::System::getWindow().getMousePosition()))
    {
        // TODO : Adjust PLAYER healing
        heal(5);
    }
}

std::shared_ptr<Enemy> Soldier::getTarget()
{
    return mTarget;
}

void Soldier::setTarget(std::shared_ptr<Enemy> e)
{
    mTarget = e;
}

bool Soldier::hasTarget()
{
    return mTarget != nullptr;
}

void Soldier::attack(Enemy* enemy)
{
    if (!isAttacking())
    {
        if (enemy != nullptr)
        {

            enemy->inflige(mDamage + mWeapon.getDamage());
            if (enemy->isDead())
            {
                enemy->giveMoney();
            }

            mCooldownTimer = sf::seconds(0);

        }
    }
}

void Soldier::stopMoving()
{
    mMovingTime = sf::Time::Zero;
    mSprite.setTextureRect(sf::IntRect(0,46 * static_cast<int>(mDirection),27,46));
}

