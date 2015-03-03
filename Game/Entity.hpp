#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Targetable.hpp"
#include "Weapon.hpp"

#include "../Lib/Application.hpp"
#include "../Lib/Trigonometry.hpp"

class Entity : public Targetable
{
    public:
        typedef std::shared_ptr<Entity> Ptr;

        enum Direction
        {
            E = 0,
            NE,
            N,
            NW,
            W,
            SW,
            S,
            SE,
        };

        Entity(Targetable::Team team);

        void setWeapon(Weapon* weapon);
        Weapon* getWeapon() const;

        void handleEvent(sf::Event const& event);
        void update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        Targetable::Ptr mTarget;
        float mSpeed;
        sf::Time mMovingTime;
        sf::Clock mLastAttack;
        Entity::Direction mDirection;
        Weapon* mWeapon;
};

#endif // ENTITY_HPP
