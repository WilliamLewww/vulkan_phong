#define GLFW_INCLUDE_VULKAN

#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <fstream>
#include <vector>
#include <set>
#include <chrono>
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
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	VkBuffer positionVertexBuffer;
	VkDeviceMemory positionVertexBufferMemory;

	VkBuffer textureCoordinateVertexBuffer;
	VkDeviceMemory textureCoordinateVertexBufferMemory;

	VkBuffer positionIndexBuffer;
	VkDeviceMemory positionIndexBufferMemory;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;

	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	VkImageView textureImageView;
	VkSampler textureSampler;

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
	void initializeDescriptorSetLayout();
	void initializeGraphicsPipeline();
	void initializeFramebuffers();
	void initializeCommandPool();

	void initializeTextureImage();
	void initializeTextureImageView();
	void initializeTextureSampler();

	void initializeVertexBuffer();
	void initializeIndexBuffer();
	void initializeUniformBuffers();

	void initializeDescriptorPool();
	void initializeDescriptorSets();

	void initializeCommandBuffer();
	void initializeSyncObjects();

	void render();
	void updateUniformBuffer(uint32_t currentImage);

	VkImageView createImageView(VkImage image, VkFormat format);
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	std::vector<char> readFile(const std::string& filepath);
	VkShaderModule createShaderModule(const std::vector<char>& code);
	
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
public:
	void initialize();
	void start();
	void quit();
};
