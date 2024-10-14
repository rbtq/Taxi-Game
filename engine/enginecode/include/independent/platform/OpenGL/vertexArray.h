/* \file vertexArray.h*/
#pragma once

#include <vector>
#include <memory>
#include "vertexBuffer.h"
#include "indexBuffer.h"

namespace Engine
{
	class VertexArray
	{
	public:
		VertexArray(); //!< Constructor
		~VertexArray(); //!< Destructor
		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer); //!< Adds vertex buffer
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer); //!< Sets index buffer
		inline uint32_t getRenderID() const { return m_OpenGL_ID; } //!< Returns OpenGL ID
		uint32_t getDrawCount() { if (m_indexBuffer) { return m_indexBuffer->getCount(); } else { return 0; } } //!< Returns draw count
		inline std::shared_ptr<IndexBuffer> getIndexBuffer() { return m_indexBuffer; } //!< Returns index buffer
		inline std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffer() { return m_vertexBuffer; } //!< Returns vertex buffer
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		uint32_t m_attributeIndex = 0; //!< Attribute Index
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffer; //!< Vertex Buffer
		std::shared_ptr<IndexBuffer> m_indexBuffer; //!< Index Buffer
	};
}