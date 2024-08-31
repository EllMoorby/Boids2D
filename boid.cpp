#include "boid.h"

Boid::Boid(float x, float y, float velX, float velY) {

	position.x = x;
	position.y = y;
	tempRadius = 10;
	body.setRadius(tempRadius);
	velocity = sf::Vector2f(velX,velY);
}

void Boid::update(float dt) {
	position += velocity * dt;
	velocity += acceleration * dt;
	std::cout << velocity.x << " " << velocity.y << "\n";
}

void Boid::align(std::vector<Boid> boids) {
	sf::Vector2f avrVec;
	int totalBoids = 0;
	for (Boid& boid : boids) {
		float dist = getDistance(boid);
		if (dist <= Settings::Distance && dist != 0.f) {
			avrVec += boid.getVelocity();
			totalBoids++;
		}
	}
	if (totalBoids != 0){
		avrVec /= (float)totalBoids;
		avrVec = setMagnitude(avrVec, Settings::MaxSpeed);
		avrVec -= velocity;
		avrVec = limit(avrVec, Settings::SteeringFactor);
	}
	acceleration = avrVec;
	//std::cout << acceleration.x << " " << acceleration.y<<"\n";
}

void Boid::constrainEdges() {
	if (position.x < 0) {
		position.x = Settings::ScreenWidth;
	}
	if (position.y < 0) {
		position.y = Settings::ScreenHeight;
	}
	if (position.x > Settings::ScreenWidth) {
		position.x = 0;
	}
	if (position.y > Settings::ScreenHeight) {
		position.y = 0;
	}
}

float Boid::getDistance(Boid other) {
	sf::Vector2f difference = position - other.getPosition();
	return sqrt(pow(difference.x, 2) + pow(difference.y, 2));
}

sf::Vector2f Boid::limit(sf::Vector2f vec, float size) {
	float magnitude = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
	if (magnitude <= size) {return vec;}
	return (size / magnitude) * vec;
}

sf::Vector2f Boid::setMagnitude(sf::Vector2f vec, float size) {
	float magnitude = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
	return (size / magnitude) * vec;
}

void Boid::draw(sf::RenderWindow& window) {
	body.setPosition(sf::Vector2f(position.x - tempRadius, position.y - tempRadius));
	window.draw(body);
}

sf::Vector2f Boid::getPosition() {return position;}
sf::Vector2f Boid::getVelocity() {return velocity;};