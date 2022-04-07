#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서
#include "Bullet.h"						// 총알을 만들고 싶다.


void Player::IdleStart()
{
	// 애니메이션 체인지
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
	// 이동키를 누르면 Run 상태로
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::IdleToRun);
		return;
	}

	// 아래쪽에 지형이 없다면 Fall상태로
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump)
	{
		ChangeState(PlayerState::Fall);
		return;
	}
	
	// 아래쪽에 지형이 있다면 그위에 서게 한다.
	if (color == RGB(0,0,0))

	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ 점프 추가.
	{
	}

	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// @@@ 회피 추가.
	{
	}

	if (0.5f <= GameEngineInput::GetInst()->GetTime("Fire"))	// @@@ 0.5초 이상 누를시 총알쏘기 -> 게이지 관련 추가
	{
		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());
	}
}
void Player::IdleToRunUpdate()
{
	// 애니메이션 종료후 Run 모션으로
	if (true == PlayerAnimationRenderer->IsEndAnimation())
	{
		ChangeState(PlayerState::Run);
		return;
	}

	// 이동키를 안눌렀다면 Idle 상태로
	if (false == IsMoveKey())				// 이동키를 안눌렀다면
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
		// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,0 };	// 미래 위치의 발기준 색상

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
	// 공중에 뜬 상태일경우 중력영향을 받는다.
	// 중력 가속도에 따른 낙하 속도.
	{
		// 내포지션에서 원하는 위치의 픽셀의 색상을 구할 수 있다.
		int Color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });

		Gravity_ += AccGravity_ * GameEngineTime::GetDeltaTime();
		if (RGB(0, 0, 0) == Color)	// 땅에 닿을 경우 
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
		// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,0 };	// 미래 위치의 발기준 색상

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

	if (false == IsMoveKey())				// 이동키를 안눌렀다면
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
		// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,0 };	// 미래 위치의 발기준 색상

		int Color = MapColImage_->GetImagePixel(CheckPos);

		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}


}

void Player::RunToIdleUpdate()
{
	// 이동키를 누르면 Run 상태로
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::IdleToRun);
		return;
	}

	// 아래쪽에 지형이 없다면 Fall상태로
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// 이동키를 안누르고, 애니메이션이 끝까지 재생되면 Idle 상태로
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
			// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
			float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			float4 CheckPos = NextPos + float4{ 0,0 };	// 미래 위치의 발기준 색상

			int Color = MapColImage_->GetImagePixel(CheckPos);

			if (RGB(0, 0, 0) != Color)
			{
				SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			}
		}

	}

	// 멈추는중에 다시 이동키를 누르면
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::IdleToRun);
		return;
	}

}

void Player::JumpUpdate()
{

}
