#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "../Lib/Application.hpp"

class Weapon : public sf::Drawable, public sf::Transformable
{
    public:
        Weapon();

        void setForce(int force);
        int getForce() const;

        void setRange(float range);
        float getRange() const;

        std::string getName() const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        sf::Sprite mSprite;
        int mForce;
        float mRange;
};

#endif // WEAPON_HPP
