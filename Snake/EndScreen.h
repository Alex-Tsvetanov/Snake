#pragma once
#include "Screen.h"
#include <iostream>
#include "FinalScore.h"

class EndScreen : public Screen
{
	FinalScore* winOrLose;
public:
	EndScreen() : Screen(10, 0) { }
	~EndScreen() { delete this->winOrLose; }
	// Inherited via Screen
	void draw() override {
		clearScreen();
		if (winOrLose->causeOfEnd == FinalScore::Result::Win)
			console.append("Got'em all! Well played, player!\nPress any key to exit.", FOREGROUND_WHITE);
		else {
			console.append("You finished with length of ", FOREGROUND_WHITE);
			char buff[30];
			console.append(_itoa(winOrLose->length, buff, 10), FOREGROUND_WHITE);
			console.append(".\n", FOREGROUND_WHITE);
			console.append("You missed a couple of apples, but well played, player! See you next time.\nPress any key to exit.", FOREGROUND_WHITE);
		}
		console.finalize();
	}
	void update() override { }
	void onKeyPressed(const Key) override {
		this->active = false;
		throw EndOfScreenException(nullptr);
	}
	void setDataFromPreviousScreen(void* win_or_lose) override {
		this->winOrLose = static_cast<FinalScore*>(win_or_lose);
	}
};

