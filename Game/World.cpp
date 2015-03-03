#include "World.hpp"

World::World(World::GameMode mode)
: mMode(mode)
, mView(cf::Application::getWindow().getView())
, mFloor(cf::Application::getResources().getTexture("Assets/Textures/tileset.png"))
, mMid(cf::Application::getResources().getTexture("Assets/Textures/tileset.png"))
, mBaseBlue(nullptr)
, mBaseRed(nullptr)
{
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
    for (unsigned int i = 0; i < mSceneNodes.size(); i++)
    {
        mSceneNodes[i]->handleEvent(event);
    }

    if (event.type == sf::Event::MouseWheelMoved)
    {
        if (event.mouseWheel.delta >= 1)
            mView.zoom(1.2f);
        else
            mView.zoom(0.8f);
    }
}

void World::update(sf::Time dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        return;
    }



    for (unsigned int i = 0; i < mSceneNodes.size(); i++)
    {
        mSceneNodes[i]->update(dt);
    }

    sf::Vector2f movement;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        movement.y--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        movement.x--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y++;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x++;
    mView.move(movement * dt.asSeconds() * 180.f);

    // Remove dead entities
    mSceneNodes.erase(std::remove_if(mSceneNodes.begin(), mSceneNodes.end(),
    [](SceneNode::Ptr o) { return o->remove(); }), mSceneNodes.end());
    mTargetables.erase(std::remove_if(mTargetables.begin(), mTargetables.end(),
    [](Targetable::Ptr o) { return o->remove(); }), mTargetables.end());
    // TODO : EFFECT ?


    // Fin de la game
    if (mBaseBlue->isDead())
        loose();
    if (mBaseRed->isDead())
        win();
}

void World::render()
{
    cf::Application::getWindow().setView(mView);

    // Render Floor
    cf::Application::getWindow().draw(mFloor);

    // Sort SceneNodes
    std::sort(mSceneNodes.begin(), mSceneNodes.end(),[](SceneNode::Ptr a, SceneNode::Ptr b) -> bool { return a->getPosition().y < b->getPosition().y; });
    // Render SceneNodes

    unsigned int renderedNodes = 0;
    for (unsigned int i = 0; i < 64; i++)
    {
        mMid.render(i,cf::Application::getWindow());

        while (mSceneNodes[0]->getPosition().y >= (i+1) * 16 && mSceneNodes[0]->getPosition().y < (i+2) * 16 && renderedNodes < mSceneNodes.size())
        {
            cf::Application::getWindow().draw(*mSceneNodes[0]);
            mSceneNodes.push_back(mSceneNodes[0]);
            mSceneNodes.erase(mSceneNodes.begin());
            renderedNodes++;
        }
    }

    for (unsigned int i = 0; i < mSceneNodes.size(); i++)
    {
        cf::Application::getWindow().draw(*mSceneNodes[i]);
    }

    // Render UpperLevel

    cf::Application::getWindow().draw(mCollisions);

    cf::Application::getWindow().setDefaultView();

    //Render HUD
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

sf::Time World::getGameTime() const
{
    return mClock.getElapsedTime();
}

Targetable::Ptr World::findNearestTarget(Targetable* e)
{
    Targetable::Team team = e->getTeam();
    Targetable::Ptr target = nullptr;
    float minDistance = 999999;
    for (unsigned int i = 0; i < mTargetables.size(); i++)
    {
        if (cf::distance(mTargetables[i]->getPosition(),e->getPosition()) < minDistance
        && mTargetables[i]->getTeam() != team
        && mTargetables[i].get() != e
        && mTargetables[i]->isAlive())
        {
            target = mTargetables[i];
            minDistance = cf::distance(target->getPosition(),e->getPosition());
        }
    }
    return target;
}

CollisionManager& World::getCollisionManager()
{
    return mCollisions;
}

void World::loadSurvival()
{
    mBaseBlue->setPosition(1500,1500);
    mBaseRed->setPosition(2000,2000);

    Entity::Ptr e = std::make_shared<Entity>(Targetable::Blue);
    e->setPosition(200,300);
    e->setMaxLife(200);
    e->setLife(200);
    addTargetable(e);

    Entity::Ptr e1 = std::make_shared<Entity>(Targetable::Blue);
    e1->setPosition(500,300);
    e1->setMaxLife(200);
    e1->setLife(200);
    addTargetable(e1);

    Entity::Ptr e4 = std::make_shared<Entity>(Targetable::Blue);
    e4->setPosition(400,300);
    e4->setMaxLife(200);
    e4->setLife(200);
    addTargetable(e4);

    Entity::Ptr e2 = std::make_shared<Entity>(Targetable::Red);
    e2->setPosition(500,700);
    e2->setMaxLife(200);
    e2->setLife(200);
    addTargetable(e2);

    Entity::Ptr e3 = std::make_shared<Entity>(Targetable::Red);
    e3->setPosition(600,700);
    e3->setMaxLife(200);
    e3->setLife(200);
    addTargetable(e3);
}

void World::loadDeathMatch()
{
}

void World::loadDomination()
{
}

void World::loose()
{

}

void World::win()
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
        mMid.setTileId(sf::Vector2i(x,63),2);
    }
    for (int y = 0; y < mapSize.y; y+=2)
    {
        mMid.setTileId(sf::Vector2i(0,y),2);
        mMid.setTileId(sf::Vector2i(15,y+1),2);
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
