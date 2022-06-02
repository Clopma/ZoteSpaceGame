#pragma once

#ifdef ZOTE_PLATFORM_WINDOWS
	#ifdef ZOTE_BUILD_DLL
		#define ZOTE_API __declspec(dllexport)
	#else
		#define ZOTE_API __declspec(dllimport)
	#endif
#else
	#error Zote only supports Windows!
#endif