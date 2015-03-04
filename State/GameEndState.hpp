#ifndef GAMEENDSTATE_HPP
#define GAMEENDSTATE_HPP

#include "../Lib/State.hpp"

#include "../Lib/Container.hpp"

#include "MenuState.hpp"
#include "GameModeState.hpp"

#include "../Game/World.hpp"

class GameEndState : public cf::State
{
    public:
        static std::string getID() { return "GameEndState"; }

        typedef std::unique_ptr<GameEndState> Ptr;

    public:
        GameEndState(cf::StateManager& manager);

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render();

    protected:
        void toGameMode();
        void toMenu();

    protected:
        cf::Container mGUI;

};

#endif // GAMEENDSTATE_HPP
