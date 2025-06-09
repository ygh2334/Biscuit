#include "bcpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Biscuit
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		if (s_CoreLogger.get() != nullptr)
			return;

		spdlog::set_pattern("%^[%T] %n: %v%s");
		s_CoreLogger = spdlog::stdout_color_mt("BISCUIT");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}