#include "SoundPlayer.hpp"

SoundPlayer::SoundPlayer()
{
    //ctor
}

SoundPlayer::SoundPtr SoundPlayer::play(std::string const& filename, float volume)
{
    if(!mBuffers.isLoaded(filename))
    {
        if(!mBuffers.load(filename))
        {
            return nullptr;
        }
    }
    SoundPtr sound(new sf::Sound);
    auto itr = mSounds.emplace(filename,std::move(sound));
    itr->second->setBuffer(mBuffers.get(filename));
    itr->second->play();
    itr->second->setVolume(volume);
    return itr->second;
}

void SoundPlayer::setVolume(float volume)
{
    for(auto itr = mSounds.begin(); itr != mSounds.end(); ++itr)
    {
        itr->second->setVolume(volume);
    }
}

void SoundPlayer::stop()
{
    mSounds.clear();
}

void SoundPlayer::update()
{
    for(auto itr = mSounds.begin(); itr != mSounds.end(); ++itr)
    {
        if(itr->second->getStatus() == sf::Sound::Stopped)
        {
            mSounds.erase(itr);
        }
    }
}
