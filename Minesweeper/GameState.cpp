#include <string>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>


namespace Game {

	GameState::GameState(gameDataRef data)
		: 
		data(data),
		gameOverText("GameOver", data->assets.getFont("font"), 42),
		winText("Win!", data->assets.getFont("font"), 42)
	{
		gameOverText.setOutlineThickness(2.0f);
		gameOverText.setOutlineColor(sf::Color::Black);
		gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2, gameOverText.getGlobalBounds().height / 2);
		gameOverText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.225f);

		winText.setOutlineThickness(2.0f);
		winText.setOutlineColor(sf::Color::Black);
		winText.setOrigin(winText.getGlobalBounds().width / 2, winText.getGlobalBounds().height / 2);
		winText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.225f);

		grid = new Grid(data, GRID_SIZE, NUM_OF_MINES);
	}

	GameState::~GameState() {
		delete grid;
	}

	void GameState::init() {
		std::cout << "Game state" << std::endl;
	}

	void GameState::handleInput() {
		sf::Event event;
		while (data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				data->window.close();
			}
			

			if (!gameOver) {

				if (sf::Event::MouseButtonPressed == event.type) {
				
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
						sf::Mouse::getPosition(data->window).x >= 0 && sf::Mouse::getPosition(data->window).x < SCREEN_WIDTH &&
						sf::Mouse::getPosition(data->window).y >= 0 && sf::Mouse::getPosition(data->window).y < SCREEN_HEIGHT) {

						grid->open(sf::Mouse::getPosition(data->window).x, sf::Mouse::getPosition(data->window).y);

					} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) &&
							   sf::Mouse::getPosition(data->window).x >= 0 && sf::Mouse::getPosition(data->window).x < SCREEN_WIDTH &&
							   sf::Mouse::getPosition(data->window).y >= 0 && sf::Mouse::getPosition(data->window).y < SCREEN_HEIGHT) {

						grid->setFlag(sf::Mouse::getPosition(data->window).x, sf::Mouse::getPosition(data->window).y);

					}

				}

			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				gameOver = false;
				win = false;
				delete grid;
				grid = new Grid(data, GRID_SIZE, NUM_OF_MINES);
			}

		}

	}

	void GameState::update(float dt) {

		if (grid->openedMine()) {
			gameOver = true;
		}

		if (grid->checkWin()) {
			win = true;
		}

	}

	void GameState::draw() {

		data->window.clear(sf::Color::White);

		grid->drawGrid();

		if (gameOver) {
			data->window.draw(gameOverText);
		}

		if (win) {
			data->window.draw(winText);
		}

		data->window.display();
	
	}

}