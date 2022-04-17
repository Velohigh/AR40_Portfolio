#include "Stage2Level.h"
#include "Player.h"
#include "PlayUI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnums.h"
#include "BackGround.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include "Define.h"
#include "Grunt.h"
#include "Gangster.h"
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineTime.h>

Stage2Level::Stage2Level() 
{
}

Stage2Level::~Stage2Level() 
{
}

void Stage2Level::Loading()
{
	{	// 백그라운드 액터
		BackGround* Back = CreateActor<BackGround>((int)ORDER::BACKGROUND);
		Back->GetRenderer()->SetImage("room_factory_3_2.bmp");		// 복습 : 각 Actor 는 Renderer를 들고 있고, 해당 렌더러는 EngineLevel 에서 출력해준다.

		float4 NewPivot = Back->GetRenderer()->GetImage()->GetScale().Half();
		Back->GetRenderer()->SetPivot(NewPivot);
	}

	{	// 플레이어 액터
		Player* NewPlayer = CreateActor<Player>((int)ORDER::PLAYER);
		NewPlayer->SetPosition({ 450, 631 });
		//NewPlayer->ChangeState(PlayerState::PlaySong);
	}


	{	// 에너미 액터
		// 그런트
		Grunt* NewGrunt = CreateActor<Grunt>((int)ORDER::MONSTER);
		NewGrunt->SetPosition({ 1054, 383 });
		NewGrunt->SetDir(ActorDir::Right);
		NewGrunt->SetState(ActorState::Walk);
		NewGrunt->SetPatrol(true);

		NewGrunt = CreateActor<Grunt>((int)ORDER::MONSTER);
		NewGrunt->SetPosition({ 483, 760 });
		NewGrunt->SetDir(ActorDir::Right);

		NewGrunt = CreateActor<Grunt>((int)ORDER::MONSTER);
		NewGrunt->SetPosition({ 583, 760 });
		NewGrunt->SetDir(ActorDir::Left);

	}

	{	// UI 액터, 하나의 엑터에 여러개의 렌더러로 UI를 표시한다.
		CreateActor<PlayUI>((int)ORDER::UI);
	}
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

