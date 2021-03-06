#pragma once

#include "Types.h"

#include <vector>
#include <vulkan/vulkan.h>

namespace Regen {

    struct VulkanSwapchainSupportDetails {
        VkSurfaceCapabilitiesKHR Capabilities;
        std::vector<VkSurfaceFormatKHR> Formats;
        std::vector<VkPresentModeKHR> PresentationModes;
    };

    class Platform;

    class VulkanRenderer {
    public:
        VulkanRenderer( Platform* platform );
        ~VulkanRenderer();

    private:
        VkPhysicalDevice selectPhysicalDevice();
        const bool physicalDeviceMeetsRequirements( VkPhysicalDevice physicalDevice );
        void detectQueueFamilyIndices( VkPhysicalDevice physicalDevice, I32* graphicsQueueIndex, I32* presentationQueueIndex );
        VulkanSwapchainSupportDetails querySwapchainSupport( VkPhysicalDevice physicalDevice );
        void createLogicalDevice( std::vector<const char*>& requiredValidationLayers );
        void createShader( const char* name );
        char* readShaderFile( const char* filename, const char* shaderType, U64* fileSize );
        void createSwapchain();
        void createSwapchainImagesAndViews();
        void createRenderPass();
        void createGraphicsPipeline();
    private:
        Platform* _platform;

        VkInstance _instance;

        VkDebugUtilsMessengerEXT _debugMessenger;

        VkPhysicalDevice _physicalDevice;
        VkDevice _device; // Logical device 
        I32 _graphicsFamilyQueueIndex;
        I32 _presentationFamilyQueueIndex;
        VkQueue _graphicsQueue;
        VkQueue _presentationQueue;

        VkSurfaceKHR _surface;

        U64 _shaderStageCount;
        std::vector<VkPipelineShaderStageCreateInfo> _shaderStages;

        VkSurfaceFormatKHR _swapchainImageFormat;
        VkExtent2D _swapchainExtent;
        VkSwapchainKHR _swapchain;

        std::vector<VkImage> _swapchainImages;
        std::vector<VkImageView> _swapchainImageViews;

        VkRenderPass _renderPass;
        VkPipelineLayout _pipelineLayout;
        VkPipeline _pipeline;
    };
}
