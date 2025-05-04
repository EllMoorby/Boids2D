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
	velocity = limit(velocity, Settings::MaxSpeed);
}

void Boid::align(std::vector<Boid> boids) {
	sf::Vector2f avrVel;
	sf::Vector2f avrPos;
	sf::Vector2f avrDif;
	sf::Vector2f difference;

	sf::Vector2f facing = setMagnitude(velocity, 1);


	int totalBoids = 0;
	for (Boid& boid : boids) {
		float dist = getDistance(boid);
		if (dist != 0.f) {
			if (dist <= Settings::Distance && isInView(boid.getPosition())) {
				avrVel += boid.getVelocity();
				avrPos += boid.getPosition();

				difference = position - boid.getPosition();
				difference /= dist;
				avrDif += difference;

				totalBoids++;
			}
		}
		
	}
	if (totalBoids != 0){
		avrVel /= (float)totalBoids;
		avrVel = setMagnitude(avrVel, Settings::MaxSpeed);
		avrVel -= velocity;
		avrVel = limit(avrVel, Settings::SteeringFactor);

		avrPos /= (float)totalBoids;
		avrPos -= position;
		avrPos = setMagnitude(avrPos, Settings::MaxSpeed);
		avrPos -= velocity;
		avrPos = limit(avrPos, Settings::SteeringFactor);

		avrDif /= (float)totalBoids;
		avrDif = setMagnitude(avrDif, Settings::MaxSpeed);
		avrDif -= velocity;
		avrDif = limit(avrDif, Settings::SteeringFactor);
	}
	acceleration = sf::Vector2f(0, 0);
	acceleration += avrVel;
	acceleration += avrPos;
	acceleration += scaleVector(avrDif,1.5);
	
}

bool Boid::isInView(sf::Vector2f otherPos) {
	
	sf::Vector2f difference = otherPos - position;
	float magnitude = sqrt(pow(difference.x, 2) + pow(difference.y, 2));
	sf::Vector2f unitVelocity = limit(velocity, 1);
	//Find cos(angle) in radians
	float cosAngle = (unitVelocity.x * difference.x) + (unitVelocity.y * difference.y);
	cosAngle /= magnitude;
	
	float angle = std::acos(cosAngle);
	float degrees = angle * (180.0 / M_PI);
	if (degrees > Settings::Angle) { return false; } else { return true; }
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

sf::Vector2f Boid::scaleVector(sf::Vector2f vec, float size) {
	return vec * size;
}

void Boid::draw(sf::RenderWindow& window) {
	body.setPosition(sf::Vector2f(position.x - tempRadius, position.y - tempRadius));
	sf::Vertex line[] =
	{
		sf::Vertex(position),
		sf::Vertex(position + limit(velocity,50))
	};
	window.draw(line, 2, sf::Lines);
	window.draw(body);
}

sf::Vector2f Boid::getPosition() {return position;}
sf::Vector2f Boid::getVelocity() {return velocity;};