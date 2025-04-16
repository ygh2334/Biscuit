#pragma once

#include "Biscuit/Renderer/Buffer.h"

namespace Biscuit
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertex, uint32_t size)
		{

		}

		virtual ~OpenGLVertexBuffer() {};

		virtual void Bind() const;
		virtual void Unbind() const;
	};
}