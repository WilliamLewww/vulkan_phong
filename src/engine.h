#define GLFW_INCLUDE_VULKAN

#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <fstream>
#include <vector>
#include <set>
#include <array>
#include <iostream>

class Engine {
private:
	GLFWwindow* window;
	VkSurfaceKHR surface;

	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;

	VkPhysicalDevice physicalDevice;
	VkDevice logicalDevice;

	uint32_t queueFamilyIndex;
	uint32_t queuePresentIndex;
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;

	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	VkBuffer positionVertexBuffer;
	VkDeviceMemory positionVertexBufferMemory;

	VkBuffer positionIndexBuffer;
	VkDeviceMemory positionIndexBufferMemory;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	size_t currentFrame = 0;

	void initializeWindow();
	void initializeVulkan();
	void initializePhysicalDevice();
	void initializeLogicalDevice();
	void initializeSwapChain();
	void initializeImageViews();
	void initializeRenderPass();
	void initializeGraphicsPipeline();
	void initializeFramebuffers();
	void initializeCommandPool();

	void initializeVertexBuffer();
	void initializeIndexBuffer();

	void initializeCommandBuffer();
	void initializeSyncObjects();

	void render();

	std::vector<char> readFile(const std::string& filepath);
	VkShaderModule createShaderModule(const std::vector<char>& code);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
public:
	void initialize();
	void start();
	void quit();
};
