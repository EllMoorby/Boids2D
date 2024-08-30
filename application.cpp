#include "application.h"

void Application::start() {
	createWindow();
	while (window.isOpen()) {
		update();
	}
	destroyWindow();
}

void Application::createWindow() {
	window.create(sf::VideoMode(Settings::ScreenWidth, Settings::ScreenHeight), "Boids2D", sf::Style::Titlebar | sf::Style::Close);
}

void Application::update() {
	while (window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		}
	}


	window.display();
	window.clear();
}


void Application::destroyWindow() {
	window.close();
}