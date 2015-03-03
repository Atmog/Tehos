#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "SceneNode.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class Effect : public SceneNode
{
    public:
        typedef std::shared_ptr<Effect> Ptr;

        Effect();

        void setLimit(sf::Time limit);
        sf::Time getLimit() const;
        sf::Time getActualTime() const;

        virtual bool remove() const;

    protected:
        sf::Time mLimit;
        sf::Clock mClock;
};

#endif // EFFECT_HPP
