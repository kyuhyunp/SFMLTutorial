#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf::Literals;

enum directions { down, right, up, left };

int main() {
	unsigned int width = 640;
	unsigned int height = 360;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Tutorials");
	window->setFramerateLimit(60);

	sf::Texture texture;
	if (!texture.loadFromFile("Sprites/ExampleSprite.png")) {
		std::cerr << "ERROR: COULD NOT LOAD FILE:: Sprites/ExampleSprite.png\n";
		return -1;
	}

	// Sprites/ExampleSprite.png is loaded in sprite
	sf::Sprite sprite(texture);
	
	// Dividing the example sprite image into four images 32 x 32 pixels
	sf::IntRect dir[4];
	for (int i = 0; i < 4; ++i) {
		dir[i] = sf::IntRect({ {32 * i, 0}, {32, 32} });
	}

	sprite.setTextureRect(dir[down]); // First image in dir
	sprite.setOrigin({ 16, 16 });
	sprite.setPosition({ width / 2.0f, height / 2.0f });
	sprite.setColor(sf::Color(0x6495EDFF));

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::R)) {
			sprite.rotate(sf::degrees(1));
		}
		

		sf::Angle currentRotation = sprite.getRotation();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
			sprite.move({ std::cosf((currentRotation + 90_deg).asRadians()), std::sinf((currentRotation + 90_deg).asRadians()) });
			sprite.setTextureRect(dir[down]);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
			sprite.move({ std::cosf((currentRotation - 90_deg).asRadians()), std::sinf((currentRotation - 90_deg).asRadians()) });
			sprite.setTextureRect(dir[up]);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
			sprite.move({ std::cosf(currentRotation.asRadians()), std::sinf(currentRotation.asRadians()) });
			sprite.setTextureRect(dir[right]);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
			sprite.move({ std::cosf((currentRotation + 180_deg).asRadians()), std::sinf((currentRotation + 180_deg).asRadians()) });
			sprite.setTextureRect(dir[left]);
		}


		// Render
		window->clear(); 

		// Drawing
		window->draw(sprite);

		window->display();
	}

	delete window;
	return 0;
}