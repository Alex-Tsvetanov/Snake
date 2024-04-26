#pragma once
#include <list>
#include "Point.h"
#include "Direction.h"
#include "DeadSnake.h"
#include "Grid.h"
#include <algorithm>

class Snake
{
private:
	std::list<Point> cells;
public:
	Snake() { }
	void setHead(const Point& head) {
		if (cells.size() == 0) {
			cells.push_back(head);
		}
		else {
			throw "Snake is not empty.";
		}
	}
	bool isHead(const Point& p) const {
		return cells.front() == p;
	}
	bool isTail(const Point& p) const {
		return !isHead(p) && std::any_of(cells.cbegin(), cells.cend(), [&p](const Point& cell) { return p == cell; });
	}
	int getSize() const {
		return cells.size();
	}
	void move(Direction dir, Grid& grid) {
		Point head = cells.front();
		
		// move the head
		Point moved_head;
		switch (dir) {
		case Direction::Up:
			moved_head = Point(head.getX(), head.getY() - 1);
			break;
		case Direction::Right:
			moved_head = Point(head.getX() + 1, head.getY());
			break;
		case Direction::Down:
			moved_head = Point(head.getX(), head.getY() + 1);
			break;
		case Direction::Left:
			moved_head = Point(head.getX() - 1, head.getY());
			break;
		}

		// if the moved head is going out of the grid
		if (!grid.has(moved_head)) {
			throw DeadSnake();
		}

		const bool did_it_eat_an_apple = grid.hasAppleOn(moved_head);
		
		// check for suicide
		for (const auto& cell : cells) {
			// if no apple is ate, the last element of the tail should be ignored.
			if (!did_it_eat_an_apple && cell == cells.back()) {
				continue;
			}
			if (moved_head == cell) {
				throw DeadSnake();
			}
		}

		// the move didn't kill the snake so let's move it
		cells.push_front(moved_head);

		// no apple is ate, so the last cell of the tail is moved and therefore removed
		if (!did_it_eat_an_apple) {
			cells.pop_back();
		}
		else {
			try {
				grid.eatAppleOn(moved_head);
			}
			catch (AppleNotFound& e) {
				// we fucked up something big times
				exit(1);
			}
		}
	}
};

