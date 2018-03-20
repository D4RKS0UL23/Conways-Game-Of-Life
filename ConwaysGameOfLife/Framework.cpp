#include "stdafx.h"
#include "Framework.h"

// Initilaize static variables
sf::RenderWindow*	Framework::m_window = nullptr;
sf::Event			Framework::m_event = sf::Event();
//TestRender			Framework::m_test = TestRender();
Map					Framework::m_map = Map(50, 50, 10);

bool Framework::init(unsigned width, unsigned height, const char* title, sf::Uint8 flags)
{
	// If Window does not exist, create it
	if (m_window == nullptr)
	{
		m_window = new sf::RenderWindow(sf::VideoMode(width, height), title, flags);
	}

	// If window is still nullptr, throw error
	if (m_window == nullptr)
	{
		std::cout << "Window could not be created." << std::endl;
		system("PAUSE");
		return false;
	}

	return true;
}

// Program loop
bool Framework::run()
{
	// If no window, break
	if (m_window == nullptr)
	{
		std::cout << "Cannot run program loop if no window was initialized. Call Framework::init first." << std::endl;
		system("PAUSE");
		return false;
	}

	// The loop
	while (m_window->isOpen())
	{
		// Run update(). If an error occures, break
		if (update() == false)
		{
			std::cout << "An Error occured in Framework::update()" << std::endl;
			system("PAUSE");
			release();
			return false;
		}
		
		// Run handleEvents(). If an error occures, break
		if (handleEvents() == false)
		{
			std::cout << "An Error occured in Framework::handleEvents()" << std::endl;
			system("PAUSE");
			release();
			return false;
		}

		// Run render(). If an error occures, break
		if (render() == false)
		{
			std::cout << "An Error occured in Framework::render()" << std::endl;
			system("PAUSE");
			release();
			return false;
		}
	}

	// release window
	release();

}

// Updates screen elements
bool Framework::update()
{
//	if (!m_test.update()) return false;
	m_map.update();
	return true;
}

// Handles window events
bool Framework::handleEvents()
{
	static float mouseDelta = 0;
	while (m_window->pollEvent(m_event))
	{
		// On Close Event
		if (m_event.type == sf::Event::Closed) m_window->close();

		if (m_event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				m_map.changeSimulationState();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
				m_map.increaseSpeed();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
				m_map.decreaseSpeed();
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		m_map.mousePos(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y, true);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		m_map.mousePos(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y, false);
	}

	

	return true;
}

// Renders objects
bool Framework::render()
{
	m_window->clear();

//	if (!m_test.render(*m_window)) return false;
	if (!m_map.render(*m_window)) return false;

	m_window->display();

	return true;
}

// Releases pointers
void Framework::release()
{
	m_window = nullptr;
	delete m_window;
	std::cout << "Released window" << std::endl;
}