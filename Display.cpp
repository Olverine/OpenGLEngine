#include "Display.h"
#include "Engine.h"
#include <iostream>
#include <GL/glew.h>

using namespace std;

Display::Display(int width, int height, const std::string& title)
{
	cout << "Initializing SDL: ";
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printError(strcat("error: ", SDL_GetError()));
	}
	else {
		printSuccess();

		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
		if (window == NULL) {
			printError(strcat("SDL Error: ", SDL_GetError()));
		}
		else {
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			context = SDL_GL_CreateContext(window);
		}
	}

	cout << "Initializing glew: ";
	GLenum status = glewInit();
	if (status != GLEW_OK) {
		printError("failed");
	}
	else {
		printSuccess();
	}

	cout << endl;
}

Display::~Display()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Display::isClosed() {
	return closed;
}

void Display::swapBuffers() {
	SDL_GL_SwapWindow(window);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			closed = true;
		}
	}
}
