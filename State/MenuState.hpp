#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "../Lib/State.hpp"

#include "GameState.hpp"

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
        void toGame();

};

#endif // INTROSTATE_HPP
