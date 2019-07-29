#include "joiner.h"

void Joiner::initialize() {
	uniformObjectBuffers.resize(2);
	uniformObjectBufferMemories.resize(2);

	coordinateObject.modelMatrix = glm::mat4(1.0f);
	coordinateObject.modelMatrix = glm::rotate(coordinateObject.modelMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	coordinateObject.viewMatrix = glm::mat4(1.0f);
	coordinateObject.projectionMatrix = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

	camera.position = glm::vec3(0.0f, -8.0f, -25.0f);
	camera.up = glm::vec3(0.0f, 1.0f, 0.0f);

	camera.pitch = 0.0f;
	camera.yaw = 90.0f;
	camera.front.x = cos(glm::radians(camera.pitch)) * cos(glm::radians(camera.yaw));
	camera.front.y = sin(glm::radians(camera.pitch));
	camera.front.z = cos(glm::radians(camera.pitch)) * sin(glm::radians(camera.yaw));
	camera.front = glm::normalize(camera.front);

	lightObject.lightPosition = glm::vec3(0.0f, -10.0f, -30.0f);
	lightObject.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	coordinateObject.viewMatrix = glm::lookAt(camera.position, camera.position + camera.front, camera.up);
	coordinateObject.projectionMatrix = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
}

void Joiner::initializeUniformBuffers(int swapChainImagesSize) {
    uniformBufferSize = sizeof(CoordinateObject) + sizeof(LightObject);

    for (int x = 0; x < uniformObjectBuffers.size(); x++) {
    	uniformObjectBuffers[x].resize(swapChainImagesSize);
    	uniformObjectBufferMemories[x].resize(swapChainImagesSize);
    }
}

void Joiner::updateUniformBuffers(Input* input) {
	static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    coordinateObject.modelMatrix = glm::rotate(coordinateObject.modelMatrix, glm::radians(0.01f), glm::vec3(0.0f, 0.0f, 1.0f));

	if (input->checkKeyDown(265)) {
		camera.position += 0.005f * camera.front;
	}
	if (input->checkKeyDown(264)) {
		camera.position -= 0.005f * camera.front;
	}
	if (input->checkKeyDown(263)) {
		camera.yaw -= 0.03f;
		camera.front.x = cos(glm::radians(camera.pitch)) * cos(glm::radians(camera.yaw));
		camera.front.y = sin(glm::radians(camera.pitch));
		camera.front.z = cos(glm::radians(camera.pitch)) * sin(glm::radians(camera.yaw));
		camera.front = glm::normalize(camera.front);
	}
	if (input->checkKeyDown(262)) {
		camera.yaw += 0.03f;
		camera.front.x = cos(glm::radians(camera.pitch)) * cos(glm::radians(camera.yaw));
		camera.front.y = sin(glm::radians(camera.pitch));
		camera.front.z = cos(glm::radians(camera.pitch)) * sin(glm::radians(camera.yaw));
		camera.front = glm::normalize(camera.front);
	}

	coordinateObject.viewMatrix = glm::lookAt(camera.position, camera.position + camera.front, camera.up);

	lightObject.viewPosition = camera.position;
}