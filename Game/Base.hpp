#ifndef BASE_HPP
#define BASE_HPP

#include "Targetable.hpp"

#include "../Lib/Application.hpp"
#include "../Lib/Vector.hpp"

#include <SFML/Graphics/CircleShape.hpp>

class Base : public Targetable
{
    public:
        typedef std::shared_ptr<Base> Ptr;

        Base(Targetable::Team team);

        void drawSpawnZone(sf::RenderTarget& target) const;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void setSpawnRadius(float radius);
        float getSpawnRadius() const;

        void transparence(bool transparent);

    protected:
        bool mTransparent;
        float mSpawnRadius;
};

#endif // BASE_HPP
