#ifndef HELP_HPP
#define HELP_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include "../Application/System.hpp"
#include "../Application/State.hpp"

#include "../SimpleGui/Container.hpp"
#include "../SimpleGui/Button.hpp"

#include "Menu.hpp"

class Help : public app::State
{
    public:
        static std::string getID();
        typedef std::unique_ptr<Help> Ptr;

    public:
        Help(app::StateManager& manager);

        void load();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render();

    private:
        SGUI::Container mGUI;
        sf::RectangleShape mShape;
};

#endif // HELP_HPP
