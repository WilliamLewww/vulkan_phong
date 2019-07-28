#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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
	Camera camera;
	CoordinateObject coordinateObject;
	LightObject lightObject;
};