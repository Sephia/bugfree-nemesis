// Main.cpp

#include "stdafx.h"
#include "Engine.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Engine* engine = new Engine();

	engine->Init();

	while (engine->Run()) {
	}

	engine->CleanUp();
	delete engine;
	engine = nullptr;


	return 0;
}