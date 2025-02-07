#pragma once

#include "Ocean/Types/SmartPtrs.hpp"

#include "Ocean/Renderer/RendererAPI.hpp"

namespace Ocean {

    namespace Shrimp {
    
    class glRendererAPI : public RendererAPI {
    public:
        virtual void Init() override final;

        virtual void SetViewport(u32 x, u32 y, u32 w, u32 h) override final;

        virtual void SetClearColor(const glm::vec4& color) override final;
        virtual void Clear() override final;

        virtual void DrawIndexed(const Ref<VertexArray>& array, u32 indexCount) override final;

    };  // RendererAPI

    }   // Shrimp

}   // Ocean
