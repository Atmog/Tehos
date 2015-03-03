#include "Base.hpp"

Base::Base(Targetable::Team team)
{
    mTeam = team;
    if (mTeam == Targetable::Red)
        mSprite.setTexture(cf::Application::getResources().getTexture("Assets/Textures/basered.png"));
    if (mTeam == Targetable::Blue)
        mSprite.setTexture(cf::Application::getResources().getTexture("Assets/Textures/baseblue.png"));
    mSprite.setOrigin(250,250);
    mLife = 1000.f;
    mMaxLife = 1000.f;
}
