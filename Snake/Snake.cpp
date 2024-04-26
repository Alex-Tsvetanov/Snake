// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Snake.h"
#include "Screen.h"
#include "HomeScreen.h"
#include "GameplayScreen.h"
#include "EndScreen.h"

class ScreenManager
{
private:
	Screen* activeScreen;
	Screen** applicationScreens;
	int screens;
public:
	ScreenManager() {
		screens = 3;
		applicationScreens = new Screen*[screens]{
			new HomeScreen(),
			new GameplayScreen(),
			new EndScreen()
		};
		activeScreen = nullptr;
	}
	void start() {
		void* data = nullptr;
		for (int screenId = 0; screenId < screens; screenId++) {
			activeScreen = applicationScreens[screenId];
			activeScreen->setDataFromPreviousScreen(data);
			try {
				activeScreen->start();
			}
			catch (EndOfScreenException& e) {
				// move to the next screen
				activeScreen->stop();
				data = e.customDataForNextScreen;
			}
		}
	}
};


int main()
{
	ScreenManager app;
	app.start();
}
