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
	if (true == IsMoveKey())									// 이동키를 눌렀다면
	{
		ChangeState(PlayerState::Move);
		return;
	}

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
void Player::AttackUpdate()
{

}
void Player::FallUpdate()
{
	// 공중에 뜬 상태일경우 중력영향을 받는다.
	// 중력 가속도에 따른 낙하 속도.
	{
		// 내포지션에서 원하는 위치의 픽셀의 색상을 구할 수 있다.
		int Color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,35 });

		AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;
		if (RGB(0, 0, 0) == Color)	// 땅에 닿을 경우 
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
	float4 CheckPos;	// ? 안쓰는듯
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
		// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,35 };	// 미래 위치의 발기준 색상

		int Color = MapColImage_->GetImagePixel(CheckPos);

		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}


}