#include "stdafx.h"
#include "TestRender.h"


TestRender::TestRender()
{
	startPos = sf::Vector2f(200, 200);

	circle = sf::CircleShape(200);
	circle.setFillColor(sf::Color::Green);
	circle.setPosition(startPos);

	counter = 0;
}

bool TestRender::render(sf::RenderWindow& window)
{
	window.draw(circle);
	return true;
}

bool TestRender::update()
{
	circle.setPosition(startPos + sf::Vector2f(sin(counter) * 100, cos(counter) * 100));
	counter += 0.001;
	return true;
}