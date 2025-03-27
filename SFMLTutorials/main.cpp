#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>


void PollEvents(sf::RenderWindow& window) {
	while (const auto event = window.pollEvent()) {
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

	sf::Texture texture;
	if (!texture.loadFromFile("Sprites/AnimationExample.png")) {
		std::cerr << "ERROR COULD NOT LOAD FILE: Sprites/AnimationExample.png!!!\n";
		return -1;
	}

	sf::Sprite sprite(texture);
	int texWidth = 0;

	sprite.setTextureRect({ { 0, 0 }, { 32, 32 } });
	sprite.setOrigin({ sprite.getTextureRect().size.x / 2.0f, sprite.getTextureRect().size.y / 2.0f });
	sprite.setPosition({ width / 2.0f, height / 2.0f });
	sprite.setScale({ 4.0f, 4.0f });

	float timerMax = 0.25f;
	float timer = 0.0f;

	float waitTimerMax = 2.25f;
	float waitTimer = waitTimerMax;

	while (window->isOpen()) {
		PollEvents(*window);
		
		timer += 0.1f;
		if (timer >= timerMax) {
			sprite.setTextureRect({ {texWidth, 0}, {32, 32} });

			texWidth += 32;
			if (texture.getSize().x <= texWidth) {
				texWidth = 0;
			} 

			timer = 0.0f;
		}
		// Render
		window->clear(); 

		// Drawing
		window->draw(sprite);

		window->display();
	}

	return 0;
}