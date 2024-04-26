#pragma once
#include "Key.h"
#include <stdlib.h>
#include <thread>
#include <chrono>
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
#include <conio.h>
#include "EndOfScreenException.h"
#include "ColorfulConsole.h"

class Screen
{
protected:
	int frames_per_second;
	int draws_per_update; // 0 to disable updates
	std::atomic<bool> active;
	ColorfulConsole console;
	void* dataToEndScreen;
public:
	Screen(int fps, int dpu) {
		frames_per_second = fps;
		draws_per_update = dpu;
		active = false;
		dataToEndScreen = nullptr;
	}

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void onKeyPressed(Key) = 0;
	virtual void setDataFromPreviousScreen(void*) = 0;

	void clearScreen() {
		console.clear();
	}

	void continousDrawing() {
		try {
			int draws = 0;
			while (active) {
				draw();
				draws++;
				std::this_thread::sleep_for(1000000us / frames_per_second);
				if (draws == draws_per_update) {
					update();
					draws = 0;
				}
			}
		}
		catch (EndOfScreenException& e) {
			active = false;
			dataToEndScreen = e.customDataForNextScreen;
		}
	}

	void start() {
		active = true;
		// background thread for drawing
		std::thread([this]() { this->continousDrawing(); }).detach(); // deatch the thread from the main thread

		// main thread (listening for commands)
		try {
			while (active) {
				// wait for a key down
				int c = _getch();
				Key keyPressed = Key(-1, -1);
				if (c && c != 224)
				{
					keyPressed = Key(c);
				}
				else
				{

					keyPressed = Key(c, _getch());
				}
				this->onKeyPressed(keyPressed);
			}
		}
		catch (EndOfScreenException& e) {
			this->active = false;
			dataToEndScreen = e.customDataForNextScreen;
		}
		throw EndOfScreenException(dataToEndScreen);
	}
	void stop() {
		active = false;
	}
};

