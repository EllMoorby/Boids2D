#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>

#include "settings.h"
#include <iostream>
#include <cstdlib>
#include <math.h>

class Boid
{
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::CircleShape body;

	//REMOVE
	int tempRadius;
public:
	Boid(float x, float y, float velX, float velY);

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	float getDistance(Boid other);

	void update(float dt);
	void draw(sf::RenderWindow& window);
	void align(std::vector<Boid> boids);
	void constrainEdges();

	bool isInView(sf::Vector2f otherPos);

	sf::Vector2f limit(sf::Vector2f vec, float size);
	sf::Vector2f setMagnitude(sf::Vector2f vec, float size);
	sf::Vector2f scaleVector(sf::Vector2f vec, float size);
};

