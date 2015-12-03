#include "FakeEnemy.hpp"

FakeEnemy::FakeEnemy() : Entity(nullptr)
{
    mSprite.setTexture(app::System::getResources().getTexture("Skeleton"));

    mMovingTime = sf::Time::Zero;
    mSprite.setTextureRect(sf::IntRect(0,32 * static_cast<int>(mDirection),32,32));

    setOrigin(sf::Vector2f(mSprite.getGlobalBounds().width/2,mSprite.getGlobalBounds().height/2));

    int side = app::Math::random<int>(0,4);
    float value;
    switch (side)
    {
        case 0: value = app::Math::random<float>(0,600); setPosition(-16,value); break;
        case 1: value = app::Math::random<float>(0,800); setPosition(value,-16);break;
        case 2: value = app::Math::random<float>(0,600); setPosition(800+16,value);break;
        case 3: value = app::Math::random<float>(0,800); setPosition(value,600+16);break;
        default: app::System::getLog() << "Random size incorrect"; break;
    }

    mPatrolPos.x = app::Math::random<float>(-20.f,820.f);
    mPatrolPos.y = app::Math::random<float>(-20.f,620.f);
}

void FakeEnemy::update(sf::Time dt)
{
    if (app::Math::distance(mPatrolPos,getPosition()) < 30)
    {
        mPatrolPos.x = app::Math::random<float>(-100.f,900.f);
        mPatrolPos.y = app::Math::random<float>(-100.f,700.f);
    }
    else
    {
        updateDirection(mPatrolPos);
        updateMovement(mPatrolPos,dt);
        updateAnimation(dt);
    }
}

void FakeEnemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mSprite,states);
}

void FakeEnemy::setPatrolPos(sf::Vector2f pos)
{
    mPatrolPos = pos;
}
