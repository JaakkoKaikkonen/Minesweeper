#pragma once

#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace Game {

	class Grid
	{
	private:
		struct Cell {
			bool mine = false;
			bool open = false;
			bool flag = false;
			int neighbors = 0;
		};


	public:
		Grid(gameDataRef data, int size, int numOfMines);
		~Grid();
		
		void open(int x, int y);

		void setFlag(int x, int y);

		void drawGrid();

		bool checkWin();

		bool openedMine() { return hitMine; }

	private:
		void floodFill(int gridX, int gridY);

		Cell* getCell(int x, int y);

		void setOpen(int gridX, int gridY);

	private:
		gameDataRef data;

		int gridSize;
		float cellWidth;

		Cell* cells = nullptr;

		int cellsOpenedCounter = 0;
		int flagCounter = 0;

		sf::RectangleShape closedCell;
		sf::RectangleShape openCell;
		sf::RectangleShape redCell;

		sf::Sprite mine;
		sf::Sprite flag;
		sf::Sprite cross;

		sf::Text number;
		
		bool hitMine = false;
	};


}