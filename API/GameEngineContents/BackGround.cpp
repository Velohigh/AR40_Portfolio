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
	Image_ = CreateRenderer();		// ��׶���� �������� �̹����� �޶����Ƿ� None �̹����� ó���� �������ش�.
}

void BackGround::Update()
{
}

void BackGround::Render()
{
	// DebugRectRender();
}
