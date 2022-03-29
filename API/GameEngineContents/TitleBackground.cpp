#include "TitleBackground.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngine.h>

TitleBackground::TitleBackground() 
{
}

TitleBackground::~TitleBackground() 
{
}

void TitleBackground::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());
}

void TitleBackground::Update()
{
}

void TitleBackground::Render()
{
	DebugRectRender();

	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("TitleBackGround.bmp");
	if (nullptr == FindImage)
	{
		MsgBoxAssert("�̹��� ��ã��");
	}

	// ����ۿ� �̹����� �����Ѵ�.
	GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());
}

