#include "Stage1Level.h"
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


Stage1Level::Stage1Level() 
{
}

Stage1Level::~Stage1Level()
{
}

void Stage1Level::Loading()
{
	{	// 백그라운드 액터
		BackGround* Back = CreateActor<BackGround>((int)ORDER::BACKGROUND);
		Back->GetRenderer()->SetImage("room_factory_2.bmp");		// 복습 : 각 Actor 는 Renderer를 들고 있고, 해당 렌더러는 EngineLevel 에서 출력해준다.
		
		float4 NewPivot = Back->GetRenderer()->GetImage()->GetScale().Half();
		Back->GetRenderer()->SetPivot(NewPivot);
	}

	{	// 플레이어 액터
		Player* NewPlayer = CreateActor<Player>((int)ORDER::PLAYER);
		NewPlayer->SetPosition({230, 671});
		NewPlayer->ChangeState(PlayerState::PlaySong);
	}


	{	// 에너미 액터
		// 그런트
		Grunt* NewGrunt = CreateActor<Grunt>((int)ORDER::MONSTER);
		NewGrunt->SetPosition({ 1054, 383 });
		NewGrunt->SetDir(ActorDir::Right);
		NewGrunt->SetState(ActorState::Walk);
		NewGrunt->SetPatrol(true);
		NewGrunt = CreateActor<Grunt>((int)ORDER::MONSTER);
		NewGrunt->SetPosition({ 338, 383 });
		NewGrunt->SetDir(ActorDir::Right);

		//NewGrunt->SetPosition({ 913, 505 });
		NewGrunt = CreateActor<Grunt>((int)ORDER::MONSTER);
		NewGrunt->SetPosition({ 530, 671 });
		NewGrunt = CreateActor<Grunt>((int)ORDER::MONSTER);
		NewGrunt->SetPosition({ 338, 671 });


		// 갱스터
		Gangster* NewGangster = CreateActor<Gangster>((int)ORDER::MONSTER);
		NewGangster->SetPosition({ 545, 383 });
		NewGangster->SetDir(ActorDir::Left);
	}

	{	// UI 액터, 하나의 엑터에 여러개의 렌더러로 UI를 표시한다.
		CreateActor<PlayUI>((int)ORDER::UI);
	}

}

void Stage1Level::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Stage2"))	// 키 입력 시 스테이지 이동 
	{
		GameEngine::GetInst().ChangeLevel("Stage2");
	}

	BgmTime -= GameEngineTime::GetDeltaTime();
	if (BgmOn == true && BgmTime < 0.f)
	{
		BgmPlayer = GameEngineSound::SoundPlayControl("song_youwillneverknow.ogg", 9999);
		BgmOn = false;
	}


}

void Stage1Level::LevelChangeStart()
{
	//BgmPlayer = GameEngineSound::SoundPlayControl("song_youwillneverknow.ogg");
}

void Stage1Level::LevelChangeEnd()
{
	BgmPlayer.Stop();
}
