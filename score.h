#pragma once
class Score
{
private:
	bool render();
	bool isshow = true;
	bool isrun = true;
public:
	bool update();
};

extern Score score;