#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleLogo.h"
#include "BackGround.h"
#include <GameEngineBase/GameEngineInput.h>
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>


TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	// Actor�� ������!
	BackGround* Back = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Back->GetRenderer()->SetImage("TitleBackGround.bmp");	// ���� �̸�
}

void TitleLevel::Update()
{
	// ���� ü����
	if (true == GameEngineInput::GetInst()->IsDown("Stage1"))
	{
	GameEngine::GetInst().ChangeLevel("Stage1");
	}

}

void TitleLevel::LevelChangeStart()
{
}

void TitleLevel::LevelChangeEnd()
{
}

