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
#include "HUD.hpp"

class World
{
    public:
        enum GameMode
        {
            Survival = 0,
            DeathMatch,
            Domination,
        };

        enum GameEnd
        {
            None = 0,
            Win,
            Loose,
        };

        World(GameMode mode);

        void handleEvent(sf::Event const& event);
        void update(sf::Time dt);
        void render();

        Targetable::Ptr findNearestTarget(Targetable* e);

        CollisionManager& getCollisionManager();

        GameEnd getEnd() const;
        GameMode getMode() const;

        void addMoney(Targetable::Team team, int amount);

    protected:
        void addTargetable(Targetable::Ptr t);

        void loadSurvival();
        void loadDeathMatch();
        void loadDomination();

        void loadMap();
        void loadCollisionManager();

        void handleAI(sf::Time dt);

    protected:
        HUD mHUD;
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
        sf::Clock mRenderBaseZone;
        sf::Time mMoneyTime;


        int mBlueMoney;
        int mRedMoney;

        unsigned int mBlueSpawned;
        unsigned int mRedSpawned;
};

#endif // WORLD_HPP
