#include "bcpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Biscuit {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			BC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}

		BC_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}