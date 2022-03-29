#include "Stage1Level.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnums.h"
#include "BackGround.h"
#include <GameEngine/GameEngineRenderer.h>


Stage1Level::Stage1Level() 
{
}

Stage1Level::~Stage1Level()
{
}

void Stage1Level::Loading()
{
	BackGround* Back = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Back->GetRenderer()->SetImage("room_factory_2.bmp");		// 복습 : 각 Actor 는 Renderer를 들고 있고, 해당 렌더러는 EngineLevel 에서 출력해준다.

	CreateActor<Player>((int)ORDER::PLAYER);
}

void Stage1Level::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Stage2"))	// 키 입력 시 스테이지 이동 
	{
		GameEngine::GlobalEngine().ChangeLevel("Stage2");
	}
}

void Stage1Level::LevelChangeStart()
{
}

void Stage1Level::LevelChangeEnd()
{
}

