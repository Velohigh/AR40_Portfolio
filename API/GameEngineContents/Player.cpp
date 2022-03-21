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
		MsgBoxAssert("이미지 못찾음");
	}

	// 백버퍼에 이미지를 복사한다.
	GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());

}

