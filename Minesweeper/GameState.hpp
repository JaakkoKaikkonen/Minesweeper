#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Grid.hpp"


namespace Game {

	class GameState : public State
	{
	public:
		GameState(gameDataRef data);
		~GameState();

		void init();

		void handleInput();
		void update(float dt);
		void draw();

	private:
		gameDataRef data;

		Grid* grid = nullptr;

		sf::Text gameOverText;

		sf::Text winText;

		bool gameOver = false;

		bool win = false;
	};

}