#pragma once
class Timer
{
private:
	bool render();
	bool isshow = true;
	bool isrun = true;
public:
	bool update();
};

extern Timer timer;