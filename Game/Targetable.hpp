#ifndef TARGETABLE_HPP
#define TARGETABLE_HPP

#include "SceneNode.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

class Targetable : public SceneNode
{
    public:
        typedef std::shared_ptr<Targetable> Ptr;

        Targetable();

        enum Team
        {
            None = 0,
            Blue,
            Red,
        };

        void setTeam(Team team);
        Team getTeam() const;

        void setLife(int life);
        int getLife() const;

        void setMaxLife(int maxLife);
        int getMaxLife() const;

        void inflige(int amount);
        void restore(int amount);

        bool isAlive() const;
        bool isDead() const;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual bool remove() const;

    protected:
        Team mTeam;
        int mLife;
        int mMaxLife;
};

#endif // TARGETABLE_HPP
