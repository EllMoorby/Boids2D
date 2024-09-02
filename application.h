#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include "boid.h"
#include <any>
#include "quadtree.h"


class Application
{
private:
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock clock;
	float deltaTime;
	std::vector<Boid> boids;
	Quadtree* quadtree;

public:
	void start(); //Starts the program
	void createWindow();
	void update(); //Runs every frame
	void destroyWindow();
	Quadtree buildQuadtree();
};
