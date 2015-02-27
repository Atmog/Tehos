#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Lib/State.hpp"

#include "MenuState.hpp"

class GameState : public cf::State
{
    public:
        static std::string getID() { return "GameState"; }

        typedef std::unique_ptr<GameState> Ptr;

    public:
        GameState(cf::StateManager& manager);

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render();

    protected:
        void toMenu();

};

#endif // GAMESTATE_HPP
