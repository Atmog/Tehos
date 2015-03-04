#ifndef EXPLOSIONEFFECT_HPP
#define EXPLOSIONEFFECT_HPP

#include "Effect.hpp"
#include "../Lib/Application.hpp"

class ExplosionEffect : public Effect
{
    public:
        typedef std::shared_ptr<Effect> Ptr;

        ExplosionEffect();
};

#endif // EXPLOSIONEFFECT_HPP
