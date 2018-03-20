/**
 * TestRender.h
 * A class used by me to test rendering/update functionality of Framework.h
 *
 * @author Robert Altner
 * @version 1.0
*/

#pragma once

#include "stdafx.h"

class TestRender
{
public:
	TestRender();

	bool render(sf::RenderWindow& window);
	bool update();

private:
	sf::CircleShape circle;
	sf::Vector2f	startPos;
	float counter;
};

