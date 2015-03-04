#ifndef CONFICIA_VECTOR_HPP
#define CONFICIA_VECTOR_HPP

#include <SFML/System/Vector2.hpp>
#include "Trigonometry.hpp"

namespace cf
{

float length(sf::Vector2f v);

float distance(sf::Vector2f v1, sf::Vector2f v2);

void rotate(sf::Vector2f& v, float deg);

void normalize(sf::Vector2f& vector);

sf::Vector2f normalizedVector(sf::Vector2f vector);

float getAngle(sf::Vector2f vector);

}

#endif // CONFICIA_VECTOR_HPP
