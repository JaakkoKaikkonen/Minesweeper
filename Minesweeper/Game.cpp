#include "Game.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace Game {

	Game::Game(int width, int height, std::string title) {

		sf::Image icon;
		icon.loadFromFile(TOP_ICON_FILEPATH);

		data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

		data->window.setPosition(sf::Vector2i(500, 100));

		data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		srand((unsigned int)time(NULL));

		//Load Resources ----------------------------------------------------------------------

		//Textures
		data->assets.loadTexture("mine", MINE_TEXTURE_FILEPATH);
		data->assets.loadTexture("flag", FLAG_TEXTURE_FILEPATH);

		//Sounds

		//Fonts
		data->assets.loadFont("font", FONT_FILEPATH);

		//-------------------------------------------------------------------------------------

		data->gameState = new GameState(data);

		this->run();
	}

	void Game::run() {
		float newTime, frameTime;

		float currentTime = this->clock.getElapsedTime().asSeconds();

		float accumulator = dt;


		while (this->data->window.isOpen()) {

			newTime = this->clock.getElapsedTime().asSeconds();

			frameTime = newTime - currentTime;

			currentTime = newTime;

			if (frameTime > 0.15f) {
				frameTime = 0.15f;
			}

			accumulator += frameTime;

			while (accumulator >= dt)
			{
				data->gameState->handleInput();
				data->gameState->update(dt);

				data->gameState->draw();

				accumulator -= dt;
			}

	
		}


	}


}