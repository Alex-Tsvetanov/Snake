#pragma once
class Point
{
private:
	int x;
	int y;
public:
	Point() : x(0), y(0) {}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	bool operator == (const Point& p) const {
		return x == p.x && y == p.y;
	}
};

