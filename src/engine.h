#define GLFW_INCLUDE_VULKAN

#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <set>
#include <iostream>

class Engine {
private:
	GLFWwindow* window;
	VkSurfaceKHR surface;

	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;

	VkPhysicalDevice physicalDevice;
	VkDevice logicalDevice;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	void initializeWindow();
	void initializeVulkan();
	void initializePhysicalDevice();
	void initializeLogicalDevice();
public:
	void initialize();
	void start();
	void quit();
};