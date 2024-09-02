#pragma once
#include <any>
#include <iostream>
#include <vector>
#include "boid.h"
#include <SFML/Graphics.hpp>


struct Point {
	float x;
	float y;
	Boid userData;
};

//Axis aligned bounding box
class AABB {
public:
	float x;
	float y;
	float halfDimension;

	AABB(float x, float y, float halfDimension);
	bool containsPoint(Point p);
	bool intersects(AABB& other);
};

class Quadtree
{
private:
	int capacity;
	AABB boundary;
	std::vector<Point> points;

	Quadtree* northWest;
	Quadtree* northEast;
	Quadtree* southWest;
	Quadtree* southEast;

public:
	Quadtree(AABB _boundary, int capacity);
	bool insert(Point p);
	void subdivide(); 
	std::vector<Point> queryRange(AABB range);
	void draw(sf::RenderWindow& window);

	std::vector<Boid> getUserData(std::vector<Point> points);
	void clear();
};

