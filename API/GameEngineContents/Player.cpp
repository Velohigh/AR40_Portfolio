#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngine.h>

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 100,100 });

	// CreateRenderer("Idle.bmp", RenderPivot::CENTER, { 0,0 });
	CreateRenderer("Idle.bmp");


	// TransParent�� �̿��� �̹��� ũ�� ���� �Լ�
	// CreateRendererToScale("hpbar.bmp", float4(300.0f, 20.0f), RenderPivot::CENTER, float4(0.0f, -100.0f));


}

void Player::Update()
{
}

void Player::Render()
{
	DebugRectRender();

	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	if (nullptr == FindImage)
	{
		MsgBoxAssert("�̹��� ��ã��");
	}

	// ����ۿ� �̹����� �����Ѵ�.
	GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());

}

