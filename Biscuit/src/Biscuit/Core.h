#pragma once

#ifdef BC_PLATFORM_WINDOWS
#if BC_DYNAMIC_LINK
	#ifdef BC_BUILD_DLL
		#define BISCUIT_API __declspec(dllexport)
	#else
		#define BISCUIT_API __declspec(dllimport)
	#endif 
#else
	#define BISCUIT_API
#endif
#else
	#error Biscuit only support Windows!
#endif

#ifdef  BC_DEBUG
	#define BC_ENABLE_ASSERTS
#endif //  BC_DEBUG

#ifdef BC_ENABLE_ASSERTS
#define BC_ASSERT(x, ...) { if(!(x)) { BC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define BC_CORE_ASSERT(x, ...) { if(!(x)) { BC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define BC_ASSERT(x, ...)
#define BC_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)	

#define BC_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)
