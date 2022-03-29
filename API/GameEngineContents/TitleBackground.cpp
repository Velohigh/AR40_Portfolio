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
		MsgBoxAssert("이미지 못찾음");
	}

	// 백버퍼에 이미지를 복사한다.
	GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());
}

