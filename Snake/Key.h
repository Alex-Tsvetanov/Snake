#pragma once
class Key
{
private:
	int key;
public:
	static const Key UpArrow, RightArrow, DownArrow, LeftArrow;
	Key(int c) : key(c) {}
	bool operator == (const Key& k) const {
		return key == k.key;
	}
};

const Key Key::UpArrow = Key(0x26);
const Key Key::RightArrow = Key(0x27);
const Key Key::DownArrow = Key(0x28);
const Key Key::LeftArrow = Key(0x25);
