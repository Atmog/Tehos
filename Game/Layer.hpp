#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

class Layer : public sf::Drawable, public sf::Transformable
{
    public:
        Layer(sf::Texture& texture, bool isometric = true);

        void setSize(sf::Vector2i size);
        sf::Vector2i getSize() const;

        void setTileSize(sf::Vector2i tileSize);
        sf::Vector2i getTileSize() const;

        void setTexSize(sf::Vector2i teSize);
        sf::Vector2i getTexSize() const;

        void setTileId(sf::Vector2i pos, unsigned int id);
        unsigned int getTileId(sf::Vector2i pos);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void render(unsigned int line, sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

        sf::FloatRect getGlobalBounds() const;

    protected:
        void update();

    protected:
        bool mIsometric;
        sf::Texture* mTexture;
        std::vector<sf::VertexArray> mTiles;
        sf::Vector2i mSize;
        sf::Vector2i mTileSize;
        sf::Vector2i mTexSize;
};

#endif // LAYER_HPP
