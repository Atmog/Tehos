#ifndef PAUSE_HPP
#define PAUSE_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../Application/System.hpp"
#include "../Application/State.hpp"

#include "../SimpleGui/Container.hpp"
#include "../SimpleGui/Button.hpp"

#include "GameState.hpp"
#include "Menu.hpp"

class Pause : public app::State
{
    public:
        static std::string getID();
        typedef std::unique_ptr<Pause> Ptr;

    public:
        Pause(app::StateManager& manager);

        void load();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render();

        void switchToGame();
        void switchToMenu();

    private:
        SGUI::Container mGUI;
        sf::RectangleShape mShape;
};


#endif // PAUSE_HPP
