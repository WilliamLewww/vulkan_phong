#define GLFW_INCLUDE_VULKAN

#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

struct Camera {
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	float pitch;
	float yaw;
};

struct CoordinateObject {
    alignas(16) glm::mat4 modelMatrix;
    alignas(16) glm::mat4 viewMatrix;
    alignas(16) glm::mat4 projectionMatrix;
};

struct LightObject {
    alignas(16) glm::vec3 lightPosition;
    alignas(16) glm::vec3 lightColor;

    alignas(16) glm::vec3 viewPosition;
};

class Joiner {
private:
public:
	VkDeviceSize uniformBufferSize;

	std::vector<std::vector<VkBuffer>> uniformObjectBuffers;
	std::vector<std::vector<VkDeviceMemory>> uniformObjectBufferMemories;

	Camera camera;
	CoordinateObject coordinateObject;
	LightObject lightObject;

	void initialize();
	void initializeUniformBuffers(int swapChainImagesSize);
};