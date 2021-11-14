#pragma once
class Timer
{
private:
	bool render();
public:
	bool isshow = true;
	bool update();
};

extern Timer timer;