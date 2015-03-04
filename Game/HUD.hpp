#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "../Lib/Container.hpp"
#include "../Lib/Application.hpp"

class HUD : public sf::Drawable
{
    public:
        HUD();

        enum Action
        {
            None = 0,

        };

        Action handleEvent(sf::Event const& event);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        cf::Container mGUI;
};

#endif // HUD_HPP
