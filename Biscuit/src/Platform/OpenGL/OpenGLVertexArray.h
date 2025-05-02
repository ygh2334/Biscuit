#pragma once

#include "Biscuit/Renderer/VertexArray.h"

namespace Biscuit
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() {}

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) override;

	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffers;
	};
}