#include <iostream>
#include <random>
#include <chrono>

#include <SFML/Graphics.hpp>



int main() {
	unsigned int width = 640;
	unsigned int height = 360;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Tutorials");
	window->setFramerateLimit(60);

	sf::Image image;
	image.resize({ width, height });

	sf::Texture texture(image.getSize());

	sf::Sprite sprite(texture);

	unsigned int size = width * height;
	
	unsigned int* board = new unsigned int[size];
	unsigned int* neighbors = new unsigned int[size];

	int dir[8] = { 1, int(width) + 1, int(width), int(width) - 1,
		-1, -int(width) - 1, -int(width), -int(width) + 1 };

	std::default_random_engine randEng;
	int seed = std::chrono::steady_clock::now().time_since_epoch().count();
	randEng.seed(seed);

	for (unsigned int i = 0; i < size; ++i) {
		std::uniform_int_distribution onOff(0, 1);
		board[i] = onOff(randEng);
		neighbors[i] = 0;
	}

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

		for (unsigned int i = 0; i < size; ++i) {
			if (board[i] == 0) {
				continue;
			}
			for (int j = 0; j < 8; ++j) {
				int index = i + dir[j];
				if (index < 0) {
					index += size;
				}
				else if (index > size - 1) {
					index -= size;
				}
				++neighbors[index];
			}
		}

		for (unsigned int i = 0; i < size; ++i) {
			if (board[i] == 0 && neighbors[i] == 3) {
				board[i] = 1;
			}
			else if (board[i] == 1 && (neighbors[i] < 2 || neighbors[i] > 3)) {
				board[i] = 0;
			}

			sf::Color color = board[i] == 1 ? sf::Color::White : sf::Color::Black;

			unsigned int x = i % width;
			unsigned int y = floor(i / width);

			sf::Vector2u pos = sf::Vector2u(x, y);

			image.setPixel(pos, color);

			neighbors[i] = 0;
		}

		texture.update(image);

		// Render
		window->clear(); 

		// Drawing
		window->draw(sprite);

		window->display();
	}

	delete[] board;
	delete[] neighbors;
	delete window;
	return 0;
}