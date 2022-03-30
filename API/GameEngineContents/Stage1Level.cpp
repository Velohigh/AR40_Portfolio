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
	{	// 백그라운드 액터
		BackGround* Back = CreateActor<BackGround>((int)ORDER::BACKGROUND);
		Back->GetRenderer()->SetImage("room_factory_2.bmp");		// 복습 : 각 Actor 는 Renderer를 들고 있고, 해당 렌더러는 EngineLevel 에서 출력해준다.
		
		
		float4 NewPivot = {};
		NewPivot = Back->GetRenderer()->GetImage()->GetScale().Half() - float4{ WINCX, WINCY}.Half();
		Back->GetRenderer()->SetPivot(NewPivot);
	}

	{	// 플레이어 액터
		Player* NewPlayer = CreateActor<Player>((int)ORDER::PLAYER);
		NewPlayer->SetPosition({150, 600});
	}

	{	// UI 액터, 하나의 엑터에 여러개의 렌더러로 UI를 표시한다.
		CreateActor<PlayUI>((int)ORDER::UI);
	}

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

