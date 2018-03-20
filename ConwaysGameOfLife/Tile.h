/**
 * Tile.h
 * Basically a wrapper class for sf::Rextangle but with
 * extra features
 *
 * @author Robert Altner
 * @version 1.0
*/

#pragma once

#include "stdafx.h"

class Tile
{
public:
	Tile(sf::Vector2f position, sf::Vector2f size);
	~Tile();

	/**
		Returns state of a tile

		@return True if alive, False if dead
	*/
	bool				getTileState() { return state; }
	bool				getWillChangeState() { return willChangeTo; }

	/**
		Sets new size of Tile

		@param size new size
	*/
	void				resize(sf::Vector2f size) { m_tile.setSize(size); }

	/**
		Sets new position of Tile

		@param position new position
	*/
	void				reposition(sf::Vector2f position) { m_tile.setPosition(position); }

	/**
		Sets a tile either as alive or dead
	*/
	void				applyStateChange();

	/**
		Makes a tile either alive or dead

		@param state New State
	*/
	void				forceStateChange(bool state) { willChangeTo = state; applyStateChange(); }

	/**
		Sets willChangeTo

		@param should Should the cell die?
	*/
	void				changeStateTo(bool should) { willChangeTo = should; }

	/**
		Renders the Tile

		@param window Reference to window
		@return False if an error occured
	*/
	bool				render(sf::RenderWindow& window);

private:
	sf::RectangleShape	m_tile;
	bool				state;	//True = alive, False = dead
	bool				willChangeTo;
};

