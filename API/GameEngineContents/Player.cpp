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

