#include "BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Define.h"

BackGround::BackGround()
	: Image_(nullptr)
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	{
		// SetPosition(GameEngineWindow::GetScale().Half());
		SetPosition({ 0,0 });	// 백그라운드는 좌표 계산하기 쉽게 0,0 위치에 만든다.
		SetScale(GameEngineWindow::GetScale());
		Image_ = CreateRenderer();		// 백그라운드는 레벨마다 이미지가 달라지므로 None 이미지로 처음에 설정해준다.

		GetRenderer()->SetPivot({ WINCX >> 1, WINCY >> 1 });
	}

	if (strcmp(GetLevel()->GetNameConstPtr(), "Title")==0)
	{
		BackAnimationRenderer_ = CreateRenderer();
		BackAnimationRenderer_->CreateFolderAnimation("TitleAnimation", "TitleAnimation", 0, 229, 0.033f, true);
		BackAnimationRenderer_->SetPivot({ WINCX >> 1, WINCY >> 1 });
		BackAnimationRenderer_->SetScale({ WINCX, WINCY});

		BackAnimationRenderer_->ChangeAnimation("TitleAnimation");
		BackAnimationRenderer_->SetTransColor(RGB(255, 255, 255));	// 이미지에서 제외할 색
	}

}

void BackGround::Update()
{
}

void BackGround::Render()
{
	// DebugRectRender();
}
