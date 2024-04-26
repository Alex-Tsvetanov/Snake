#pragma once
struct FinalScore
{
	int length;
	enum Result {
		Win,
		Loss
	};
	Result causeOfEnd;
	FinalScore(int length, Result end) {
		this->length = length;
		this->causeOfEnd = end;
	}
};

