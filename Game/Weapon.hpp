#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "../Application/System.hpp"

class Weapon : public sf::Drawable, public sf::Transformable
{
    public:
        enum Type
        {
            Nothing = 0,
            Stick = 1,
            Baton = 2,
            Sword = 3,
            LightSaber = 4,
            // And will come soon :)
        };

        Weapon();
        Weapon(Type type);

        void setType(int type);
        void setType(Type type);
        Type getType();

        int getPrice();
        int getDamage();
        float getCooldown();

        void setRotation(float angle);
        void setPosition(sf::Vector2f position);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

    private:
        sf::Sprite mSprite;
        Type mType;
};

#endif // WEAPON_HPP
