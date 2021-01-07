#pragma once
#include "RenderPass.h"

#include "APIWrappers/PipelineState/GraphicPipelineState.h"
#include "APIWrappers/RootSignature.h"
#include "APIWrappers/DescriptorHeap.h"
#include "APIWrappers/Resources/Buffers/Views/VertexBufferView.h"
#include "APIWrappers/Resources/Buffers/Views/IndexBufferView.h"
#include "APIWrappers/Resources/Buffers/UploadBuffer.h"
#include "APIWrappers/Resources/Buffers/Views/ConstantBufferView.h"

namespace Boolka
{

    class DebugRenderPass :
        public RenderPass
    {
    public:
        DebugRenderPass();
        ~DebugRenderPass();

        bool Initialize(Device& device, RenderContext& renderContext, ResourceTracker& resourceTracker) override;
        void Unload() override;

        bool Render(RenderContext& renderContext, ResourceTracker& resourceTracker) override;
        bool PrepareRendering() override;

    private:
        GraphicPipelineState m_PSO;
        UploadBuffer m_VertexBuffer;
        VertexBufferView m_VertexBufferView;
        UploadBuffer m_IndexBuffer;
        IndexBufferView m_IndexBufferView;
        Buffer m_ConstantBuffers[BLK_IN_FLIGHT_FRAMES];
        UploadBuffer m_UploadBuffers[BLK_IN_FLIGHT_FRAMES];
        ConstantBufferView m_ConstantBufferViews[BLK_IN_FLIGHT_FRAMES];

        float m_CurrentAngle;
    };

}

