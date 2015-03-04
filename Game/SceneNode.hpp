#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "CollisionShape.hpp"

class World;

class SceneNode : public sf::Drawable, public sf::Transformable
{
    public:
        typedef std::shared_ptr<SceneNode> Ptr;

        SceneNode();

        virtual void handleEvent(sf::Event const& event);
        virtual void update(sf::Time dt);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;

        void setWorld(World* world);

        virtual bool remove() const;

        sf::FloatRect getGlobalBounds() const;

    protected:
        World* mWorld;
        sf::Sprite mSprite;
        CollisionShape::Ptr mCollision;
};

#endif // SCENENODE_HPP
