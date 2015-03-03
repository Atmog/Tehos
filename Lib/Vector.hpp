#ifndef CONFICIA_VECTOR_HPP
#define CONFICIA_VECTOR_HPP

#include <SFML/System/Vector2.hpp>
#include "Trigonometry.hpp"

namespace cf
{

float length(sf::Vector2f v);

float distance(sf::Vector2f v1, sf::Vector2f v2);

void rotate(sf::Vector2f& v, float deg);

}

#endif // CONFICIA_VECTOR_HPP
