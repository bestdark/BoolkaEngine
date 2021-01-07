#include "stdafx.h"
#include "VertexBufferView.h"

namespace Boolka
{

    VertexBufferView::VertexBufferView()
        : m_View{}
    {
    }

    VertexBufferView::~VertexBufferView()
    {
        BLK_ASSERT(m_View.BufferLocation == 0);
    }

    bool VertexBufferView::Initialize(Buffer& vertexBuffer, UINT size, UINT stride)
    {
        BLK_ASSERT(m_View.BufferLocation == 0);

        m_View.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
        m_View.SizeInBytes = size;
        m_View.StrideInBytes = stride;

        return true;
    }

    void VertexBufferView::Unload()
    {
        BLK_ASSERT(m_View.BufferLocation != 0);
        m_View = {};
    }

}