#include "bcpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Biscuit {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}