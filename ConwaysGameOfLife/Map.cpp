#include "stdafx.h"
#include "Map.h"


Map::Map(unsigned sizeX, unsigned sizeY, unsigned tileSize)
{
	m_zoom = 1.0f;
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_simState = false;
	steps = 0;
	stepDenominator = 100;

	createGrid(sizeX, sizeY);
}


Map::~Map()
{
}

bool Map::render(sf::RenderWindow& window)
{
	for (auto it : m_grid)
	{
		it.second->render(window);
	}
	
	return true;
}

// Create grid
void Map::createGrid(unsigned sizeX, unsigned sizeY)
{
	std::cout << "Creating Grid. Be patient...." << std::endl;
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			// TODO: Remove Magic Numbers
			Tile* t = new Tile(sf::Vector2f((800 /sizeX) * x, (800 / sizeY) * y), sf::Vector2f(800 / sizeX, 800 / sizeY));
			std::pair<Position, Tile*> p(Position(x, y), t);
			m_grid.emplace(p);
		}
	}
}

// Mouse pos
void Map::mousePos(unsigned x, unsigned y, bool left)
{
	unsigned tileX = floor(x / (800 / m_sizeX));
	unsigned tileY = floor(y / (800 / m_sizeY));
	if (tileX > m_sizeX) tileX = m_sizeX;
	if (tileY > m_sizeX) tileY = m_sizeY;
	if (tileX < 0) tileX = 0;
	if (tileY < 0) tileY = 0;

	if (left) m_grid.find(Position(tileX, tileY))->second->forceStateChange(true);
	else m_grid.find(Position(tileX, tileY))->second->forceStateChange(false);
}

// Simulates
bool Map::update()
{
	if (m_simState && steps % stepDenominator == 0)
	{
		//std::cout << "Start simulation" << std::endl;
		for (auto it : m_grid)
		{
			// TODO HARDCODED UUGHHHH KILL ME
			int neighbours = 0;
			if (m_grid.find(Position(it.first.x - 1, it.first.y - 1)) != m_grid.end())
			{
				if (m_grid.find(Position(it.first.x - 1, it.first.y - 1))->second->getTileState()) neighbours++;
			}

			if (m_grid.find(Position(it.first.x    , it.first.y - 1)) != m_grid.end())
			{
				if (m_grid.find(Position(it.first.x    , it.first.y - 1))->second->getTileState()) neighbours++;
			}

			if (m_grid.find(Position(it.first.x + 1, it.first.y - 1)) != m_grid.end())
			{
				if (m_grid.find(Position(it.first.x + 1, it.first.y - 1))->second->getTileState()) neighbours++;
			}

			if (m_grid.find(Position(it.first.x - 1, it.first.y    )) != m_grid.end())
			{
				if (m_grid.find(Position(it.first.x - 1, it.first.y    ))->second->getTileState()) neighbours++;
			}

			if (m_grid.find(Position(it.first.x + 1, it.first.y    )) != m_grid.end())
			{
				if (m_grid.find(Position(it.first.x + 1, it.first.y    ))->second->getTileState()) neighbours++;
			}

			if (m_grid.find(Position(it.first.x - 1, it.first.y + 1)) != m_grid.end())
			{
				if (m_grid.find(Position(it.first.x - 1, it.first.y + 1))->second->getTileState()) neighbours++;
			}

			if (m_grid.find(Position(it.first.x    , it.first.y + 1)) != m_grid.end())
			{
				if (m_grid.find(Position(it.first.x    , it.first.y + 1))->second->getTileState()) neighbours++;
			}

			if (m_grid.find(Position(it.first.x + 1, it.first.y + 1)) != m_grid.end())
			{
				if (m_grid.find(Position(it.first.x + 1, it.first.y + 1))->second->getTileState()) neighbours++;
			}

			//if (it.first.x == 1 && it.first.y == 1) std::cout << neighbours << std::endl;

			if (neighbours < 2)
			{
				//if (it.first.x == 1 && it.first.y == 1) std::cout << "dying..." << std::endl;
				it.second->changeStateTo(false);
			}
			if (neighbours == 2) it.second->changeStateTo(it.second->getTileState());
			if (neighbours == 3) 
			{
				//if (it.first.x == 1 && it.first.y == 1) std::cout << "reviving..." << std::endl;
				it.second->changeStateTo(true);
			}
			if (neighbours > 3) it.second->changeStateTo(false);

			//if (it.first.x == 1 && it.first.y == 1) std::cout << it.second->getWillChangeState() << std::endl;
		}
		
		for (auto it : m_grid)
		{
			it.second->applyStateChange();
			//if (it.first.x == 1 && it.first.y == 1) std::cout << it.second->getTileState() << std::endl;
		}
		//std::cout << "End simulation" << std::endl;
		//std::cout << std::endl;
	}
	steps++;

	return true;
}