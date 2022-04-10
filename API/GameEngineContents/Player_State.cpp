#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Effect_JumpCloud.h"
#include "Effect_LandCloud.h"
#include "Effect_DustCloud.h"
#include "ContentsEnums.h"


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
	AnimationName_ = "Attack_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
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
	Effect_DustCloud* NewEffect = GetLevel()->CreateActor<Effect_DustCloud>((int)ORDER::UI);
	NewEffect->SetPosition(GetPosition());
	if (CurDir_ == PlayerDir::Right)
		NewEffect->SetDir(ActorDir::Left);
	else if (CurDir_ == PlayerDir::Left)
		NewEffect->SetDir(ActorDir::Right);

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
	Effect_JumpCloud* NewEffect = GetLevel()->CreateActor<Effect_JumpCloud>((int)ORDER::UI);
	NewEffect->SetPosition(GetPosition());

	SetPosition(GetPosition() + float4{0, -2});
	AnimationName_ = "Jump_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	MoveDir *= Speed_;
	MoveDir += float4::UP * JumpPower_;	// ���� �Ŀ�
}

void Player::LandingStart()
{

	AnimationName_ = "Landing_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(0.f);

}

////////////////////////////////////////
// StateUpdate
void Player::IdleUpdate()
{
	// �̵�Ű�� ������ IdleToRun ���·�
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::IdleToRun);
		return;
	}

	// �Ʒ��ʿ� ������ ���ٸ� Fall���·�
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump && color != RGB(255,0,0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (color == RGB(255, 0, 0) &&
		true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		SetPosition(GetPosition() + float4{0, 1});
	}

	// ����Ű�� ������ Jump ���·�
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ ���� �߰�.
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	// ����Ű�� ������ ���ݻ��·�
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
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

	// ����Ű�� ������ Jump ���·�
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ ���� �߰�.
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	// ����
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump && color != RGB(255, 0, 0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (color == RGB(255, 0, 0) &&
		true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		SetPosition(GetPosition() + float4{ 0, 1 });
	}


	MoveDir = float4::ZERO;

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
	if (true == PlayerAnimationRenderer->IsEndAnimation())
	{
		ChangeState(PlayerState::Fall);
		return;
	}

}
void Player::FallUpdate()
{
	// ���߿� �� �����ϰ�� �߷¿����� �޴´�.
	// �߷� ���ӵ��� ���� ���� �ӵ�.
	{
		// �������ǿ��� ���ϴ� ��ġ�� �ȼ��� ������ ���� �� �ִ�.
		int Color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });

		Gravity_ += AccGravity_ * GameEngineTime::GetDeltaTime();
		if (RGB(0, 0, 0) == Color || RGB(255,0,0) == Color)	// ���� ���� ��� 
		{
			Gravity_ = 10.0f;
			MoveDir.Normal2D();
			
			Effect_LandCloud* NewEffect = GetLevel()->CreateActor<Effect_LandCloud>((int)ORDER::UI);
			NewEffect->SetPosition(GetPosition());

			ChangeState(PlayerState::Landing);	
			return;
		}
		SetMove(float4::DOWN * Gravity_ * GameEngineTime::GetDeltaTime());
	}
	
	// ����
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * 2000.f;
		float4 TempX = { MoveDir.x,0,0 };

		if (TempX.Len2D() >= 450.f)
		{
			TempX.Range2D(450.f);
			MoveDir.x = TempX.x;
		}
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * 2000.f;
		float4 TempX = { MoveDir.x,0,0 };

		if (TempX.Len2D() >= 450.f)
		{
			TempX.Range2D(450.f);
			MoveDir.x = TempX.x;
		}
	}


	SetMove(MoveDir * GameEngineTime::GetDeltaTime());


}
void Player::DodgeUpdate()
{

}
void Player::RunUpdate()
{

	// �̵�Ű�� �ȴ����� Idle ���·�
	if (false == IsMoveKey())
	{
		ChangeState(PlayerState::RunToIdle);
		return;
	}

	// ����Ű�� ������ Jump ���·�
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ ���� �߰�.
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	// �Ʒ��ʿ� ������ ���ٸ� Fall���·�
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump && color != RGB(255,0,0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (color == RGB(255, 0, 0) &&
		true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		SetPosition(GetPosition() + float4{ 0, 1 });
	}

	// ����
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	MoveDir = float4::ZERO;

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

	// ����Ű�� ������ Jump ���·�
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ ���� �߰�.
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	// �Ʒ��ʿ� ������ ���ٸ� Fall���·�
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump && color != RGB(255, 0, 0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (color == RGB(255, 0, 0) &&
		true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		SetPosition(GetPosition() + float4{ 0, 1 });
	}

	// ����
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
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


	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.f;

	float4 TempY = { 0,MoveDir.y,0 };

	if (30.0f >= TempY.Len2D())
	{
		MoveDir.y = 0;
		//MoveDir.Normal2D();
		ChangeState(PlayerState::Fall);
		return;
	}

	// ����
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	// ���� ���� ���� ��� 
	int Color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (RGB(0, 0, 0) == Color)
	{
		Gravity_ = 10.0f;
		MoveDir.Normal2D();

		Effect_LandCloud* NewEffect = GetLevel()->CreateActor<Effect_LandCloud>((int)ORDER::UI);
		NewEffect->SetPosition(GetPosition());

		ChangeState(PlayerState::Landing);
		return;
	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * 2000.f;
		float4 TempX = { MoveDir.x,0,0 };

		if (TempX.Len2D() >= 450.f)
		{
			TempX.Range2D(450.f);
			MoveDir.x = TempX.x;
		}
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * 2000.f;
		float4 TempX = { MoveDir.x,0,0 };

		if (TempX.Len2D() >= 450.f)
		{
			TempX.Range2D(450.f);
			MoveDir.x = TempX.x;
		}
	}


	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

}

void Player::LandingUpdate()
{
	if (true == PlayerAnimationRenderer->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	// �̵�Ű�� ������ IdleToRun ���·�
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::IdleToRun);
		return;
	}

	// �Ʒ��ʿ� ������ ���ٸ� Fall���·�
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump && color != RGB(255, 0, 0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}


	// ����
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}


	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (color == RGB(255, 0, 0) &&
		true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		SetPosition(GetPosition() + float4{ 0, 1 });
	}

	// ����Ű�� ������ Jump ���·�
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ ���� �߰�.
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

}
