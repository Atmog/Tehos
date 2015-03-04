#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "SceneNode.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class Effect : public SceneNode
{
    public:
        typedef std::shared_ptr<Effect> Ptr;

        Effect(sf::Int64 frames = 0, sf::Time timePerFrame = sf::Time::Zero);
        virtual void update(sf::Time dt);
        virtual bool remove() const;

    protected:
        const sf::Int64 mFrames;
        const sf::Time mTimePerFrame;
        sf::Vector2i mFrameSize;
        sf::Clock mClock;
};

#endif // EFFECT_HPP
