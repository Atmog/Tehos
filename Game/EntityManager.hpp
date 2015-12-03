#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <vector>
#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "../Application/Math.hpp"

#include "Weapon.hpp"

class Entity;
class Enemy;
class Soldier;

class EntityManager : public sf::Drawable
{
    public:
        EntityManager();

        void update(sf::Time dt);
        void handleEvent(sf::Event const& event);

        void spawnEnemy(int wave);
        bool spawnSoldier(sf::Vector2f position,Weapon::Type type);

        std::shared_ptr<Enemy> getNearestEnemy(Soldier* s);
        std::shared_ptr<Soldier> getNearestSoldier(Enemy* e);

        unsigned int getEnemyCount() const;
        unsigned int getSoldierCount() const;

        bool giveWeaponToSoldier(sf::Vector2f position, Weapon::Type type);

        void reset();

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

    private:
        std::vector<std::shared_ptr<Entity>> mEntities;
        std::vector<std::shared_ptr<Enemy>> mEnemies;
        std::vector<std::shared_ptr<Soldier>> mSoldiers;
};

#endif // ENTITYMANAGER_HPP
