#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
	unsigned int width = 640;
	unsigned int height = 360;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Tutorials");

	while (window->isOpen()) {
		while (const std::optional event = window->pollEvent()) {
			// Close the window
			if (event->is<sf::Event::Closed>()) {
				window->close();
			}

			// Close if Esc key pressed
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
					window->close();
				}
			}
		}

		// Render
		window->clear(sf::Color(0xFF8800FF)); // Background color to Orange

		// Drawing
		window->display();
	}
	delete window;
	return 0;
}