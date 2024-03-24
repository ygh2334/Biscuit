#pragma once

#include "Biscuit/Layer.h"
#include "Biscuit/Events/KeyEvent.h"
#include "Biscuit/Events/MouseEvent.h"
#include "Biscuit/Events/ApplicationEvent.h"

namespace Biscuit
{
	class BISCUIT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}