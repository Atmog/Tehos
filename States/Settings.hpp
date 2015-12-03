#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "../Application/System.hpp"
#include "../Application/State.hpp"

#include "../SimpleGui/Container.hpp"
#include "../SimpleGui/Button.hpp"

#include "Menu.hpp"

class Settings : public app::State
{
    public:
        static std::string getID();
        typedef std::unique_ptr<Settings> Ptr;

    public:
        Settings(app::StateManager& manager);

        void load();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render();

    private:
        SGUI::Container mGUI;
        SGUI::Button::Ptr mRadioFr;
        SGUI::Button::Ptr mRadioEn;
        SGUI::Slider::Ptr mMusic;
        SGUI::Slider::Ptr mSound;
        int mMusicVol;
        int mSoundVol;
};

#endif // SETTINGS_HPP
