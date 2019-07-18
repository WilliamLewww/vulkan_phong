#define GLFW_INCLUDE_VULKAN

#pragma once
#include <GLFW/glfw3.h>

class Engine {
private:
	GLFWwindow* window;

	VkInstance instance;

	void initializeWindow();
	void initializeVulkan();
public:
	void initialize();
	void start();
	void quit();
};