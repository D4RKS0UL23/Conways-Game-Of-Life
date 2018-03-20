#include "stdafx.h"
#include "Tile.h"


Tile::Tile(sf::Vector2f position, sf::Vector2f size)
{
	willChangeTo = false;
	state = false;

	m_tile.setPosition(position);
	m_tile.setSize(size);
	m_tile.setFillColor(sf::Color::Black);
}


Tile::~Tile()
{
}

// Renders Tile
bool Tile::render(sf::RenderWindow& window)
{
	window.draw(m_tile);
	return true;
}

// Change state of cell
void Tile::applyStateChange()
{
	//if(!state) std::cout << state << ", " << willChangeTo << std::endl;
	state = willChangeTo;
	
	if (state == true) m_tile.setFillColor(sf::Color::White);
	if (state == false) m_tile.setFillColor(sf::Color::Black);
}