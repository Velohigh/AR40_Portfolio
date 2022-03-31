#include "PlayUI.h"
#include "Define.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

PlayUI::PlayUI() 
{
}

PlayUI::~PlayUI() 
{
}

void PlayUI::Start()
{
	// 액터를 화면 중앙에 놓는다.
	SetPosition({ WINCX>>1, WINCY>>1 });

	// 화면 특정 위치에 UI 랜더러를 만든다.
	{
		//GameEngineRenderer* NewRenderer = CreateRenderer("이미지 경로 추가");
		//NewRenderer->SetPivot();	// 렌더러를 띄울 위치 삽입

		//NewRenderer->CameraEffectOff();	// UI는 카메라의 영향을 받지 않는다. EX) HP바, 게이지 등
	}
}

void PlayUI::Update()
{
}

void PlayUI::Render()
{
	// DebugRectRender();
}

