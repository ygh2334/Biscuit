#pragma once

namespace Biscuit {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{

		}

		operator float() const { return m_Time; }  //允许Timestep隐式转换为float
		float GetSeconds() const { return m_Time; }
		float GetMilliSeconds() const { return m_Time * 1000; }
	private:
		float m_Time;
	};
}