#ifndef FAKEENEMY_HPP
#define FAKEENEMY_HPP

#include "Entity.hpp"

class FakeEnemy : public Entity
{
    public:
        FakeEnemy();

        void update(sf::Time dt);

        void setPatrolPos(sf::Vector2f pos);

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

    private:
        sf::Vector2f mPatrolPos;
};

#endif // FAKEENEMY_HPP
