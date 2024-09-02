#include "quadtree.h"

AABB::AABB(float x, float y, float halfDimension) {
	this->x = x;
	this->y = y;
	this->halfDimension = halfDimension;
}

bool AABB::containsPoint(Point p) {
	return (p.x >= x - halfDimension && p.x <= x + halfDimension && p.y >= y - halfDimension && p.y <= y + halfDimension);
}

bool AABB::intersects(AABB& other) {
	// Check if one square is to the left of the other
	if (x + halfDimension < other.x - other.halfDimension ||
		other.x + other.halfDimension < x - halfDimension) {
		return false;
	}

	// Check if one square is above the other
	if (y + halfDimension < other.y - other.halfDimension ||
		other.y + other.halfDimension < y - halfDimension) {
		return false;
	}

	return true;
}

Quadtree::Quadtree(AABB _boundary, int capacity): boundary(_boundary) {
	this->capacity = capacity;
}

bool Quadtree::insert(Point p) {
	//Point outside range
	if (!boundary.containsPoint(p)) {
		return false;
	}

	if (points.size() < capacity) {
		points.push_back(p);
		return true;
	}

	//If full subdivide

	//Check if already divided
	if (northWest == NULL) {
		subdivide();
	}
	
	//Add the point to the children
	if (northWest->insert(p)) return true;
	if (northEast->insert(p)) return true;
	if (southWest->insert(p)) return true;
	if (southEast->insert(p)) return true;

	//Failed
	return false;
	
}

void Quadtree::subdivide() {
	AABB northEastBoundary(boundary.x - (boundary.halfDimension / 2), (boundary.y - (boundary.halfDimension / 2)), (boundary.halfDimension / 2));
	AABB northWestBoundary(boundary.x + (boundary.halfDimension / 2), (boundary.y - (boundary.halfDimension / 2)), (boundary.halfDimension / 2));
	AABB southEastBoundary(boundary.x - (boundary.halfDimension / 2), (boundary.y + (boundary.halfDimension / 2)), (boundary.halfDimension / 2));
	AABB southWestBoundary(boundary.x + (boundary.halfDimension / 2), (boundary.y + (boundary.halfDimension / 2)), (boundary.halfDimension / 2));

	northEast = new Quadtree(northEastBoundary, capacity);
	northWest = new Quadtree(northWestBoundary, capacity);
	southEast = new Quadtree(southEastBoundary, capacity);
	southWest = new Quadtree(southWestBoundary, capacity);
}

std::vector<Point> Quadtree::queryRange(AABB range) {
	std::vector<Point> pointsInRange;

	if (!boundary.intersects(range)) {
		return pointsInRange;
	}

	for (int p = 0; p < points.size(); p++)
	{
		if (range.containsPoint(points[p]))
			pointsInRange.push_back(points[p]);
	}

	if (northWest == NULL) {
		return pointsInRange;
	}
		
	std::vector<Point> otherPoints;
	
	otherPoints = northWest->queryRange(range);
	pointsInRange.insert(pointsInRange.end(), otherPoints.begin(), otherPoints.end());
	otherPoints = northEast->queryRange(range);
	pointsInRange.insert(pointsInRange.end(), otherPoints.begin(), otherPoints.end());
	otherPoints = southWest->queryRange(range);
	pointsInRange.insert(pointsInRange.end(), otherPoints.begin(), otherPoints.end());
	otherPoints = southEast->queryRange(range);
	pointsInRange.insert(pointsInRange.end(), otherPoints.begin(), otherPoints.end());

	return pointsInRange;
}

void Quadtree::draw(sf::RenderWindow& window) {
	sf::RectangleShape shape(sf::Vector2f(boundary.halfDimension * 2, boundary.halfDimension * 2));
	shape.setPosition(sf::Vector2f(boundary.x - boundary.halfDimension, boundary.y - boundary.halfDimension));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1);
	if (northWest != NULL) {
		northEast->draw(window);
		northWest->draw(window);
		southEast->draw(window);
		southWest->draw(window);
	}
	window.draw(shape);
}

std::vector<Boid> Quadtree::getUserData(std::vector<Point> points) {
	std::vector<Boid> returnVec;
	for (Point& point : points) {
		returnVec.push_back(point.userData);
	}
	return returnVec;
}

void Quadtree::clear() {
	if (points.size() != 0) {
		points.clear();
	}

	northEast = NULL;
	northWest = NULL;
	southEast = NULL;
	southWest = NULL;
}