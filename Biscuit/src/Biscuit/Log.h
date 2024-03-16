#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Biscuit 
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() 
		{ 
			if (!s_CoreLogger)
				Init();
			return s_CoreLogger; 
		}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() 
		{ 
			if (!s_ClientLogger)
				Init();
			return s_ClientLogger; 
		}
		
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger; 
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define BC_CORE_TRACE(...)  ::Biscuit::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BC_CORE_INFO(...)   ::Biscuit::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BC_CORE_WARN(...)   ::Biscuit::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BC_CORE_ERROR(...)  ::Biscuit::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BC_CORE_FATAL(...)  ::Biscuit::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define BC_TRACE(...)  ::Biscuit::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BC_INFO(...)   ::Biscuit::Log::GetClientLogger()->info(__VA_ARGS__)
#define BC_WARN(...)   ::Biscuit::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BC_ERROR(...)  ::Biscuit::Log::GetClientLogger()->error(__VA_ARGS__)
#define BC_FATAL(...)  ::Biscuit::Log::GetClientLogger()->critical(__VA_ARGS__)
