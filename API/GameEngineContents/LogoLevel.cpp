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
	// Actor를 만들자!
}

void LogoLevel::Update()
{
	GameEngine::GlobalEngine().ChangeLevel("Stage");
}

