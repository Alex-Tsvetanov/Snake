#pragma once
#include "Key.h"
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <condition_variable>
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

class Screen
{
private:
	int fps;
	std::condition_variable cv;
	std::mutex cv_m;
public:
	virtual void invalidateView() = 0;
	virtual void draw() const = 0;
	virtual void update() = 0;
	virtual void onKeyPressed(Key) = 0;

	void clearScreen() const {
		system("cls");
	}

	void start() {
		// background thread
		std::thread gameplay(
			[this]() {
				try {
					while(true) {
						std::unique_lock<std::mutex> lk(cv_m);
						this->draw();
						cv.wait_for(lk, (1000000us / fps));
					}
				}
				catch (...) {
					return;
				}
			}
		);
		gameplay.detach(); // deatch the thread from the main thread

		// main thread (listening for commands)
		while (true )
	}
};

