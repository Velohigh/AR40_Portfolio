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
	// Actor를 만들자!
	BackGround* Back = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Back->GetRenderer()->SetImage("TitleBackGround.bmp");	// 파일 이름
}

void TitleLevel::Update()
{
	// 레벨 체인지
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

