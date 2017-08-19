#include "LuaComponent.h"
#include <iostream>

using namespace luabridge;

void printMessage(std::string msg) {
	std::cout << msg << std::endl;
}

void setPosition(float x, float y, float z)
{
	//gameObject->setPosition(x, y, z);
	std::cout << x << y << z << std::endl;
} 

LuaComponent::LuaComponent(char * script)
{
	L = luaL_newstate();
	luaL_openlibs(L);


	getGlobalNamespace(L)
		.beginClass<GameObject>("GameObject")
		.addConstructor<void(*)(void)>()
		.addFunction("setPosition", &GameObject::setPosition)
		.endClass();

	getGlobalNamespace(L)
		.addFunction("printMessage", printMessage);


	//getGlobalNamespace(L).addVariable("gameObject", gameObject);

	luaL_dofile(L, "script.lua");
	lua_pcall(L, 0, 0, 0);
	LuaRef s = getGlobal(L, "testString");
	LuaRef n = getGlobal(L, "number");
	setGlobal(L, gameObject, "gameObject");
	std::string luaString = s.cast<std::string>();
	int answer = n.cast<int>();
}

LuaComponent::~LuaComponent()
{
	lua_close(L);
}

void LuaComponent::printLuaError(lua_State * state)
{
}

void LuaComponent::update(float deltaTime)
{
	try {
		LuaRef updateFunction = getGlobal(L, "update");
		updateFunction(deltaTime);
	}
	catch (...) {

	}
}

void LuaComponent::render() {
	try {
		LuaRef renderFunction = getGlobal(L, "render");
		renderFunction();
	}
	catch (...) {
	
	}
}

void LuaComponent::draw(glm::mat4 view, glm::mat4 projection) {
	try {
		LuaRef drawFunction = getGlobal(L, "draw");
		drawFunction();
	}
	catch (...) {

	}
}


