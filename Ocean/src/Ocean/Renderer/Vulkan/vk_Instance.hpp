#pragma once

/**
 * @file vk_Instance.hpp
 * @author Evan F.
 * @brief The Vulkan instance for Ocean.
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "Ocean/Types/SmartPtrs.hpp"
#include "Ocean/Types/Strings.hpp"

#include "Ocean/Primitives/Array.hpp"
#include "Ocean/Primitives/Macros.hpp"

#include "Ocean/Renderer/Vulkan/vk_Device.hpp"
#include "Ocean/Renderer/Vulkan/vk_Swapchain.hpp"
#include "vk_Command.hpp"

// std
#include <mutex>

// libs
#include <glad/vulkan.h>

namespace Ocean {

    namespace Splash {

        /**
         * @brief The Vulkan renderer instance that manages all of the Vulkan systems.
         */
        class vkInstance {
        public:
            vkInstance();
            ~vkInstance();

            /**
             * @brief Get the singleton object of vkInstance.
             */
            OC_GET_SINGLETON(vkInstance);

            /**
             * @brief Prepares Vulkan for rendering after instance construction.
             */
            void Prepare();
            /**
             * @brief Clean's up Vulkan before deconstruction.
             */
            void Cleanup();

            /**
             * @brief Get's the Vulkan instance.
             * 
             * @return VkInstance
             */
            OC_INLINE VkInstance Instance() const { return this->m_Instance; }
            /**
             * @brief Get's a Ref to the vkDevice.
             * @details Only returns the first item in m_Devices as it is sorted to assume the first device is the best.
             * 
             * @return const Ref<vkDevice> 
             */
            OC_INLINE const Ref<vkDevice> Device() { return this->m_Devices[0]; }
            /**
             * @brief Get's the instance extensions by value.
             * 
             * @return const DynamicArray<cstring>& 
             */
            OC_INLINE const DynamicArray<cstring>& Extensions() { return this->m_Extensions; }
            /**
             * @brief Initializes the swapchain with the given window surface.
             * 
             * @param surface The VkSurfaceKHR given by the window platform.
             */
            OC_INLINE void InitSwapchain(VkSurfaceKHR surface) { this->m_Swapchain = MakeRef<vkSwapchain>(surface); };
            /**
             * @brief Get's a Ref to the vkSwapchain.
             * 
             * @return const Ref<vkSwapchain>
             */
            OC_INLINE const Ref<vkSwapchain> Swapchain() { return this->m_Swapchain; }

        private:
            /**
             * @brief Get's the physical Vulkan devices and sorts them into m_Devices.
             * @details After getting the physical Vulkan devices, it will sort them into m_Devices from most fit to least fit.
             */
            void GetDevices();

        private:
            OC_NO_COPY(vkInstance);

        private:
            VkInstance m_Instance; /** @brief The Vulkan instance. */

            DynamicArray<cstring> m_Extensions; /** @brief The enabled instance extensions. */
            DynamicArray<cstring> m_Layers; /** @brief The enabled validation layers. */

            DynamicArray<Ref<vkDevice>> m_Devices; /** @brief The list of vkDevice's to use for rendering. */

            /** @todo Make multi-swapchain support for multiple surfaces. */
            Ref<vkSwapchain> m_Swapchain; /** @brief The vkSwapchain that is related to the window. */

            Scope<vkCommandPool> m_CommandPool; /** @brief The vkCommandPool to create vkCommandBuffers and submit commands to. */

        };  // vkInstance

    }   // Splash

}   // Ocean
