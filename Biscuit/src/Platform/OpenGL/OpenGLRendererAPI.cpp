#include "bcpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Biscuit {

	void OpenGLRendererAPI::Init()
	{
		//开启blender 颜色混合
		glEnable(GL_BLEND);

		//最终颜色 = 源颜色 * Alpha + 目标颜色 * (1 - Alpha)
		//源颜色: 当前正在绘制的像素（例如你当前绘制的纹理、颜色等）    
		//Alpha: 源颜色的透明度值（通常是它自己的 alpha 通道）
		//目标颜色: 当前这个像素位置上已经存在的颜色（也就是帧缓冲中已有的颜色，俗称“被覆盖的颜色”） 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}