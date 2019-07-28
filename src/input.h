#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

class Input {
private:
	static std::vector<int> keyDownList;
	
	double mousePositionX, mousePositionY;
public:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursorPositionCallback(GLFWwindow* window, double x, double y);
	
	bool checkKeyDown(int key);
	glm::vec2 getMousePosition();
};