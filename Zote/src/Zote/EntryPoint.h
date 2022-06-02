#pragma once
#include "Application.h";

#ifdef ZOTE_PLATFORM_WINDOWS

int main()
{
	auto app = Zote::CreateApplication();
	app->Run();
	delete app;
}

#endif 
