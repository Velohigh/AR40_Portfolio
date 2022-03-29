#include "BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>

BackGround::BackGround()
	: Image_(nullptr)
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());
	Image_ = CreateRenderer();		// 백그라운드는 레벨마다 이미지가 달라지므로 None 이미지로 처음에 설정해준다.
}

void BackGround::Update()
{
}

void BackGround::Render()
{
	// DebugRectRender();
}
