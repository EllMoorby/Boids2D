#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include "boid.h"
#include <iostream>

class Application
{
private:
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock clock;
	float deltaTime;
	std::vector<Boid> boids;

public:
	void start(); //Starts the program
	void createWindow();
	void update(); //Runs every frame
	void destroyWindow();
};
