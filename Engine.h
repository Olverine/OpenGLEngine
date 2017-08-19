#pragma once

#include "GameObject.h"

#if defined(_WIN32)

#include <Windows.h>

#endif

const int ERROR_COLOR = 28;
const int SUCCESS_COLOR = 26;
const int RESET_COLOR = 7;

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

std::vector<GameObject*> getObjects();
void printError(const char* err);
void printColored(const char* msg, int color);
void printSuccess(const char* msg);
void printSuccess();