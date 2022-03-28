#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleLogo.h"
#include "TitleBackground.h"


TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	// Actor�� ������!
	CreateActor<TitleBackground>(0);
	CreateActor<TitleLogo>(1);
}

void TitleLevel::Update()
{
	//GameEngine::GlobalEngine().ChangeLevel("Stage");
}

