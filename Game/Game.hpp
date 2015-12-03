#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Network/Http.hpp>

#include "../Application/System.hpp"
#include "../Application/SettingsParser.hpp"

#include "../Audio/Audio.hpp"

#include "EntityManager.hpp"

#include <SFML/Graphics/Image.hpp>

#include "Score.hpp"

class Game
{
    public:
        static void init();
        static void release();
        static Game& instance();

        static void update(sf::Time dt);
        static void handleEvent(sf::Event const& event);
        static void render();

        static void playMusic(std::string const& filename);
        static std::shared_ptr<sf::Sound> playSound(std::string const& filename);
        static int getMusicVolume();
        static int getSoundVolume();
        static void setMusicVolume(int volume);
        static void setSoundVolume(int volume);

        static bool getFullScreen();
        static bool setFullScreen(bool value);

        static EntityManager& getEntityManager();

        static void loadLangFile(std::string const& filename);
        static std::string getTextLang(std::string const& id);

        static int getBaseLife();
        static void attackBase(int damage);

        static int getMoney();
        static void earnMoney(int amount);
        static void spendMoney(int amount);

        static int getTime();

        static void addGame();

        static void startNewGame();

    protected:
        Game();

        static Game* Instance;

        MusicPlayer mMusics;
        SoundPlayer mSounds;
        app::SettingsParser mLang;
        app::SettingsParser mSettings;
        EntityManager mEntities;
        Score mScore;

        sf::Image mIcon;

        sf::Time mClock;
        sf::Time mSpawnTimer;
        int mWave;
        int mBaseLife;
        int mMoney;
};

#endif // GAME_HPP
