#include "LogoLevel.h"
#include "GameEngine/GameEngine.h"

LogoLevel::LogoLevel() 
{
}

LogoLevel::~LogoLevel() 
{
}

void LogoLevel::Loading()
{
	// Actor�� ������!
}

void LogoLevel::Update()
{
	GameEngine::GlobalEngine().ChangeLevel("Stage");
}

