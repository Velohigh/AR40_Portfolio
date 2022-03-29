#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleLogo.h"
#include "TitleBackground.h"
#include <GameEngineBase/GameEngineInput.h>


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
	// ���� ü����
	if (true == GameEngineInput::GetInst()->IsDown("Stage1"))
	{
	GameEngine::GlobalEngine().ChangeLevel("Stage1");
	}

}

void TitleLevel::LevelChangeStart()
{
}

void TitleLevel::LevelChangeEnd()
{
}

