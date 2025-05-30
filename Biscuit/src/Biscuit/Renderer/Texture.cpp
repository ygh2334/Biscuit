#include "bcpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Biscuit {

	Biscuit::Ref<Biscuit::Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}

		BC_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}