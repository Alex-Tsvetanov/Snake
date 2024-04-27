#pragma once
#include "Screen.h"
#include <iostream>

class HomeScreen : public Screen
{
public:
	HomeScreen() : Screen(5s) { }
	// Inherited via Screen
	void draw() override {
		clearScreen();
		console.append("Hello, player! This is the game Snake.\nPress any key to start it.\n(In 5 seconds the game will start automatically)", FOREGROUND_WHITE);
		console.finalize();
	}
	void update() override {
		throw EndOfScreenException(nullptr);
	}
	void onKeyPressed(const Key) override {
		throw EndOfScreenException(nullptr);
	}

	void setDataFromPreviousScreen(void*) override {}
};

