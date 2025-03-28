#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>


void PollEvents(sf::RenderWindow& window) {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
				window.close();
			}
		}
	}
}

int main() {
	unsigned int width = 640;
	unsigned int height = 360;
	auto window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ width, height }), "Tutorials");
	window->setFramerateLimit(60);

	sf::Font font;
	std::string filename = "Fonts/ARIAL.TTF";
	if (!font.openFromFile(filename)) {
		std::cerr << "ERROR COULD NOT LOAD FILE:: " << filename << "\n";
		return -1;
	}

	sf::Text text(font);
	text.setString("Time: 0.000000");
	text.setOrigin(text.getGlobalBounds().size / 2.0f);
	text.setPosition({ width / 2.0f, height / 2.0f });
	text.setFillColor(sf::Color(0x6495EDFF));
	text.setOutlineThickness(1.0f);
	text.setOutlineColor(sf::Color(0x9B6A12FF));

	sf::Clock clock;
	float dt;

	while (window->isOpen()) {
		PollEvents(*window);
		
		dt = clock.restart().asSeconds();

		std::stringstream sStream;
		sStream << "Time: " << dt;
		text.setString(sStream.str());

		// Render
		window->clear(); 

		// Drawing
		window->draw(text);

		window->display();
	}

	return 0;
}