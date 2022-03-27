#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>

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


	// TransParent를 이용한 이미지 크기 조정 함수
	// CreateRendererToScale("hpbar.bmp", float4(300.0f, 20.0f), RenderPivot::CENTER, float4(0.0f, -100.0f));

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Jump", VK_SPACE);	//virtual key (윈도우 키)
		GameEngineInput::GetInst()->CreateKey("Dodge", VK_LSHIFT);
		// VK_LBUTTON 마우스 좌클릭

	}

}

void Player::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetMove(float4::RIGHT);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN);
	}

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

