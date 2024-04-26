#pragma once
#include <list>
#include "Point.h"
#include "AppleNotFound.h"

class Grid
{
private:
	std::list<Point> apples;
	int size_x;
	int size_y;
public:
	Grid() {
		size_x = 0;
		size_y = 0;
	}
	Grid(int size_x, int size_y) {
		this->size_x = size_x;
		this->size_y = size_y;
	}
	void addApple(const Point& p) {
		apples.push_back(p);
	}
	int numberOfApples() const {
		return apples.size();
	}
	int sizeX() const {
		return size_x;
	}
	int sizeY() const {
		return size_y;
	}
	bool has(const Point& p) const {
		return (0 <= p.getX() && p.getX() < size_x) && (0 <= p.getY() && p.getY() < size_y);
	}
	bool hasAppleOn(const Point& p) const {
		for (const Point& apple : apples) {
			if (apple == p) {
				return true;
			}
		}
		return false;
	}
	void eatAppleOn(const Point& p) {
		for (std::list<Point>::iterator it = apples.begin(); it != apples.end(); it++) {
			if (*it == p) {
				apples.erase(it);
				return;
			}
		}
		throw AppleNotFound();
	}
};

