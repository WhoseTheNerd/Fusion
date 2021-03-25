#pragma once

#ifdef F_PLATFORM_WINDOWS
	#ifdef F_BUILD_DLL
		#define F_API __declspec(dllexport)
	#else
		#define F_API __declspec(dllimport)
	#endif
#else
	#error Fusion only supports Windows right now
#endif