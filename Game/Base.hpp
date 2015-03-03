#ifndef BASE_HPP
#define BASE_HPP

#include "Targetable.hpp"

#include "../Lib/Application.hpp"

class Base : public Targetable
{
    public:
        typedef std::shared_ptr<Base> Ptr;

        Base(Targetable::Team team);
};

#endif // BASE_HPP
