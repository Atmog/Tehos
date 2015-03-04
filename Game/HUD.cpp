#include "HUD.hpp"

HUD::HUD()
{

}

HUD::Action HUD::handleEvent(sf::Event const& event)
{
    return HUD::Action::None;
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mGUI,states);
}
