#include "World.hpp"

World::World(World::GameMode mode)
: mMode(mode)
, mView(cf::Application::getWindow().getView())
, mFloor(cf::Application::getResources().getTexture("Assets/Textures/tileset.png"))
, mMid(cf::Application::getResources().getTexture("Assets/Textures/tileset.png"))
, mBaseBlue(nullptr)
, mBaseRed(nullptr)
{
    mBlueMoney = 500;
    mRedMoney = 500;

    mBaseBlue = std::make_shared<Base>(Targetable::Blue);
    addTargetable(mBaseBlue);
    mBaseRed = std::make_shared<Base>(Targetable::Red);
    addTargetable(mBaseRed);

    switch (mMode)
    {
        case World::GameMode::Survival: loadSurvival(); break;
        case World::GameMode::DeathMatch: loadDeathMatch(); break;
        case World::GameMode::Domination: loadDomination(); break;
    }

    loadMap();
    loadCollisionManager();
}

void World::handleEvent(sf::Event const& event)
{
    // Check HUD
    HUD::Action actionHUD = mHUD.handleEvent(event);
    switch (actionHUD)
    {
        /*case :
        {

        } break;

        case :
        {

        } break;*/

        default:
        {
            for (unsigned int i = 0; i < mSceneNodes.size(); i++)
            {
                mSceneNodes[i]->handleEvent(event);
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mp = cf::Application::getWindow().getMousePositionView(mView);
                if (mBlueMoney >= 100 && cf::distance(mp,mBaseBlue->getPosition()) <= mBaseBlue->getSpawnRadius())
                {
                    mBlueMoney -= 100;
                    Entity::Ptr e = std::make_shared<Entity>(Targetable::Blue);
                    e->setPosition(mp);
                    addTargetable(e);
                }
                if (cf::distance(mp,mBaseBlue->getPosition()) > mBaseBlue->getSpawnRadius())
                {
                    mRenderBaseZone.restart();
                }
                if (mBlueMoney < 100)
                {
                }
            }
        }
    }

    // Zoom
    if (event.type == sf::Event::MouseWheelMoved)
    {
        if (event.mouseWheel.delta < 1)
            mView.zoom(1.2f);
        else
            mView.zoom(0.8f);
    }
}

void World::update(sf::Time dt)
{
    // Update Entities
    for (unsigned int i = 0; i < mSceneNodes.size(); i++)
    {
        mSceneNodes[i]->update(dt);
    }

    // View movement
    sf::Vector2f movement;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        movement.y--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        movement.x--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y++;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x++;
    mView.move(movement * dt.asSeconds() * 300.f);

    // Remove dead entities
    mSceneNodes.erase(std::remove_if(mSceneNodes.begin(), mSceneNodes.end(),
    [](SceneNode::Ptr o) { return o->remove(); }), mSceneNodes.end());
    mTargetables.erase(std::remove_if(mTargetables.begin(), mTargetables.end(),
    [](Targetable::Ptr o) { return o->remove(); }), mTargetables.end());
    // TODO : EFFECT ?

    mMoneyTime += dt;
    if (mMoneyTime >= sf::seconds(0.1))
    {
        mMoneyTime = sf::Time::Zero;
        mBlueMoney++;
        mRedMoney++;
    }

    handleAI(dt);
}

void World::render()
{
    // Fix World View
    cf::Application::getWindow().setView(mView);

    // Render Floor
    cf::Application::getWindow().draw(mFloor);



    if (cf::distance(mBaseBlue->getPosition(),cf::Application::getWindow().getMousePositionMap()) < 75
    || (mRenderBaseZone.getElapsedTime() < sf::seconds(0.5)))
    {
        mBaseBlue->drawSpawnZone(cf::Application::getWindow());
    }

    if (cf::distance(mBaseRed->getPosition(),cf::Application::getWindow().getMousePositionMap()) < 75)
    {
        mBaseRed->drawSpawnZone(cf::Application::getWindow());
    }

    bool tB = false;
    bool tR = false;
    for (unsigned int i = 0; i < mSceneNodes.size(); i++)
    {
        if (mBaseBlue->getGlobalBounds().intersects(mSceneNodes[i]->getGlobalBounds()) && mBaseBlue->getPosition() != mSceneNodes[i]->getPosition())
            tB = true;
        if (mBaseRed->getGlobalBounds().intersects(mSceneNodes[i]->getGlobalBounds()) && mBaseRed->getPosition() != mSceneNodes[i]->getPosition())
            tR = true;
    }
    mBaseBlue->transparence(tB);
    mBaseRed->transparence(tR);

    // Sort SceneNodes
    std::sort(mSceneNodes.begin(), mSceneNodes.end(),[](SceneNode::Ptr a, SceneNode::Ptr b) -> bool { return a->getPosition().y < b->getPosition().y; });
    // Render SceneNodes

    for (int i = 0; i < mMid.getSize().y; i++)
    {
        mMid.render(i,cf::Application::getWindow());
    }
    for (unsigned int i = 0; i < mSceneNodes.size(); i++)
    {
        cf::Application::getWindow().draw(*mSceneNodes[i]);
    }

    cf::Application::getWindow().draw(mCollisions);

    // Set Normal View
    cf::Application::getWindow().setDefaultView();

    // Draw HUD
    cf::Application::getWindow().draw(mHUD);
}

