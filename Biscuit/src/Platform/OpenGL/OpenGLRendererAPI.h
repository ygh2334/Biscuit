#pragma once
#include "Biscuit/Renderer/RendererAPI.h"

namespace Biscuit {

	class OpenGLRendererAPI : public RendererAPI 
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
