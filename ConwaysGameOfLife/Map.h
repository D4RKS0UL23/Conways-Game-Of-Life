/**
 * Map.h
 * Contains the Grid of CGOL and handles the generations
 *
 * @author Robert Altner
 * @version 1.0
*/


#pragma once

#include "stdafx.h"
#include "Tile.h"

struct Position
{
	int x, y;

	Position(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

};

inline bool operator <(Position left, Position right)
{
	if (left.y < right.y) return true;
	else if (left.y > right.y) return false;
	else if (left.y == right.y)
	{
		if (left.x < right.x) return true;
		else return false;
	}
	else return false;
}

class Map
{
public:
	Map(unsigned sizeX, unsigned sizeY, unsigned tileSize);
	~Map();

	/**
		Renders Grid and Tiles to the window

		@param window A reference to the window
		@return False if an error occured
	*/
	bool render(sf::RenderWindow& window);

	/**
		Simulates
	*/
	bool update();

	/**
		Gets called when a mouse click was received

		@param x xPos of the Cursor
		@param y yPos of the Cursor
	*/
	void mousePos(unsigned x, unsigned y, bool left);

	void increaseSpeed() { stepDenominator--; if (stepDenominator <= 0) stepDenominator = 1; }
	void decreaseSpeed() { stepDenominator++; }
	/**
		Changes if we should simulate
	*/
	void changeSimulationState() { m_simState = !m_simState; }

private:
	float m_zoom;
	unsigned int m_tileSize;
	unsigned m_sizeX, m_sizeY;
	bool m_simState;
	unsigned steps;
	unsigned stepDenominator;

	std::map<Position, Tile*> m_grid;

	/**
		Create Grid

		@param sizeX x size of the grid
		@param suzeY y size of the grid
	*/
	void createGrid(unsigned sizeX, unsigned sizeY);
};

