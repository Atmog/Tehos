#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

class Soldier;

class Enemy : public Entity
{
    public:
        typedef std::shared_ptr<Enemy> Ptr;

        friend class EntityManager;

        Enemy(EntityManager* manager);

        void update(sf::Time dt);
        void handleEvent(sf::Event const& event);

        std::shared_ptr<Soldier> getTarget();
        void setTarget(std::shared_ptr<Soldier> e);

        bool hasTarget();

        bool hasGiveMoney();
        void giveMoney();

        void stopMoving();

    private:
        std::shared_ptr<Soldier> mTarget;
        bool mHasGiveMoney;

};

#endif // ENEMY_HPP
