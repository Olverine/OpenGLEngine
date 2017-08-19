#pragma once
#include "GameObject.h"
#include "Engine.h"

#include <lua.hpp>
//#include <LuaState.h>
#include <LuaBridge.h>

class LuaComponent :
	public Component
{
public:
	LuaComponent(char* script);
	~LuaComponent();

	void printLuaError(lua_State* state);

	void update(float);
	void render();
	void draw(glm::mat4 view, glm::mat4 projection);

private:
	lua_State *L;

	//void setPosition(float, float, float);

	//lua::State state;
};

