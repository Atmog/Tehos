#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "../Lib/State.hpp"

#include "../Lib/Container.hpp"

#include "GameModeState.hpp"

class MenuState : public cf::State
{
    public:
        static std::string getID() { return "MenuState"; }

        typedef std::unique_ptr<MenuState> Ptr;

    public:
        MenuState(cf::StateManager& manager);

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render();

    protected:
        void toGameMode();

    protected:
        cf::Container mGUI;

};

#endif // INTROSTATE_HPP
