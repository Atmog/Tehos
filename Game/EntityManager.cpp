#include "EntityManager.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "Soldier.hpp"

EntityManager::EntityManager()
{
    //ctor
}

void EntityManager::update(sf::Time dt)
{
    mEntities.erase(std::remove_if(mEntities.begin(), mEntities.end(),
    [](Entity::Ptr o) { return o->isDead(); }),
    mEntities.end());

    mEnemies.erase(std::remove_if(mEnemies.begin(), mEnemies.end(),
    [](Enemy::Ptr o) { return o->isDead(); }),
    mEnemies.end());

    mSoldiers.erase(std::remove_if(mSoldiers.begin(), mSoldiers.end(),
    [](Soldier::Ptr o) { return o->isDead(); }),
    mSoldiers.end());

    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        mEntities[i]->update(dt);
    }

    std::sort(mEntities.begin(), mEntities.end(),
    [](Entity::Ptr a, Entity::Ptr b) -> bool
    {
        return a->getPosition().y - a->getOrigin().y + a->getBounds().height < b->getPosition().y - b->getOrigin().y + b->getBounds().height;
    });
}

void EntityManager::handleEvent(sf::Event const& event)
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        mEntities[i]->handleEvent(event);
    }
}

void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        target.draw(*mEntities[i]);
    }
}

void EntityManager::spawnEnemy(int wave)
{
    if (mEntities.size() < 500)
    {
        Enemy::Ptr enemy = std::shared_ptr<Enemy>(new Enemy(this));

        enemy->setMaxLife(100+wave*wave);
        enemy->setLife(100+wave*wave);

        int side = app::Math::random<int>(0,3);
        float value;
        switch (side)
        {
            case 0: value = app::Math::random<float>(30,300); enemy->setPosition(-16,value); break;
            case 1: value = app::Math::random<float>(0,800); enemy->setPosition(value,-16);break;
            case 2: value = app::Math::random<float>(30,300); enemy->setPosition(800+16,value);break;
            default: app::System::getLog() << "Random size incorrect"; break;
        }

        mEntities.push_back(enemy);
        mEnemies.push_back(enemy);
    }
    else
    {
        app::System::getLog() << "There are too many Entities to spawn enemies !!";
    }
}

bool EntityManager::spawnSoldier(sf::Vector2f position, Weapon::Type type)
{
    if (!sf::FloatRect(300,450,200,150).contains(position) && mEntities.size() < 500)
    {
        Soldier::Ptr soldier = std::shared_ptr<Soldier>(new Soldier(this));
        soldier->setPosition(position);
        soldier->setWeaponType(type);
        mEntities.push_back(soldier);
        mSoldiers.push_back(soldier);
        Game::playSound("Assets/Sounds/spawn.wav");
        return true;
    }
    else if (mEntities.size() >= 500)
    {
        app::System::getLog() << "There are too many Entities to spawn soldiers !!";
    }
    return false;
}

Enemy::Ptr EntityManager::getNearestEnemy(Soldier* s)
{
    Enemy::Ptr e = nullptr;
    for (unsigned int i = 0; i < mEnemies.size(); i++)
    {
        if (e == nullptr || app::Math::distance(e->getPosition(),s->getPosition()) > app::Math::distance(mEnemies[i]->getPosition(),s->getPosition()))
        {
            e = mEnemies[i];
        }
    }
    return e;
}

Soldier::Ptr EntityManager::getNearestSoldier(Enemy* e)
{
    Soldier::Ptr s = nullptr;
    for (unsigned int i = 0; i < mSoldiers.size(); i++)
    {
        if (s == nullptr || app::Math::distance(e->getPosition(),s->getPosition()) > app::Math::distance(mSoldiers[i]->getPosition(),e->getPosition()))
        {
            s = mSoldiers[i];
        }
    }
    return s;
}

unsigned int EntityManager::getEnemyCount() const
{
    return mEnemies.size();
}

unsigned int EntityManager::getSoldierCount() const
{
    return mSoldiers.size();
}

bool EntityManager::giveWeaponToSoldier(sf::Vector2f position, Weapon::Type type)
{
    for (unsigned int i = 0; i < mSoldiers.size(); i++)
    {
        if (mSoldiers[i]->getBounds().contains(position) && static_cast<int>(mSoldiers[i]->getWeaponType()) < static_cast<int>(type))
        {
            mSoldiers[i]->setWeaponType(type);
            mSoldiers[i]->updateWeapon(sf::Time::Zero);
            return true;
        }
    }
    return false;
}

void EntityManager::reset()
{
    mEntities.clear();
    mEnemies.clear();
    mSoldiers.clear();
}
