#include "Application.h"
#include "AnimatedText.h"
#include <SFML/Graphics.hpp>
#include <sstream>

namespace mo {
	Application* Application::m_instance = nullptr;

	Application::Application() {}

	Application* Application::instance() {
		if (m_instance == nullptr) {
			m_instance = new Application;
		}
		return m_instance;
	}

	int Application::run() {
		setlocale(LC_ALL, "Russian");

		while (true) {
			std::cout << "Введите строку: ";
			std::string text;
			std::getline(std::cin >> std::ws, text);

			std::cout << "Введите количество секунд: ";
			unsigned char duration;
			scanf_s("%hhd", &duration);

			AnimatedText animatedText(text, duration);

			sf::RenderWindow window(
				sf::VideoMode(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT),
				"Animated Text",
				sf::Style::Close);
			window.setFramerateLimit(60);

			sf::Font font;
			font.loadFromFile("Aloreta_Marthin.otf");

			sf::Text textView;
			textView.setFont(font);
			textView.setCharacterSize(50);
			textView.setFillColor(sf::Color::Black);

			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						window.close();
					}
				}

				if (!window.isOpen()) {
					break;
				}

				window.clear(sf::Color::White);

				if (animatedText.update()) {
					textView.setString(sf::String(animatedText.getCurrentText()));

					// центрируем текст
					sf::FloatRect textViewRect = textView.getLocalBounds();
					textView.setOrigin(textViewRect.left + textViewRect.width / 2.0f,
						textViewRect.top + textViewRect.height / 2.0f);
					textView.setPosition(sf::Vector2f(
						MAIN_WINDOW_WIDTH / 2.0f, MAIN_WINDOW_HEIGHT / 2.0f));
				}

				window.draw(textView);
				window.display();
			}
		}

		return 0;
	}
}