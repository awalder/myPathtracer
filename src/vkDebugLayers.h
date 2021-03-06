#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

#include "vkTools.h"

class vkDebugAndExtensions
{
    public:
    void init();

    std::vector<const char*> getRequiredInstanceExtensions() const;
    std::vector<const char*> getRequiredDeviceExtensions() const;
    std::vector<const char*> getRequiredInstanceLayers() const;

    void setupDebugMessenger(VkInstance m_instance);
    void cleanUp(VkInstance m_instance);

    struct LayerProperties
    {
        VkLayerProperties                  properties;
        std::vector<VkExtensionProperties> extensions;
    };

    bool isValidationLayersEnabled() const { return m_EnableValidationLayers; };

    private:

    VkDebugUtilsMessengerEXT m_Messenger = VK_NULL_HANDLE;

    // Extensions requested by GLFW and possible debug extensions.
    std::vector<const char*> m_RequiredInstanceExtensions;

    // Platform specific swapchain extension
    //std::vector<const char*> m_RequiredDeviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    std::vector<const char*> m_RequiredDeviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME, VK_NV_RAY_TRACING_EXTENSION_NAME,
        VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME};

    // Validation layer
    std::vector<const char*> m_RequiredInstanceLayers = {};

    static VKAPI_ATTR VkBool32 VKAPI_CALL
                               debug_messenger_callback(VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT             messageType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
                                                        void*                                       userData);

    VkResult createDebugUtilsMessengerEXT(VkInstance                                m_instance,
                                          const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                          const VkAllocationCallbacks*              pAllocator,
                                          VkDebugUtilsMessengerEXT*                 pMessenger);
    void     destroyDebugUtilsMessengerEXT(VkInstance                   m_instance,
                                           VkDebugUtilsMessengerEXT     messenger,
                                           const VkAllocationCallbacks* pAllocator);

    static const char* debugAnnotObjectToString(const VkObjectType object_type);

    //#if NDEBUG
#if 0  // Permanently on for now
    const bool m_EnableValidationLayers = false;
#else
    const bool m_EnableValidationLayers = true;
#endif  // NDEBUG
};
