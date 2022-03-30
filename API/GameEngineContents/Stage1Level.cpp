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
		
		
		float4 NewPivot = {};
		NewPivot = Back->GetRenderer()->GetImage()->GetScale().Half() - float4{ WINCX, WINCY}.Half();
		Back->GetRenderer()->SetPivot(NewPivot);
	}

	{	// �÷��̾� ����
		Player* NewPlayer = CreateActor<Player>((int)ORDER::PLAYER);
		NewPlayer->SetPosition({150, 600});
	}

	{	// UI ����, �ϳ��� ���Ϳ� �������� �������� UI�� ǥ���Ѵ�.
		CreateActor<PlayUI>((int)ORDER::UI);
	}

}

void Stage1Level::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Stage2"))	// Ű �Է� �� �������� �̵� 
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

