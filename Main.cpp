#include <iostream>
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>

#include "Display.h"
#include "Mesh.h"
#include "Shader.h"
#include "Engine.h"
#include "Camera.h"
#include "JoystickRotator.h"
#include "Input.h"
#include "CameraFly.h"
#include "Terrain.h"

using namespace std;
using namespace glm;

std::vector<GameObject*> objects;

int main(int argc, char* argv[]) {
	Display display(1366, 768, "Game");

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	Shader shader("shaders/basic");
	shader.setColor(glm::vec3(1, 0, 1));

	Vertex vertices[] = {
		glm::vec3(-1,-1,0),
		glm::vec3(0,1,0),
		glm::vec3(1,-1,0)
	};

	GameObject* cam = new GameObject();
	cam->addComponent(new Camera());
	cam->addComponent(new CameraFly());
	cam->position = glm::vec3(0, 0, -2);
	objects.push_back(cam);

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	mesh.setShader(&shader);

	GameObject* triangle = new GameObject();
	triangle->name = "Triangle";
	triangle->addComponent(&mesh);
	
	JoystickRotator rot = JoystickRotator();
	triangle->addComponent(&rot);

	objects.push_back(triangle);

	GameObject* terrain = new GameObject();
	Terrain* terrainComp = new Terrain("resources/heightmap/1.bmp");
	terrainComp->setShader(new Shader("shaders/terrain"));
	terrain->scale.y = 0.2f;
	terrain->addComponent(terrainComp);
	objects.push_back(terrain);
	

	float now;
	float prev;

	now = GetTickCount();

	while(true) {
		prev = now;
		now = GetTickCount();

		float deltaTime = (now - prev) / 1000;
		if (deltaTime == 0) {
			//deltaTime = 0.0001f;
		}else if(deltaTime > 1000){
			deltaTime = 0;
		}

		glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update gamepad states
		Input::update();

		// Update every component
		for each (GameObject* obj in objects)
		{
			for each (Component* comp in obj->components)
			{
				comp->update(deltaTime);
			}
		}

		// Call render() on every component
		for each (GameObject* obj in objects)
		{
			for each (Component* comp in obj->components)
			{
				comp->render();
			}
		}

		display.swapBuffers();
	}

	system("pause");
	return EXIT_SUCCESS;
}

vector<GameObject*> getObjects() {
	return objects;
}

void printColored(const char * msg, int color)
{
#if defined (_WIN32)
	SetConsoleTextAttribute(hConsole, color);
#endif
	cout << msg << endl;
#if defined (_WIN32)
	SetConsoleTextAttribute(hConsole, RESET_COLOR);
#endif
}

void printError(const char * err) { printColored(err, ERROR_COLOR); }

void printSuccess(const char * msg) { printColored(msg, SUCCESS_COLOR); }

void printSuccess() { printSuccess("success!"); }