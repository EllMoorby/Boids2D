#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"

#include <iostream>

class Application
{
private:
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock clock;

public:
	void start(); //Starts the program
	void createWindow();
	void update(); //Runs every frame
	void destroyWindow();
};
