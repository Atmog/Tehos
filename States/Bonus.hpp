#ifndef BONUS_HPP
#define BONUS_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include "../Application/System.hpp"
#include "../Application/State.hpp"

#include "../SimpleGui/Container.hpp"
#include "../SimpleGui/Button.hpp"

#include "Menu.hpp"

class Bonus : public app::State
{
    public:
        static std::string getID();
        typedef std::unique_ptr<Bonus> Ptr;

    public:
        Bonus(app::StateManager& manager);

        void load();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render();

    private:
        SGUI::Container mGUI;
};

#endif // BONUS_HPP
