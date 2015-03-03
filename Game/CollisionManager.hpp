#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "CollisionShape.hpp"
#include "../Lib/Trigonometry.hpp"
#include "../Lib/Vector.hpp"

class CollisionManager : public sf::Drawable
{
    public:
        CollisionManager();

        void add(CollisionShape::Ptr shape);
        void remove(CollisionShape::Ptr shape);

        bool intersect(CollisionShape::Ptr shape);
        bool contains(sf::Vector2f point);

        void movementCorrection(CollisionShape::Ptr shape, sf::Vector2f& movement);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        std::vector<CollisionShape::Ptr> mCollisions;
};

#endif // COLLISIONMANAGER_HPP
