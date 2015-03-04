#include "CollisionManager.hpp"

CollisionManager::CollisionManager()
{
}

void CollisionManager::add(CollisionShape::Ptr shape)
{
    mCollisions.push_back(shape);
}

void CollisionManager::remove(CollisionShape::Ptr shape)
{
    for (auto itr = mCollisions.begin(); itr != mCollisions.end(); itr++)
    {
        if ((*itr) == shape)
        {
            mCollisions.erase(itr);
        }
    }
}

bool CollisionManager::intersect(CollisionShape::Ptr shape)
{
    if (shape == nullptr)
        return false;
    for (unsigned int i = 0; i < mCollisions.size(); i++)
        if (mCollisions[i] != nullptr)
            if (mCollisions[i]->intersect(shape))
                return true;
    return false;
}

bool CollisionManager::contains(sf::Vector2f point)
{
    for (unsigned int i = 0; i < mCollisions.size(); i++)
    {
        if (mCollisions[i] != nullptr)
        {
            if (mCollisions[i]->contains(point))
            {
                return true;
            }
        }
    }
    return false;
}

void CollisionManager::movementCorrection(CollisionShape::Ptr shape, sf::Vector2f& movement)
{
    if (shape == nullptr)
        return;
    float l = cf::length(movement);
    sf::Vector2f initialPos = shape->getPosition();
    shape->setPosition(initialPos + movement);
    for (unsigned int i = 0; i < mCollisions.size(); i++)
        if (mCollisions[i] != nullptr)
            if (mCollisions[i]->intersect(shape))
            {
                sf::Vector2f mvt = mCollisions[i]->getPosition() - initialPos;
                cf::normalize(mvt);
                movement = -mvt * l * 0.5f;
                shape->setPosition(initialPos + movement);
            }
}

void CollisionManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i = 0; i < mCollisions.size(); i++)
    {
        target.draw(*mCollisions[i]);
    }
}
