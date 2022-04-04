#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineLevel.h> // ������ ���ؼ�
#include "Bullet.h"						// �Ѿ��� ����� �ʹ�.


void Player::IdleStart()
{
	// �ִϸ��̼� ü����
	AnimationName_ = "Idle_";
}

void Player::AttackStart()
{

}

void Player::FallStart()
{

}

void Player::DodgeStart()
{

}

void Player::MoveStart()
{

}

////////////////////////////////////////
// StateUpdate
void Player::IdleUpdate()
{
	if (true == IsMoveKey())									// �̵�Ű�� �����ٸ�
	{
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ ���� �߰�.
	{
	}

	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// @@@ ȸ�� �߰�.
	{
	}

	if (0.5f <= GameEngineInput::GetInst()->GetTime("Fire"))	// @@@ 0.5�� �̻� ������ �Ѿ˽�� -> ������ ���� �߰�
	{
		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());
	}
}
void Player::AttackUpdate()
{

}
void Player::FallUpdate()
{
	// ���߿� �� �����ϰ�� �߷¿����� �޴´�.
	// �߷� ���ӵ��� ���� ���� �ӵ�.
	{
		// �������ǿ��� ���ϴ� ��ġ�� �ȼ��� ������ ���� �� �ִ�.
		int Color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,35 });

		AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;
		if (RGB(0, 0, 0) == Color)	// ���� ���� ��� 
		{
			AccGravity_ = 0.0f;
			ChangeState(PlayerState::Idle);	
			return;
		}
		SetMove(float4::DOWN * AccGravity_ * GameEngineTime::GetDeltaTime());
	}
}
void Player::DodgeUpdate()
{

}
void Player::MoveUpdate()
{
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

	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,35 };	// �̷� ��ġ�� �߱��� ����

		int Color = MapColImage_->GetImagePixel(CheckPos);

		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}


}