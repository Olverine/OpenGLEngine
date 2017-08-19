#pragma once
#include <string>
#include <SDL.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	~Display();

	void swapBuffers();
	bool isClosed();

private:
	SDL_Window* window;
	SDL_GLContext context;

	bool closed;
};

