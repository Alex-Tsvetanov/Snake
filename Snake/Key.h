#pragma once
class Key
{
private:
	int c1, c2;
public:
	static const Key UpArrow, RightArrow, DownArrow, LeftArrow;
	Key(int c) : c1(-1), c2(c) {}
	Key(int a, int b) : c1(a), c2(b) {}
	bool operator == (const Key& k) const {
		return c1 == k.c1 && c2 == k.c2;
	}
};

const Key Key::UpArrow = Key(224, 72);
const Key Key::RightArrow = Key(224, 77);
const Key Key::DownArrow = Key(224, 80);
const Key Key::LeftArrow = Key(224, 75);
