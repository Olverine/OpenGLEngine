#pragma once
#include <string>
#include <SDL.h>
#include <stdint.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	~Display();

	void swapBuffers();
	bool isClosed();

private:

	bool closed;
};

Uint32 getMouseState(int*, int*);
void setMousePosition(int, int);

int getWindowWidth();
int getWindowHeight();