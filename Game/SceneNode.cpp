#include "SceneNode.hpp"
#include "World.hpp"

SceneNode::SceneNode()
{
    mCollision = std::make_shared<CollisionShape>();
}

void SceneNode::handleEvent(sf::Event const& event)
{
}

void SceneNode::update(sf::Time dt)
{
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite,states);
}

void SceneNode::setWorld(World* world)
{
    mWorld = world;
}

bool SceneNode::remove() const
{
    return false;
}
