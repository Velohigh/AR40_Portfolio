#include "Stage1Level.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

enum class ORDER
{
	BACKGROUND,
	PLAYER,
	MONSTER,
	UI
};

Stage1Level::Stage1Level() 
{
}

Stage1Level::~Stage1Level()
{
}

void Stage1Level::Loading()
{
}

void Stage1Level::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Stage2"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Stage2");
	}
}

void Stage1Level::LevelChangeStart()
{
	CreateActor<Player>((int)ORDER::PLAYER);
}

void Stage1Level::LevelChangeEnd()
{
}

