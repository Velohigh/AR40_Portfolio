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
#include "Mouse.h"


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
		Grunt* NewPlayer = CreateActor<Grunt>((int)ORDER::MONSTER);
		NewPlayer->SetPosition({ 1054, 381 });
		NewPlayer = CreateActor<Grunt>((int)ORDER::MONSTER);
		NewPlayer->SetPosition({ 338, 381 });
	}

	{	// UI ����, �ϳ��� ���Ϳ� �������� �������� UI�� ǥ���Ѵ�.
		CreateActor<PlayUI>((int)ORDER::UI);
	}

	{	// ���콺 ����
		Mouse* NewMouse = CreateActor<Mouse>((int)ORDER::UI);
	}

}

void Stage1Level::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Stage2"))	// Ű �Է� �� �������� �̵� 
	{
		GameEngine::GetInst().ChangeLevel("Stage2");
	}
}

void Stage1Level::LevelChangeStart()
{
}

void Stage1Level::LevelChangeEnd()
{
}

