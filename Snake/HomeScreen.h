#pragma once
#include "Screen.h"
#include <iostream>

class HomeScreen : public Screen
{
public:
	HomeScreen() : Screen(10, 0) { }
	// Inherited via Screen
	void draw() override {
		clearScreen();
		console.append("Hello, player! This is the game Snake.\nPress any key to start it.\n", FOREGROUND_WHITE);
		console.finalize();
	}
	void update() override { }
	void onKeyPressed(const Key) override {
		this->active = false;
		throw EndOfScreenException(nullptr);
	}

	void setDataFromPreviousScreen(void*) override {}
};

