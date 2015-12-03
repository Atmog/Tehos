#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <cmath>
#include <iostream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

#include "../Application/System.hpp"
#include "Game.hpp"
#include "Weapon.hpp"

class EntityManager;

class Entity : public sf::Drawable, public sf::Transformable
{
    public:
        enum Direction
        {
            E = 0,
            N = 1,
            W = 2,
            S = 3,
        };

        typedef std::shared_ptr<Entity> Ptr;

        Entity(EntityManager* manager = nullptr);

        virtual void update(sf::Time dt);
        virtual void handleEvent(sf::Event const& event);

        int getLife();
        int getMaxLife();
        int getSpeed();
        int getDamage();

        void setLife(int life);
        void setMaxLife(int maxLife);
        void setSpeed(int speed);
        void setDamage(int damage);

        void inflige(int damage);
        void heal(int heal);

        bool isDead();
        bool isAttacking();

        sf::FloatRect getBounds() const;

        void attack(Entity* entity);

        void updateDirection(sf::Vector2f goTo);
        void updateMovement(sf::Vector2f goTo, sf::Time dt);
        void updateAnimation(sf::Time dt);
        void updateWeapon(sf::Time dt);

        void stopMoving();

        void setWeaponType(Weapon::Type type);
        Weapon::Type getWeaponType();

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

    protected:
        EntityManager* mManager;

        sf::Sprite mSprite;

        int mLife;
        int mMaxLife;
        int mSpeed;
        int mDamage;

        Direction mDirection;
        sf::Time mMovingTime;

        Weapon mWeapon;
        sf::Time mCooldownTimer;
};

#endif // ENTITY_HPP
