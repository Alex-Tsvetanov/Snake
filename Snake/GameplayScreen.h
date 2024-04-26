#pragma once
#include "Screen.h"
#include "Snake.h"
#include "FinalScore.h"
#include <iostream>

class GameplayScreen : public Screen
{
private:
	Direction latestDirection;
	Snake snake;
	Grid grid;
public:
	GameplayScreen() : Screen(10, 2) {
		latestDirection = Direction::Right;
		snake.setHead(Point(0, 0));
		grid = Grid(20, 20);
		for (int i = 0; i < 10; i++) {
			grid.addApple(Point(rand() % 20, rand() % 20));
		}
	}
	// Inherited via Screen
	void draw() override {
		clearScreen();
		console.append("Snake length: ", FOREGROUND_WHITE);
		char buff[30];
		console.append(_itoa(snake.getSize(), buff, 10), FOREGROUND_WHITE);
		console.append("\n", FOREGROUND_WHITE);
		for (int x = 0; x < grid.sizeX() + 2; x++) {
			console.append("-", FOREGROUND_WHITE);
		}
		console.append("\n", FOREGROUND_WHITE);
		for (int y = 0; y < grid.sizeY(); y++) {
			console.append("|", FOREGROUND_WHITE);
			for (int x = 0; x < grid.sizeX(); x++) {
				if (snake.isHead(Point(x, y))) {
					console.append('o', FOREGROUND_RED);
				}
				else if (snake.isTail(Point(x, y))) {
					console.append('o', FOREGROUND_BLUE);
				}
				else if (grid.hasAppleOn(Point(x, y))) {
					console.append('+', FOREGROUND_GREEN);
				}
				else {
					console.append(" ", FOREGROUND_WHITE);
				}
			}
			console.append("|\n", FOREGROUND_WHITE);
		}
		for (int x = 0; x < grid.sizeX() + 2; x++) {
			console.append("-", FOREGROUND_WHITE);
		}
		console.append("\n", FOREGROUND_WHITE);
		console.finalize();
	}
	void update() override {
		try {
			snake.move(latestDirection, grid);
		}
		catch (const DeadSnake&) {
			this->active = false;
			console.append("The end.\nPress any key to continue.", FOREGROUND_WHITE);
			console.finalize();
			throw EndOfScreenException(new FinalScore(snake.getSize(), FinalScore::Result::Loss));
		}
		if (grid.numberOfApples() == 0) {
			this->draw();
			this->active = false;
			console.append("You won.\nPress any key to continue.", FOREGROUND_WHITE);
			console.finalize();
			throw EndOfScreenException(new FinalScore(snake.getSize(), FinalScore::Result::Win));
		}
	}
	void onKeyPressed(const Key keyPressed) override {
		if (keyPressed == Key::UpArrow) {
			latestDirection = Direction::Up;
		}
		else if (keyPressed == Key::RightArrow) {
			latestDirection = Direction::Right;
		}
		else if (keyPressed == Key::DownArrow) {
			latestDirection = Direction::Down;
		}
		else if (keyPressed == Key::LeftArrow) {
			latestDirection = Direction::Left;
		}
	}
	void setDataFromPreviousScreen(void*) override {}
};

