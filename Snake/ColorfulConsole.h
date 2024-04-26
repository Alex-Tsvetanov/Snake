#pragma once
#include <windows.h>
#include <stdio.h>

// teacher's code
#define FOREGROUND_BLUE      0x0001 // text color contains blue.
#define FOREGROUND_GREEN     0x0002 // text color contains green.
#define FOREGROUND_RED       0x0004 // text color contains red.
#define FOREGROUND_INTENSITY 0x0008 // text color is intensified.
#define BACKGROUND_BLUE      0x0010 // background color contains blue.
#define BACKGROUND_GREEN     0x0020 // background color contains green.
#define BACKGROUND_RED       0x0040 // background color contains red.
#define BACKGROUND_INTENSITY 0x0080 // background color is intensified.

#define FOREGROUND_WHITE     0x0007 // text color contains dark white.
#define FOREGROUND_INTENSIVEWHITE     0x000F // text color contains intensive white

class ColorfulConsole
{
	CHAR_INFO* buffer;
	int row, col;
	int sizeY, sizeX;

	// teacher's code
	void setup_screen(COORD* cd)
	{
		HANDLE hCons;
		CONSOLE_SCREEN_BUFFER_INFO ConsInfo;
		SMALL_RECT rect;
		COORD c1;
		hCons = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hCons, &ConsInfo);
		c1.X = 0;
		c1.Y = 0;
		rect = ConsInfo.srWindow;
		sizeX = ConsInfo.dwMaximumWindowSize.X;
		sizeY = ConsInfo.dwMaximumWindowSize.Y;
		row = 0;
		col = 0;
		buffer = (CHAR_INFO*)calloc(sizeX * sizeY, sizeof(CHAR_INFO));

		if (buffer == nullptr || ReadConsoleOutput(hCons, buffer, /*ConsInfo.dwSize*/ ConsInfo.dwMaximumWindowSize, c1, &ConsInfo.srWindow) == 0) {
			printf("Failed reading %d\n", GetLastError());
			return;
		}
		if (cd != NULL)
			*cd = ConsInfo.dwMaximumWindowSize; // maximum allowable console window size
	}
	// teacher's code
	void put_screen(COORD* cd)
	{
		HANDLE hCons;
		COORD c1;
		CONSOLE_SCREEN_BUFFER_INFO ConsInfo;

		hCons = GetStdHandle(STD_OUTPUT_HANDLE);
		c1.X = 0;
		c1.Y = 0;
		GetConsoleScreenBufferInfo(hCons, &ConsInfo);

		if (WriteConsoleOutput(hCons, buffer, *cd, c1, &ConsInfo.srWindow) == 0) {
			printf("Failed writing\n");
			return;
		}
		return;
	}
public:
	ColorfulConsole() {
		COORD cd;
		setup_screen(&cd);
		row = 0;
		col = 0;
	}
	// teacher's code
	void set_window_title(unsigned short* str)
	{
		SetConsoleTitle((LPCWSTR)str);
		return;
	}

	// teacher's code
	void clear()
	{
		COORD cd;
		int i, j;
		setup_screen(&cd);
		sizeX = cd.X;
		sizeY = cd.Y;
		row = 0;
		col = 0;
		for (j = 0; j < sizeY; j++)
			for (i = 0; i < sizeX; i++) {
				buffer[j * sizeX + i].Char.AsciiChar = 0;
				buffer[j * sizeX + i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
			}
		put_screen(&cd);
		return;
	}

	void append(const char* str, unsigned short color) {
		for (int i = 0; i < strlen(str); i++) {
			if (str[i] == '\n') {
				row++;
				col = 0;
			}
			else {
				buffer[row * sizeX + col].Char.AsciiChar = str[i];
				buffer[row * sizeX + col].Attributes = color;
				row = row + (col + 1) / sizeX;
				col = (col + 1) % sizeX;
			}
		}
	}

	void append(const char ch, unsigned short color) {
		buffer[row * sizeX + col].Char.AsciiChar = ch;
		buffer[row * sizeX + col].Attributes = color;
		row = row + (col + 1) / sizeX;
		col = (col + 1) % sizeX;
	}

	void finalize() {
		COORD cd;
		cd.X = sizeX;
		cd.Y = sizeY;
		put_screen(&cd);
	}
};

