#include "Layer.hpp"

Layer::Layer(sf::Texture& texture, bool isometric)
{
    mTexture = &texture;
    mIsometric = isometric;
    update();
}

void Layer::setSize(sf::Vector2i size)
{
    mSize = size;
    update();
}

sf::Vector2i Layer::getSize() const
{
    return mSize;
}

void Layer::setTileSize(sf::Vector2i tileSize)
{
    mTileSize = tileSize;
    update();
}

sf::Vector2i Layer::getTileSize() const
{
    return mTileSize;
}

void Layer::setTexSize(sf::Vector2i texSize)
{
    mTexSize = texSize;
    update();
}

sf::Vector2i Layer::getTexSize() const
{
    return mTexSize;
}

void Layer::setTileId(sf::Vector2i pos, unsigned int id)
{
    if (pos.x < getSize().x && pos.y < getSize().y)
    {
        int tilesPerRow = 1;
        if (mTexture != nullptr)
            tilesPerRow = mTexture->getSize().x / getTexSize().x;

        sf::Vector2f tc = sf::Vector2f((id % tilesPerRow) * getTexSize().x,(id / tilesPerRow) * getTexSize().y);

        sf::Vertex* quad = &(mTiles[pos.y][pos.x*4]);
        quad[0].texCoords = tc;
        quad[1].texCoords = sf::Vector2f(tc.x + getTexSize().x, tc.y);
        quad[2].texCoords = sf::Vector2f(tc.x + getTexSize().x, tc.y + getTexSize().y);
        quad[3].texCoords = sf::Vector2f(tc.x, tc.y + getTexSize().y);
    }
}

unsigned int Layer::getTileId(sf::Vector2i pos)
{
    if (pos.x < getSize().x && pos.y < getSize().y)
    {
        sf::Vertex* quad = &(mTiles[pos.y][pos.x*4]);
        sf::Vector2f tc = quad[0].texCoords;
        sf::Vector2i c = sf::Vector2i(tc.x/getTexSize().x,tc.y/getTexSize().y);
        int tilesPerRow = 0;
        if (mTexture != nullptr)
            tilesPerRow = mTexture->getSize().x / getTexSize().x;
        return c.y * tilesPerRow + c.x;
    }
    return 0;
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i = 0; i < mTiles.size(); i++)
    {
        render(i,target,states);
    }
}

void Layer::render(unsigned int line, sf::RenderTarget& target, sf::RenderStates states) const
{
    if (line >= 0 && line < mTiles.size())
    {
        states.transform *= getTransform();
        if (mTexture != nullptr)
            states.texture = mTexture;
        target.draw(mTiles[line],states);
    }
}

sf::FloatRect Layer::getGlobalBounds() const
{
    sf::FloatRect rect;
    rect.left = getPosition().x;
    rect.top = getPosition().y;
    rect.width = mSize.x * mTileSize.x;
    rect.height = mSize.y * mTileSize.y;
    if (mIsometric)
        rect.height *= 0.5f;
    return rect;
}

void Layer::update()
{
    mTiles.clear();
    for (int y = 0; y < getSize().y; y++)
    {
        mTiles.push_back(sf::VertexArray(sf::Quads));
        mTiles.back().resize(getSize().x * 4);
        for (int x = 0; x < getSize().x; x++)
        {
            sf::Vertex* quad = &(mTiles.back()[x*4]);
            if (mIsometric)
            {
                if ((y%2)==0)
                {
                    quad[0].position = sf::Vector2f(x * getTexSize().x,y * getTileSize().y/2 - 32);
                    quad[1].position = sf::Vector2f((x+1) * getTexSize().x,y * getTileSize().y/2 - 32);
                    quad[2].position = sf::Vector2f((x+1) * getTexSize().x,y * getTileSize().y/2 + getTexSize().y - 32);
                    quad[3].position = sf::Vector2f(x * getTexSize().x,y * getTileSize().y/2 + getTexSize().y - 32);
                }
                else
                {
                    quad[0].position = sf::Vector2f((x+0.5) * getTexSize().x,y * getTileSize().y/2 - 32);
                    quad[1].position = sf::Vector2f((x+1.5) * getTexSize().x,y * getTileSize().y/2 - 32);
                    quad[2].position = sf::Vector2f((x+1.5) * getTexSize().x,y * getTileSize().y/2 + getTexSize().y - 32);
                    quad[3].position = sf::Vector2f((x+0.5) * getTexSize().x,y * getTileSize().y/2 + getTexSize().y - 32);
                }
            }
            else
            {
                quad[0].position = sf::Vector2f(x * getTexSize().x,y * getTileSize().y);
                quad[1].position = sf::Vector2f((x+1) * getTexSize().x,y * getTileSize().y);
                quad[2].position = sf::Vector2f((x+1) * getTexSize().x,(y+1) * getTileSize().y);
                quad[3].position = sf::Vector2f(x * getTexSize().x,(y+1) * getTileSize().y);
            }
        }
    }
}
