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
	// SetPosition(GameEngineWindow::GetScale().Half());
	SetPosition({ 0,0 });	// ��׶���� ��ǥ ����ϱ� ���� 0,0 ��ġ�� �����.
	SetScale(GameEngineWindow::GetScale());
	Image_ = CreateRenderer(RenderPivot::CENTER, {WINCX>>1, WINCY>>1});		// ��׶���� �������� �̹����� �޶����Ƿ� None �̹����� ó���� �������ش�.
}

void BackGround::Update()
{
}

void BackGround::Render()
{
	// DebugRectRender();
}
