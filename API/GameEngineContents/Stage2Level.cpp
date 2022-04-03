#include "Stage2Level.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

Stage2Level::Stage2Level() 
{
}

Stage2Level::~Stage2Level() 
{
}

void Stage2Level::Loading()
{
}

void Stage2Level::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Ending"))
	{
		GameEngine::GetInst().ChangeLevel("Ending");
	}
}

void Stage2Level::LevelChangeStart()
{
}

void Stage2Level::LevelChangeEnd()
{
}

