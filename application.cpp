#include "application.h"

void Application::start() {
	srand(time(0));
	createWindow();
	
	for (int i = 0; i < Settings::NumberOfBoids; i++) {
		Boid newBoid = Boid{ (float)((double)rand() / (RAND_MAX)) * Settings::ScreenWidth, (float)((double)rand() / (RAND_MAX)) * Settings::ScreenHeight,(float)(rand() % 101)-50.f,(float)(rand() % 51) - 50.f };
		boids.push_back(newBoid);
	}
	while (window.isOpen()) {
		update();
	}
	destroyWindow();
}

void Application::createWindow() {
	window.create(sf::VideoMode(Settings::ScreenWidth, Settings::ScreenHeight), "Boids2D", sf::Style::Titlebar | sf::Style::Close);
}

void Application::update() {
	deltaTime = clock.getElapsedTime().asSeconds();
	clock.restart();

	while (window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		}
	}

	for (Boid& boid : boids) {
		boid.constrainEdges();
		boid.align(boids);
		boid.update(deltaTime);
		boid.draw(window);
	}
	window.display();
	window.clear();
}


void Application::destroyWindow() {
	window.close();
}