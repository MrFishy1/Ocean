#include "vk_Command.hpp"

#include "Ocean/Types/SmartPtrs.hpp"
#include "Ocean/Types/Strings.hpp"

#include "Ocean/Primitives/Exceptions.hpp"

#include "Ocean/Renderer/Vulkan/vk_Vulkan.hpp"
#include "Ocean/Renderer/Vulkan/vk_Instance.hpp"

// libs
#include <glad/vulkan.h>

namespace Ocean {

    namespace Splash {

        vkCommandPool::vkCommandBuffer::vkCommandBuffer(VkCommandPool pool, b8 primary) :
            m_ParentPool(pool),
            m_Buffer(VK_NULL_HANDLE)
        {
            const VkCommandBufferAllocateInfo bufferInfo {
                VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                nullptr,
                this->m_ParentPool,
                (primary) ? VK_COMMAND_BUFFER_LEVEL_PRIMARY : VK_COMMAND_BUFFER_LEVEL_SECONDARY,
                1
            };

            vkCheck(
                vkAllocateCommandBuffers(vkInstance::Get().Device()->GetLogical(), &bufferInfo, &this->m_Buffer)
            );
        }

        vkCommandPool::vkCommandBuffer::~vkCommandBuffer() {
            vkFreeCommandBuffers(vkInstance::Get().Device()->GetLogical(), this->m_ParentPool, 1, &this->m_Buffer);
        }



        vkCommandPool::vkCommandPool(u32 queueIndex) :
            m_Pool(VK_NULL_HANDLE),
            m_QueueIndex(queueIndex),
            m_Buffers(0)
        {
            const VkCommandPoolCreateInfo poolInfo {
                VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
                nullptr,
                VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
                this->m_QueueIndex
            };

            vkCheck(
                vkCreateCommandPool(vkInstance::Get().Device()->GetLogical(), &poolInfo, nullptr, &this->m_Pool)
            );
        }

        vkCommandPool::~vkCommandPool() {
            this->m_Buffers.clear();

            vkDestroyCommandPool(vkInstance::Get().Device()->GetLogical(), this->m_Pool, nullptr);
        }

        void vkCommandPool::CreateBuffer(cstring name, b8 primary) {
            if (this->m_Buffers.find(name) != this->m_Buffers.end())
                throw Exception(Error::INVALID_ARGUMENT, "Attempting to create a buffer that already exists! vkCommandPool::CreateBuffer.");

            this->m_Buffers[name] = MakeRef<vkCommandBuffer>(this->m_Pool, primary);
        }

        void vkCommandPool::DestroyBuffer(cstring name) {
            if (this->m_Buffers.find(name) == this->m_Buffers.end())
                throw Exception(Error::INVALID_ARGUMENT, "Attempting to destroy a buffer that does not exist! vkCommandPool::DestroyBuffer.");

            this->m_Buffers.erase(name);
        }

    } // namespace Splash

} // namespace Ocean
