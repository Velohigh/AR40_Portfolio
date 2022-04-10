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
	{	// ��׶��� ����
		BackGround* Back = CreateActor<BackGround>((int)ORDER::BACKGROUND);
		Back->GetRenderer()->SetImage("room_factory_2.bmp");		// ���� : �� Actor �� Renderer�� ��� �ְ�, �ش� �������� EngineLevel ���� ������ش�.
		
		float4 NewPivot = Back->GetRenderer()->GetImage()->GetScale().Half();
		Back->GetRenderer()->SetPivot(NewPivot);

		Back->CreateCollision("Door", { 100, 100 }, { 280, 100 });	// �̹��� ���� ũ�� 100*100�� ��ġ280,100 �� �浹ü Door�� �����.
	}

	{	// �÷��̾� ����
		Player* NewPlayer = CreateActor<Player>((int)ORDER::PLAYER);
		NewPlayer->SetPosition({150, 600});
	}


	{	// ���ʹ� ����
		Grunt* NewGrunt = CreateActor<Grunt>((int)ORDER::MONSTER);
		NewGrunt->SetPosition({ 1054, 383 });
		NewGrunt->SetDir(ActorDir::Right);
		NewGrunt = CreateActor<Grunt>((int)ORDER::MONSTER);
		NewGrunt->SetPosition({ 338, 383 });
		NewGrunt->SetDir(ActorDir::Right);

		// ������
		Gangster* NewGangster = CreateActor<Gangster>((int)ORDER::MONSTER);
		NewGangster->SetPosition({ 545, 383 });
		NewGangster->SetDir(ActorDir::Left);
	}

	{	// UI ����, �ϳ��� ���Ϳ� �������� �������� UI�� ǥ���Ѵ�.
		CreateActor<PlayUI>((int)ORDER::UI);
	}

}

void Stage1Level::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Stage2"))	// Ű �Է� �� �������� �̵� 
	{
		GameEngine::GetInst().ChangeLevel("Stage2");
	}

	BgmTime -= GameEngineTime::GetDeltaTime();
	if (BgmTime <= 0)
	{
		BgmPlayer.Stop();
	}
}

void Stage1Level::LevelChangeStart()
{
	BgmPlayer = GameEngineSound::SoundPlayControl("song_youwillneverknow.ogg");
	BgmTime = 10.0f;

}

void Stage1Level::LevelChangeEnd()
{
}

