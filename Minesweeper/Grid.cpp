#include "Grid.hpp"
#include <cassert>
#include <iostream>

namespace Game {

	Grid::Grid(gameDataRef data, int size, int numOfMines) 
		:
		data(data),
		gridSize(size),
		cellWidth(SCREEN_WIDTH / (float)size),
		closedCell(sf::Vector2f(cellWidth, cellWidth)),
		openCell(sf::Vector2f(cellWidth, cellWidth)),
		mine(data->assets.getTexture("mine")),
		flag(data->assets.getTexture("flag")), 
		number("0", data->assets.getFont("font"), 20)
	{
		closedCell.setOutlineThickness(1.0f);
		closedCell.setOutlineColor(sf::Color::Black);
		closedCell.setFillColor(sf::Color(185, 185, 185));

		openCell.setOutlineThickness(1.0f);
		openCell.setOutlineColor(sf::Color::Black);
		openCell.setFillColor(sf::Color(100, 100, 100));

		mine.setOrigin(mine.getGlobalBounds().width / 2, mine.getGlobalBounds().height / 2);
		float mineScale = (cellWidth * 0.8f) / mine.getGlobalBounds().width;
		mine.setScale(mineScale, mineScale);

		flag.setOrigin(flag.getGlobalBounds().width / 2, flag.getGlobalBounds().height / 2);
		float flagScaleX = (cellWidth * 0.8f) / flag.getGlobalBounds().width;
		float flagScaleY = (cellWidth * 0.8f) / flag.getGlobalBounds().height;
		flag.setScale(flagScaleX, flagScaleY);

		number.setOrigin(number.getGlobalBounds().width / 2, number.getGlobalBounds().height / 2);
		float numberScaleX = (cellWidth * 0.6f) / number.getGlobalBounds().width;
		float numberScaleY = (cellWidth * 0.6f) / number.getGlobalBounds().height;
		number.setScale(numberScaleX, numberScaleY);


		//Allocate cell array
		cells = new Cell[gridSize * gridSize];

		//Set mines randomly
		for (int i = 0; i < numOfMines; i++) {
			bool* mine = &cells[rand() % (gridSize * gridSize)].mine;
			if (*mine) {
				i--;
			} else {
				*mine = true;
			}
		}

		//Calculate number of mines as neighbors for every cell
		for (int i = 0; i < gridSize; i++) {
			for (int j = 0; j < gridSize; j++) {

				if (getCell(i, j)->mine) {
					continue;
				}

				for (int k = (i == 0 ? 0 : -1); k <= (i == gridSize - 1 ? 0 : 1); k++) {
					for (int l = (j == 0 ? 0 : -1); l <= (j == gridSize - 1 ? 0 : 1); l++) {

						if (getCell(i + k, j + l)->mine) {
							getCell(i, j)->neighbors++;
						}

					}
				}

			}
		}

	}

	Grid::~Grid() {
		delete[] cells;
	}


	void Grid::open(int x, int y) {

		int gridX = int(x / cellWidth);
		int gridY = int(y / cellWidth);

		if (!getCell(gridX, gridY)->open) {

			if (getCell(gridX, gridY)->mine) {

				hitMine = true;
				this->setOpen(gridX, gridY);

			} else if (getCell(gridX, gridY)->neighbors == 0) {

				this->floodFill(gridX, gridY);

			} else {

				this->setOpen(gridX, gridY);

			}

		}

	}

	void Grid::setFlag(int x, int y) {
		int gridX = int(x / cellWidth);
		int gridY = int(y / cellWidth);

		if (!getCell(gridX, gridY)->open && !getCell(gridX, gridY)->flag) {

			getCell(gridX, gridY)->flag = true;
			flagCounter++;

		} else if (!getCell(gridX, gridY)->open && getCell(gridX, gridY)->flag) {

			getCell(gridX, gridY)->flag = false;
			flagCounter--;

		}
	}

	void Grid::drawGrid() {
		for (int i = 0; i < gridSize; i++) {
			for (int j = 0; j < gridSize; j++) {

				if (getCell(i, j)->open) {

					openCell.setPosition(i * cellWidth, j * cellWidth);
					data->window.draw(openCell);

					if (getCell(i, j)->mine) {

						mine.setPosition(i * cellWidth + cellWidth / 2, j * cellWidth + cellWidth / 2);
						data->window.draw(mine);

					} else if (getCell(i, j)->neighbors != 0) {

						number.setString(std::to_string(getCell(i, j)->neighbors));
						number.setPosition(i * cellWidth + cellWidth / 2, j * cellWidth + cellWidth / 2);
						data->window.draw(number);

					}

				} else {

					closedCell.setPosition(i * cellWidth, j * cellWidth);
					data->window.draw(closedCell);

					if (getCell(i, j)->flag) {

						flag.setPosition(i * cellWidth + cellWidth / 2, j * cellWidth + cellWidth / 2);
						data->window.draw(flag);

					}

				}

			}
		}
	}

	bool Grid::checkWin() {
		if (((gridSize * gridSize) - cellsOpenedCounter) == NUM_OF_MINES && flagCounter == NUM_OF_MINES) {
			return true;
		} else {
			return false;
		}
	}

	void Grid::floodFill(int gridX, int gridY) {
		if (!getCell(gridX, gridY)->open) {

			this->setOpen(gridX, gridY);

			if (getCell(gridX, gridY)->neighbors == 0) {

				for (int i = (gridX == 0 ? 0 : -1); i <= (gridX == gridSize - 1 ? 0 : 1); i++) {
					for (int j = (gridY == 0 ? 0 : -1); j <= (gridY == gridSize - 1 ? 0 : 1); j++) {
						this->floodFill(gridX + i, gridY + j);
					}
				}

			}
		}
	}


	Grid::Cell* Grid::getCell(int x, int y) {
		assert(x >= 0);
		assert(x < gridSize);
		assert(y >= 0);
		assert(y < gridSize);
		return &cells[y * gridSize + x];
	}


	void Grid::setOpen(int gridX, int gridY) {
		getCell(gridX, gridY)->open = true;
		cellsOpenedCounter++;
		if (getCell(gridX, gridY)->flag) {
			flagCounter--;
		}
	}

}