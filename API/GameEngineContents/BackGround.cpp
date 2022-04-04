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
	Image_ = CreateRenderer();		// ��׶���� �������� �̹����� �޶����Ƿ� None �̹����� ó���� �������ش�.
	
	GetRenderer()->SetPivot({ WINCX >> 1, WINCY >> 1 });
	//GetRenderer()->SetPivot(GetRenderer()->GetImage()->GetScale().Half());
}

void BackGround::Update()
{
}

void BackGround::Render()
{
	// DebugRectRender();
}
