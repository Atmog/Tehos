#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include "Entity.hpp"

class Enemy;

class Soldier : public Entity
{
    public:
        typedef std::shared_ptr<Soldier> Ptr;

        friend class EntityManager;

        Soldier(EntityManager* manager);

        void update(sf::Time dt);
        void handleEvent(sf::Event const& event);

        std::shared_ptr<Enemy> getTarget();
        void setTarget(std::shared_ptr<Enemy> e);

        bool hasTarget();

        void attack(Enemy* enemy);

        void stopMoving();

    private:
        std::shared_ptr<Enemy> mTarget;
        sf::Vector2f mPatrolPos;
};

#endif // SOLDIER_HPP
