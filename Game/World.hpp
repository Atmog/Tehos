#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "../Lib/Application.hpp"
#include "../Lib/Vector.hpp"
#include "../Lib/Random.hpp"

#include "SceneNode.hpp"
#include "Targetable.hpp"
#include "Entity.hpp"
#include "Layer.hpp"
#include "Base.hpp"
#include "CollisionManager.hpp"
#include "CollisionShape.hpp"

class World
{
    public:
        enum GameMode
        {
            Survival = 0,
            DeathMatch,
            Domination,
        };

        World(GameMode mode);

        void handleEvent(sf::Event const& event);
        void update(sf::Time dt);
        void render();

        void addTargetable(Targetable::Ptr t);

        sf::Time getGameTime() const;

        Targetable::Ptr findNearestTarget(Targetable* e);

        CollisionManager& getCollisionManager();

    protected:
        void loadSurvival();
        void loadDeathMatch();
        void loadDomination();

        void loose();
        void win();

        void loadMap();
        void loadCollisionManager();

    protected:
        GameMode mMode;
        sf::View mView;
        sf::Clock mClock;
        std::vector<SceneNode::Ptr> mSceneNodes;
        std::vector<Targetable::Ptr> mTargetables;
        Layer mFloor;
        Layer mMid;
        CollisionManager mCollisions;
        Base::Ptr mBaseBlue;
        Base::Ptr mBaseRed;

        unsigned int mBlueSpawned;
        unsigned int mRedSpawned;
};

#endif // WORLD_HPP
