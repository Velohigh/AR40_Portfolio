#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // ������ ���ؼ�
#include "Bullet.h"						// �Ѿ��� ����� �ʹ�.

Player::Player()
	: Speed_(100), Gravity_(100.f)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	// SetPosition(GameEngineWindow::GetScale().Half());	// �÷��̾� ���� ��ġ, �� �������� �����ٰ��̹Ƿ� �ּ�
	SetScale({ 36,70 });		// ��Ʈ�ڽ�

	//// GameEngineRenderer* Render = CreateRendererToScale("Idle.bmp", { 300, 300 });
	GameEngineRenderer* Render = CreateRenderer();
	//// Render->SetIndex(0, {72, 70});	// ū�̹��� ���忡 ��� �ִϸ��̼��� 10��° �̹�����, Ư�� ũ��� ���

	// TransParent�� �̿��� �̹��� ũ�� ���� �Լ�
	// CreateRendererToScale("hpbar.bmp", float4(300.0f, 20.0f), RenderPivot::CENTER, float4(0.0f, -100.0f));

	// �ִϸ��̼��� �ϳ��� ����� �ִϸ��̼ǵ� ����ȴ�.
	Render->CreateAnimation("idle_Right.bmp", "Idle_Right", 0, 10, 0.1f, true);
	Render->ChangeAnimation("Idle_Right");
	Render->SetTransColor(RGB(255,255,255));

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Jump", VK_SPACE);	//virtual key (������ Ű)
		GameEngineInput::GetInst()->CreateKey("Dodge", VK_LSHIFT);
		// VK_LBUTTON ���콺 ��Ŭ��

		GameEngineInput::GetInst()->CreateKey("Fire", 'Q');
		GameEngineInput::GetInst()->CreateKey("DebugRender", VK_F1);


	}

}

void Player::Update()
{
	MapColImage_ = GameEngineImageManager::GetInst()->Find("room_factory_2_ColMap.bmp");

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�.");
	}

	float4 CheckPos;	// ? �Ⱦ��µ�
	float4 MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir = float4::UP;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir = float4::DOWN;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// ���� �߰�.
	{
	}

	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// ȸ�� �߰�.
	{
	}

	if (0.5f <= GameEngineInput::GetInst()->GetTime("Fire"))	// 0.5�� �̻� ������ �Ѿ˽�� -> ������ ���� �߰�
	{
		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());
	}

	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,70 };	// �̷� ��ġ�� �߱��� ����

		int Color = MapColImage_->GetImagePixel(CheckPos);

		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}

	// �߷� ���ӵ��� ���� ���� �ӵ�.
	{
		// �������ǿ��� ���ϴ� ��ġ�� �ȼ��� ������ ���� �� �ִ�.
		int Color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,70 });

		AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;
		if (RGB(0,0,0) == Color)
		{
			AccGravity_ = 0.0f;
		}
		SetMove(float4::DOWN * AccGravity_ * GameEngineTime::GetDeltaTime());
	}

}

void Player::Render()
{
	if (GetAsyncKeyState(VK_F1))
	{
		DebugRectRender();
	}

	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("�̹��� ��ã��");
	//}

	//// ����ۿ� �̹����� �����Ѵ�.
	//GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());

}

