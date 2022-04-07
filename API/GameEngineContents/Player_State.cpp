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
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(0.f);
}

void Player::IdleToRunStart()
{
	AnimationName_ = "Idle_To_Run_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(200.f);
}

void Player::AttackStart()
{

}

void Player::FallStart()
{
	AnimationName_ = "Fall_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
}

void Player::DodgeStart()
{

}

void Player::RunStart()
{
	AnimationName_ = "Run_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(450.f);
}

void Player::RunToIdleStart()
{
	AnimationName_ = "Run_To_Idle_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(100.f);

}

void Player::JumpStart()
{
}

////////////////////////////////////////
// StateUpdate
void Player::IdleUpdate()
{
	// �̵�Ű�� ������ Run ���·�
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::IdleToRun);
		return;
	}

	// �Ʒ��ʿ� ������ ���ٸ� Fall���·�
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump)
	{
		ChangeState(PlayerState::Fall);
		return;
	}
	
	// �Ʒ��ʿ� ������ �ִٸ� ������ ���� �Ѵ�.
	if (color == RGB(0,0,0))

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
void Player::IdleToRunUpdate()
{
	// �ִϸ��̼� ������ Run �������
	if (true == PlayerAnimationRenderer->IsEndAnimation())
	{
		ChangeState(PlayerState::Run);
		return;
	}

	// �̵�Ű�� �ȴ����ٸ� Idle ���·�
	if (false == IsMoveKey())				// �̵�Ű�� �ȴ����ٸ�
	{
		ChangeState(PlayerState::Idle);
		return;
	}


	float4 MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}

	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,0 };	// �̷� ��ġ�� �߱��� ����

		int Color = MapColImage_->GetImagePixel(CheckPos);

		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
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
		int Color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });

		Gravity_ += AccGravity_ * GameEngineTime::GetDeltaTime();
		if (RGB(0, 0, 0) == Color)	// ���� ���� ��� 
		{
			AccGravity_ = 0.0f;
			ChangeState(PlayerState::Idle);	
			return;
		}
		SetMove(float4::DOWN * Gravity_ * GameEngineTime::GetDeltaTime());
	}

	float4 MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}

	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,0 };	// �̷� ��ġ�� �߱��� ����

		int Color = MapColImage_->GetImagePixel(CheckPos);

		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}


}
void Player::DodgeUpdate()
{

}
void Player::RunUpdate()
{

	if (false == IsMoveKey())				// �̵�Ű�� �ȴ����ٸ�
	{
		ChangeState(PlayerState::RunToIdle);
		return;
	}


	float4 MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}

	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,0 };	// �̷� ��ġ�� �߱��� ����

		int Color = MapColImage_->GetImagePixel(CheckPos);

		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}


}

void Player::RunToIdleUpdate()
{
	// �̵�Ű�� ������ Run ���·�
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::IdleToRun);
		return;
	}

	// �Ʒ��ʿ� ������ ���ٸ� Fall���·�
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// �̵�Ű�� �ȴ�����, �ִϸ��̼��� ������ ����Ǹ� Idle ���·�
	if (false == IsMoveKey() && 
		true == PlayerAnimationRenderer->IsEndAnimation())				
	{
		ChangeState(PlayerState::Idle);
		return;
	}


	else if (false == IsMoveKey() &&
		false == PlayerAnimationRenderer->IsEndAnimation())
	{
		float4 MoveDir = float4::ZERO;

		if (CurDir_ == PlayerDir::Left)
		{
			MoveDir = float4::LEFT;
		}

		else if (CurDir_ == PlayerDir::Right)
		{
			MoveDir = float4::RIGHT;
		}

		{
			// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
			float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			float4 CheckPos = NextPos + float4{ 0,0 };	// �̷� ��ġ�� �߱��� ����

			int Color = MapColImage_->GetImagePixel(CheckPos);

			if (RGB(0, 0, 0) != Color)
			{
				SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			}
		}

	}

	// ���ߴ��߿� �ٽ� �̵�Ű�� ������
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::IdleToRun);
		return;
	}

}

void Player::JumpUpdate()
{

}
