#include "KatanaZero.h"
#include "TitleLevel.h"
#include "StageLevel.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

KatanaZero::KatanaZero() 
{
}

KatanaZero::~KatanaZero() 
{
}

void KatanaZero::GameInit()
{
	// 윈도우 크기 설정
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 0,0 }, { 1280, 720 });

	GameEngineImageManager::GetInst()->Load("D:\\AR40_JUNG\\Portfolio\\API\\Resources\\Player\\spr_idle\\0.bmp", "Idle.bmp");

	CreateLevel<TitleLevel>("Title");
	CreateLevel<StageLevel>("Stage");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Stage");

}

void KatanaZero::GameLoop()
{
}

void KatanaZero::GameEnd()
{
}

