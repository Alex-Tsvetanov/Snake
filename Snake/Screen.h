#pragma once
#include "Key.h"
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
#include <conio.h>
#include "EndOfScreenException.h"
#include "ColorfulConsole.h"

class Screen
{
protected:
	enum UpdateStatus {
		Forced,
		Scheduled
	};
	std::atomic<bool> active;
	ColorfulConsole console;
	void* dataToEndScreen;
	UpdateStatus automaicUpdater;
	std::chrono::duration<double, std::micro> delay;
	std::mutex updating;
public:
	Screen(std::chrono::duration<double, std::micro> delayBeforeAutomaticAction) {
		delay = delayBeforeAutomaticAction;
		active = false;
		dataToEndScreen = nullptr;
		automaicUpdater = UpdateStatus::Scheduled;
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
			auto time_for_scheduled_update = std::chrono::steady_clock::now() + delay;
			draw();
			while (active) {
				// an immediate update has been requested
				if (automaicUpdater == UpdateStatus::Forced) {
					std::lock_guard<std::mutex> lk (updating);
					update();
					draw();
					automaicUpdater = UpdateStatus::Scheduled; // reset to automatic updater
					time_for_scheduled_update = std::chrono::steady_clock::now() + delay; // set next time for automatic update
				}
				// no user input enforced immediate action
				else {
					// and the time for automatic move has come
					if (std::chrono::steady_clock::now() >= time_for_scheduled_update) {
						std::lock_guard<std::mutex> lk(updating);
						update();
						draw();
						time_for_scheduled_update = std::chrono::steady_clock::now() + delay; // set next time for automatic update
					}
				}
			}
		}
		catch (EndOfScreenException& e) {
			this->active = false;
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
				for (int key = 0x01; key <= 0xFE; key++) {
					// the key is pressed
					if ((GetAsyncKeyState(key) & 0x0001) != 0) {
						Key keyPressed = Key(key);
						std::lock_guard<std::mutex> lk(updating);
						this->onKeyPressed(keyPressed);
						break;
					}
				}
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

