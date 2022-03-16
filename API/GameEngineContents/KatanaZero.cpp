#include "KatanaZero.h"
#include "TitleLevel.h"
#include "StageLevel.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>

KatanaZero::KatanaZero() 
{
}

KatanaZero::~KatanaZero() 
{
}

void KatanaZero::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 0,0 }, { 1280, 720 });

	CreateLevel<TitleLevel>("Title");
	CreateLevel<StageLevel>("Stage");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Title");

}

void KatanaZero::GameLoop()
{
}

void KatanaZero::GameEnd()
{
}

