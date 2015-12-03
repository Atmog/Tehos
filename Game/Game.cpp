#include "Game.hpp"

Game* Game::Instance = new Game();

Game::Game()
{
    Instance = this;
    mBaseLife = 1000;
    mSpawnTimer = sf::Time::Zero;
    mWave = 0;
    mMoney = 300;
    std::string lang;
    int vol;
    if (!mSettings.loadFromFile("Assets/Data/settings.dat"))
    {
        lang = "en";
        vol = 100;
        mSettings.set<std::string>("Lang",lang);
        mSettings.set<bool>("Fullscreen",true);
        mSettings.set<int>("MusicVolume",vol);
        mSettings.set<int>("SoundVolume",vol);
    }
    else
    {
        mSettings.get<std::string>("Lang",lang);
    }
    loadLangFile(std::string("Assets/Lang/" + lang + ".lang"));
    mMusics.setVolume(static_cast<float>(vol));
    mIcon.loadFromFile("Assets/Atmog/icon.png");
    app::System::getWindow().setIcon(mIcon.getSize().x,mIcon.getSize().y,mIcon.getPixelsPtr());
}

void Game::init()
{
    Instance = new Game();
}

void Game::release()
{
    if (Instance != nullptr)
    {
        Instance->mSettings.saveToFile();
    }
    Instance = nullptr;
}

Game& Game::instance()
{
    if (Instance == nullptr)
    {
        init();
    }
    return *Instance;
}

void Game::update(sf::Time dt)
{
    if (Instance == nullptr)
    {
        init();
    }
    Instance->mEntities.update(dt);
    Instance->mClock += dt;
    Instance->mSpawnTimer += dt;
    if (Instance->mSpawnTimer >= sf::seconds(5))
    {
        Instance->mWave++;
        for (int i = 0; i < Instance->mWave; i++)
        {
            Instance->mEntities.spawnEnemy(Instance->mWave);
        }
        Instance->mSpawnTimer = sf::Time::Zero;
    }
    Instance->mSounds.update();
}

void Game::handleEvent(sf::Event const& event)
{
    if (Instance == nullptr)
    {
        init();
    }
    Instance->mEntities.handleEvent(event);
}

void Game::render()
{
    if (Instance == nullptr)
    {
        init();
    }
    app::System::getWindow().draw(Instance->mEntities);
}

void Game::playMusic(std::string const& filename)
{
    if (Instance == nullptr)
    {
        init();
    }
    if (Instance->mMusics.openFromFile(filename))
    {
        Instance->mMusics.setVolume(static_cast<float>(getMusicVolume()));
        Instance->mMusics.setLoop(true);
        Instance->mMusics.sf::Music::play();
    }
    else
    {
        app::System::getLog() << std::string("Can't load Music : " + filename);
    }
}

std::shared_ptr<sf::Sound> Game::playSound(std::string const& filename)
{
    if (Instance == nullptr)
    {
        init();
    }
    Instance->mSounds.update();
    std::shared_ptr<sf::Sound> sound = Instance->mSounds.play(filename,static_cast<float>(getSoundVolume()));
    if (sound == nullptr)
    {
        app::System::getLog() << std::string("Error with Sound : " + filename);
    }
    else
    {
        sound->setVolume(static_cast<float>(getSoundVolume()));
    }
    return sound;
}

int Game::getMusicVolume()
{
    if (Instance == nullptr)
    {
        init();
    }
    int actualValue = 100;
    Instance->mSettings.get<int>("MusicVolume",actualValue);
    return actualValue;
}

int Game::getSoundVolume()
{
    if (Instance == nullptr)
    {
        init();
    }
    int actualValue = 100;
    Instance->mSettings.get<int>("SoundVolume",actualValue);
    return actualValue;
}

void Game::setMusicVolume(int volume)
{
    if (Instance == nullptr)
    {
        init();
    }
    int actualValue = 100;
    Instance->mSettings.get<int>("MusicVolume",actualValue);
    if (volume != actualValue)
    {
        Instance->mSettings.set<int>("MusicVolume",volume);
        Instance->mMusics.setVolume(static_cast<float>(volume));
    }
}

void Game::setSoundVolume(int volume)
{
    if (Instance == nullptr)
    {
        init();
    }
    int actualValue = 100;
    Instance->mSettings.get<int>("SoundVolume",actualValue);
    if (volume != actualValue)
    {
        Instance->mSounds.update();
        Instance->mSettings.set<int>("SoundVolume",volume);
        Instance->mSounds.setVolume(static_cast<float>(volume));
    }
}

bool Game::getFullScreen()
{
    if (Instance == nullptr)
    {
        init();
    }
    bool actualValue = false;
    Instance->mSettings.get<bool>("Fullscreen",actualValue);
    return actualValue;
}

bool Game::setFullScreen(bool value)
{
    if (Instance == nullptr)
    {
        init();
    }
    bool actualValue = false;
    Instance->mSettings.get<bool>("Fullscreen",actualValue);
    if (value != actualValue)
    {
        Instance->mSettings.set<bool>("Fullscreen",value);
        return true;
    }
    return false;
}

EntityManager& Game::getEntityManager()
{
    if (Instance == nullptr)
    {
        init();
    }
    return Instance->mEntities;
}

void Game::loadLangFile(std::string const& filename)
{
    if (Instance == nullptr)
    {
        init();
    }
    Instance->mLang.loadFromFile(filename);
    if (filename == "Assets/Data/en.lang")
    {
        Instance->mSettings.set<std::string>("Lang","en");
    }
    else if (filename == "Assets/Data/fr.lang")
    {
        Instance->mSettings.set<std::string>("Lang","fr");
    }
}

std::string Game::getTextLang(std::string const& id)
{
    if (Instance == nullptr)
    {
        init();
    }
    std::string text;
    Instance->mLang.get<std::string>(id,text);
    return text;
}

int Game::getBaseLife()
{
    if (Instance == nullptr)
    {
        init();
    }
    return Instance->mBaseLife;
}

void Game::attackBase(int damage)
{
    if (Instance == nullptr)
    {
        init();
    }
    Instance->mBaseLife -= damage;
    Instance->mBaseLife = std::max(0,Instance->mBaseLife);
}

int Game::getMoney()
{
    if (Instance == nullptr)
    {
        init();
    }
    return Instance->mMoney;
}

void Game::earnMoney(int amount)
{
    if (Instance == nullptr)
    {
        init();
    }
    Instance->mMoney += amount;
}

void Game::spendMoney(int amount)
{
    if (Instance == nullptr)
    {
        init();
    }
    Instance->mMoney -= amount;
}

int Game::getTime()
{
    if (Instance == nullptr)
    {
        init();
    }
    return static_cast<int>(Instance->mClock.asSeconds());
}

void Game::startNewGame()
{
    if (Instance == nullptr)
    {
        init();
    }
    Instance->mEntities.reset();
    Instance->mClock = sf::Time::Zero;
    Instance->mSpawnTimer = sf::Time::Zero;
    Instance->mBaseLife = 1000;
    Instance->mWave = 0;
    Instance->mMoney = 300;
    Instance->mSounds.update();
}

void Game::addGame()
{
    sf::Http::Request request("/Tehos/counter.php", sf::Http::Request::Post);
    request.setBody("");

    sf::Http http("http://atmog.altervista.org/");
    sf::Http::Response response = http.sendRequest(request);

    if (response.getStatus() != sf::Http::Response::Ok)
    {
        app::System::getLog() << "Failed to submit game";
    }
}
