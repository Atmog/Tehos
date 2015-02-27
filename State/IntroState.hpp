#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "../Lib/State.hpp"

#include "MenuState.hpp"

class IntroState : public cf::State
{
    public:
        static std::string getID() { return "IntroState"; }

        typedef std::unique_ptr<IntroState> Ptr;

    public:
        IntroState(cf::StateManager& manager);

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render();

    protected:
        void toMenu();

};

#endif // INTROSTATE_HPP
