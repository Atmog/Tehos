#include "ExplosionEffect.hpp"

ExplosionEffect::ExplosionEffect()
: Effect(20,sf::seconds(1.f/20.f))
{
    mFrameSize = sf::Vector2i(51,128);
    mSprite.setTexture(cf::Application::getResources().getTexture("Assets/Textures/explosion.png"));
    mSprite.setOrigin(mFrameSize.x/2,mFrameSize.y);
    update(sf::Time::Zero);
}
