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
		SetPosition({ 0,0 });	// ��׶���� ��ǥ ����ϱ� ���� 0,0 ��ġ�� �����.
		SetScale(GameEngineWindow::GetScale());
		Image_ = CreateRenderer();		// ��׶���� �������� �̹����� �޶����Ƿ� None �̹����� ó���� �������ش�.

		GetRenderer()->SetPivot({ WINCX >> 1, WINCY >> 1 });
	}

	if (strcmp(GetLevel()->GetNameConstPtr(), "Title")==0)
	{
		BackAnimationRenderer_ = CreateRenderer();
		BackAnimationRenderer_->CreateFolderAnimation("TitleAnimation", "TitleAnimation", 0, 229, 0.033f, true);
		BackAnimationRenderer_->SetPivot({ WINCX >> 1, WINCY >> 1 });
		BackAnimationRenderer_->SetScale({ WINCX, WINCY});

		BackAnimationRenderer_->ChangeAnimation("TitleAnimation");
		BackAnimationRenderer_->SetTransColor(RGB(255, 255, 255));	// �̹������� ������ ��
	}

}

void BackGround::Update()
{
}

void BackGround::Render()
{
	// DebugRectRender();
}
