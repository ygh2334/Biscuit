#pragma once
#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Biscuit/Renderer/Shader.h"

namespace  Biscuit
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformFloat(const std::string& name, const glm::vec4& value);

	private:
		uint32_t m_RendererID;
	};
}