void World::addMoney(Targetable::Team team, int amount)
{
    if (team == Targetable::Team::Blue)
    {
        mBlueMoney += amount;
    }
    else if (team == Targetable::Team::Red)
    {
        mRedMoney += amount;
    }
}

Targetable::Ptr World::findNearestTarget(Targetable* e)
{
    Targetable::Team team = e->getTeam();
    Targetable::Ptr target = nullptr;
    float actualDistance = 999999;
    float maxDistance = 1000;
    for (unsigned int i = 0; i < mTargetables.size(); i++)
    {
        float d = cf::distance(mTargetables[i]->getPosition(),e->getPosition());
        if (d < actualDistance
        && d < maxDistance
        && mTargetables[i]->getTeam() != team
        && mTargetables[i].get() != e
        && mTargetables[i]->isAlive())
        {
            target = mTargetables[i];
            actualDistance = cf::distance(target->getPosition(),e->getPosition());
        }
    }
    return target;
}

CollisionManager& World::getCollisionManager()
{
    return mCollisions;
}

World::GameEnd World::getEnd() const
{
    if (!mBaseBlue->isDead() && !mBaseRed->isDead())
        return GameEnd::None;

    if (mBaseBlue->isDead() || mBaseRed->isDead())
    {
        // Save data
    }
    if (mBaseBlue->isDead())
    {
        // Save data
        return GameEnd::Loose;
    }
    else if (mBaseRed->isDead())
    {
        // Save data
        return GameEnd::Win;
    }

    return GameEnd::None;
}

World::GameMode World::getMode() const
{
    return mMode;
}

void World::addTargetable(Targetable::Ptr e)
{
    e->setWorld(this);
    mSceneNodes.push_back(e);
    mTargetables.push_back(e);

    if (e->getTeam() == Targetable::Red)
        mRedSpawned++;
    if (e->getTeam() == Targetable::Blue)
        mBlueSpawned++;
}

void World::loadSurvival()
{
    mBaseBlue->setPosition(520,930);
    mBaseRed->setPosition(-11111,-11111);
}

void World::loadDeathMatch()
{
}

void World::loadDomination()
{
}

void World::loadMap()
{
    sf::Vector2i mapSize = sf::Vector2i(16,64);
    sf::Vector2i tileSize = sf::Vector2i(64,32);
    sf::Vector2i texSize = sf::Vector2i(64,64);

    mFloor.setSize(mapSize);
    mFloor.setTileSize(tileSize);
    mFloor.setTexSize(texSize);
    for (int x = 0; x < mapSize.x; x++)
    {
        for (int y = 0; y < mapSize.y; y++)
        {
            mFloor.setTileId(sf::Vector2i(x,y),1);
        }
    }

    mMid.setSize(mapSize);
    mMid.setTileSize(tileSize);
    mMid.setTexSize(texSize);
    for (int x = 0; x < mapSize.x; x++)
    {
        mMid.setTileId(sf::Vector2i(x,0),2);
        mMid.setTileId(sf::Vector2i(x,mapSize.y-1),2);
    }
    for (int y = 0; y < mapSize.y; y+=2)
    {
        mMid.setTileId(sf::Vector2i(0,y),2);
        mMid.setTileId(sf::Vector2i(mapSize.x-1,y+1),2);
    }
    for (int x = 0; x < mapSize.x; x++)
    {
        for (int y = 0; y < mapSize.y; y++)
        {
            if (cf::random(0,100) > 98)
            {
                mMid.setTileId(sf::Vector2i(x,y),2);
            }
        }
    }
}

void World::loadCollisionManager()
{
    CollisionShape shape;
    shape.setPointCount(4);
    shape.setPoint(0,sf::Vector2f(0,-mMid.getTileSize().y/2));
    shape.setPoint(1,sf::Vector2f(mMid.getTileSize().x/2,0));
    shape.setPoint(2,sf::Vector2f(0,mMid.getTileSize().y/2));
    shape.setPoint(3,sf::Vector2f(-mMid.getTileSize().x/2,0));
    for (int x = 0; x < mMid.getSize().x; x++)
    {
        for (int y = 0; y < mMid.getSize().y; y++)
        {
            if (mMid.getTileId(sf::Vector2i(x,y)) == 2)
            {
                if (y%2 == 0)
                    shape.setPosition(sf::Vector2f((x+0.5)*mMid.getTileSize().x,(y+1)*mMid.getTileSize().y/2));
                else
                    shape.setPosition(sf::Vector2f((x+1)*mMid.getTileSize().x,(y+1)*mMid.getTileSize().y/2));

                mCollisions.add(std::make_shared<CollisionShape>(shape));
            }
        }
    }
}

void World::handleAI(sf::Time dt)
{
    if (mRedMoney >= 100 && mClock.getElapsedTime() >= sf::seconds(10))
    {
        mRedMoney -= 100;
        Entity::Ptr e = std::make_shared<Entity>(Targetable::Red);
        e->setPosition(sf::Vector2f(cf::randomDev(520.f,300.f),cf::randomDev(200.f,20.f)));
        addTargetable(e);
    }

    if (mMode == World::GameMode::Survival)
    {
        // Money Bonus Over Elapsed Time
    }
}
