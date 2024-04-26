#pragma once
#include "Screen.h"
#include "Snake.h"
#include <iostream>

class GameplayScreen : public Screen
{
private:
	Direction latestDirection;
	Snake snake;
	Grid grid;
public:
	GameplayScreen() {
		latestDirection = Direction::Right;
		snake.setHead(Point(0, 0));
		grid = Grid(20, 20);
	}
	// Inherited via Screen
	void draw() const override {
		clearScreen();
		for (int x = 0; x < grid.sizeX(); x++) {
			std::cout << "-";
		}
		std::cout << "\n";
		for (int y = 0; y < grid.sizeY(); y++) {
			std::cout << "|";
			for (int x = 0; x < grid.sizeX(); x++) {
				if (snake.isHead(Point(x, y))) {
					std::cout << "@";
				}
				else if (snake.isTail(Point(x, y))) {
					std::cout << "o";
				}
				else if (grid.hasAppleOn(Point(x, y))) {
					std::cout << "+";
				}
				else {
					std::cout << " ";
				}
			}
			std::cout << "|\n";
		}
		for (int x = 0; x < grid.sizeX(); x++) {
			std::cout << "-";
		}
		std::cout << "\n";
		std::cout.flush();
	}
	void update() override {
		try {
			snake.move(latestDirection, grid);
			invalidateView(); // force re-draw immediately on update
		}
		catch (const DeadSnake& e) {
			throw e;
		}
	}
	void onKeyPressed(const Key keyPressed) override {
		if (keyPressed == Key::UpArrow) {
			latestDirection = Direction::Up;
			update();
		}
		else if (keyPressed == Key::RightArrow) {
			latestDirection = Direction::Right;
			update();
		}
		else if (keyPressed == Key::DownArrow) {
			latestDirection = Direction::Down;
			update();
		}
		else if (keyPressed == Key::LeftArrow) {
			latestDirection = Direction::Left;
			update();
		}
	}
};

