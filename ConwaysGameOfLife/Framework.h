/**
 * Framework.h
 * Handles Events, Updates and Renders the Window
 * It is static, since only one window should be created
 *
 * @author Robert Altner
 * @version 1.0
*/

#pragma once

#include "stdafx.h"

class Framework
{
public:
	/**
		Initializes a window

		@param width Width of the window
		@param height Height of the window
		@param title Title of the window
		@param flags A uint with SFML flags
		@return True if success, False if fail
	*/
	static bool						init(unsigned width, unsigned height, const char* title, sf::Uint8 flags);

	/**
		The program loop

		@return False if an error occured
	*/
	static bool						run();
	
private:
	static sf::RenderWindow*		m_window;			// A reference to a window object
	static sf::Event				m_event;			// The event handling variable of SFML
//	static TestRender				m_test;
	static Map						m_map;				// The grid

	/**
		Updates the elements on screen

		@return False if an error occured
	*/
	static bool						update();

	/**
		Handles events in the program

		@return False if an error occured
	*/
	static bool						handleEvents();

	/**
		Renders elements to screen

		@return False if an error occured
	*/
	static bool						render();

	/**
		Deletes pointers
	*/
	static void						release();
};

