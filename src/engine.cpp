#include "engine.h"

void Engine::initialize() {
	initializeWindow();
	initializeVulkan();
	initializePhysicalDevice();
	initializeLogicalDevice();
}

void Engine::initializeWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(1000, 600, "Vulkan-Phong", nullptr, nullptr);
}

void Engine::initializeVulkan() {
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.apiVersion = VK_API_VERSION_1_1;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

void Engine::initializePhysicalDevice() {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	physicalDevice = devices[0];
}

void Engine::initializeLogicalDevice() {
	uint32_t queueFamilyIndex = -1;
	uint32_t queuePresentIndex = -1;
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

	for (int x = 0; x < queueFamilies.size() && queueFamilyIndex == -1; x++) {
		if (queueFamilies[x].queueCount > 0 && queueFamilies[x].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			queueFamilyIndex = x;
		}

    	VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, x, surface, &presentSupport);

        if (queueFamilies[x].queueCount > 0 && presentSupport) {
            queuePresentIndex = x;
        }
	}

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {queueFamilyIndex, queuePresentIndex};

	float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        
        queueCreateInfos.push_back(queueCreateInfo);
    }

	VkPhysicalDeviceFeatures deviceFeatures = {};

	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;
    createInfo.enabledLayerCount = 0;

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice) != VK_SUCCESS) {
	    throw std::runtime_error("failed to create logical device!");
	}
	vkGetDeviceQueue(logicalDevice, queueFamilyIndex, 0, &graphicsQueue);
	vkGetDeviceQueue(logicalDevice, queuePresentIndex, 0, &presentQueue);
}

void Engine::start() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void Engine::quit() {
	vkDestroyDevice(logicalDevice, nullptr);
	vkDestroySurfaceKHR(instance, surface, nullptr);
	vkDestroyInstance(instance, nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();
}