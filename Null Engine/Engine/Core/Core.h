#pragma once

#ifdef NULL_ENGINE
	#define API __declspec(dllexport)
#else
	#define API __declspec(dllimport)
#endif