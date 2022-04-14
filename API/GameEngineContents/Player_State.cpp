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
#include "Effect_Slash.h"
#include "ContentsEnums.h"
#include "Mouse.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineSound.h>


#include <GameEngine/GameEngineLevel.h> // ������ ���ؼ�
#include "Bullet.h"						// �Ѿ��� ����� �ʹ�.
#include <time.h>


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
	// ���� ����
	// GameEngineSound::SoundPlayOneShot("sound_player_slash_1.wav");

	// ���� ����Ʈ, @@@ �̹��� ȸ�� �߰��Ұ�.
	Effect_Slash* NewEffect = GetLevel()->CreateActor<Effect_Slash>((int)ORDER::Effect);
	NewEffect->SetPosition(GetPosition());


	AnimationName_ = "Attack_";
	if (Mouse_->GetPosition().x >= (GetCameraEffectPosition() + float4{ 0,-35 }).x)
	{
		CurDir_ = PlayerDir::Right;
		ChangeDirText = "Right";
	}
	else if (Mouse_->GetPosition().x < (GetCameraEffectPosition() + float4{ 0,-35 }).x)
	{
		CurDir_ = PlayerDir::Left;
		ChangeDirText = "Left";
	}
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);

	float4 AttackDir = Mouse_->GetPosition() - (GetCameraEffectPosition() + float4{ 0,-35 });
	AttackDir.Normal2D();
	MoveDir = float4::ZERO;
	// ���߿��� ���� �ѹ��� �����϶��� y�� �������� �ο��Ѵ�.
	if (AttackCount_ <= 0)
	{
		MoveDir = AttackDir * 480.f;
		++AttackCount_;
	}
	else if (AttackCount_ >= 1)
	{
		// �÷��̾�� 2ȸ �������� y�� �̵� ����, ���� ���� ���� ������
		if (AttackDir.y < 0)
		{
			MoveDir = float4{ AttackDir.x, 0 } * 480.f;
		}
		else
		{
			MoveDir = float4{ AttackDir.x, AttackDir.y} * 480.f;
		}
	}
	Gravity_ = 10.f;

}

void Player::FallStart()
{
	AnimationName_ = "Fall_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
}

void Player::DodgeStart()
{
	AnimationName_ = "Dodge_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(680.f);

}

void Player::RunStart()
{
	for (int i = 0; i < 5; ++i)
	{
		Effect_DustCloud* NewEffect = GetLevel()->CreateActor<Effect_DustCloud>((int)ORDER::Effect);
		NewEffect->SetPosition(GetPosition());
		if (CurDir_ == PlayerDir::Right)
			NewEffect->SetDir(ActorDir::Left);
		else if (CurDir_ == PlayerDir::Left)
			NewEffect->SetDir(ActorDir::Right);
	}

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
	// ���� ����Ʈ
	Effect_JumpCloud* NewEffect = GetLevel()->CreateActor<Effect_JumpCloud>((int)ORDER::Effect);
	NewEffect->SetPosition(GetPosition());

	// ���� ����
	//GameEngineSound::SoundPlayOneShot("sound_player_jump.wav");

	SetPosition(GetPosition() + float4{0, -2});
	AnimationName_ = "Jump_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	MoveDir *= Speed_;
	MoveDir += float4::UP * JumpPower_;	// ���� �Ŀ�
}

void Player::LandingStart()
{
	// ���� ����Ʈ
	Effect_LandCloud* NewEffect = GetLevel()->CreateActor<Effect_LandCloud>((int)ORDER::Effect);
	NewEffect->SetPosition(GetPosition());

	AnimationName_ = "Landing_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	MoveDir = float4::ZERO;
	SetSpeed(0.f);
	AttackCount_ = 0;
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
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,10 });
	int Rcolor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump && Rcolor != RGB(255, 0, 0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (Rcolor == RGB(255, 0, 0) &&
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

	// ����Ű�� ������ ���ݻ��·�
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// @@@ ȸ�� �߰�.
	{
		ChangeState(PlayerState::Dodge);
		return;
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

	// ȸ��Ű�� ������ Dodge ���·�
	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// @@@ ȸ�� �߰�.
	{
		ChangeState(PlayerState::Dodge);
		return;
	}

	// ����
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	// �Ʒ� ������ ���ٸ� Fall ���·�
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,10 });
	int Rcolor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });

	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump && Rcolor != RGB(255, 0, 0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (Rcolor == RGB(255, 0, 0) &&
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

	MapCollisionCheckMoveGround();
}


void Player::AttackUpdate()
{
	if (true == PlayerAnimationRenderer->IsEndAnimation())
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	MapCollisionCheckMoveAir();

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

	MapCollisionCheckMoveAir();

}
void Player::DodgeUpdate()
{
	// ���� ����� RunToIdle ���·�
	if (true == PlayerAnimationRenderer->IsEndAnimation())
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

	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	MapCollisionCheckMoveGround();

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
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,10 });
	int Rcolor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump && Rcolor != RGB(255,0,0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (Rcolor == RGB(255, 0, 0) &&
		true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		SetPosition(GetPosition() + float4{ 0, 1 });
	}

	// ȸ��Ű�� ������ Dodge ���·�
	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// @@@ ȸ�� �߰�.
	{
		ChangeState(PlayerState::Dodge);
		return;
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

	MapCollisionCheckMoveGround();
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
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,10 });
	int Rcolor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump && Rcolor != RGB(255, 0, 0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (Rcolor == RGB(255, 0, 0) &&
		true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		SetPosition(GetPosition() + float4{ 0, 1 });
	}

	// ȸ��Ű�� ������ Dodge ���·�
	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// @@@ ȸ�� �߰�.
	{
		ChangeState(PlayerState::Dodge);
		return;
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

		MapCollisionCheckMoveGround();
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


	MapCollisionCheckMoveAir();

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
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,10 });
	int Rcolor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump && Rcolor != RGB(255, 0, 0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// ȸ��Ű�� ������ Dodge ���·�
	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// @@@ ȸ�� �߰�.
	{
		ChangeState(PlayerState::Dodge);
		return;
	}

	// ����
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}


	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (Rcolor == RGB(255, 0, 0) &&
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


void Player::OnGroundUpdate()
{



}

void Player::MapCollisionCheckMoveAir()
{

	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		float4 NextPos = GetPosition() + (float4{ 0,MoveDir.y } *GameEngineTime::GetDeltaTime());
		float4 CheckPos = NextPos + float4{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		float4 CheckPosTopRight = NextPos + float4{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		float4 CheckPosTopLeft = NextPos + float4{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

		int Color = MapColImage_->GetImagePixel(CheckPos);
		int TopRightColor = MapColImage_->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = MapColImage_->GetImagePixel(CheckPosTopLeft);


		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			SetMove(float4{ 0,MoveDir.y } *GameEngineTime::GetDeltaTime());
		}
	}

	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		float4 NextPos = GetPosition() + (float4{ MoveDir.x,0 } *GameEngineTime::GetDeltaTime());
		float4 CheckPos = NextPos + float4{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		float4 CheckPosTopRight = NextPos + float4{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		float4 CheckPosTopLeft = NextPos + float4{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

		int Color = MapColImage_->GetImagePixel(CheckPos);
		int TopRightColor = MapColImage_->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = MapColImage_->GetImagePixel(CheckPosTopLeft);

		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			SetMove(float4{ MoveDir.x,0 } *GameEngineTime::GetDeltaTime());
		}
	}
}

void Player::MapCollisionCheckMoveGround()
{
	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		float4 NextPos = GetPosition() + (float4{ 0,MoveDir.y } *GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		float4 CheckPosTopRight = NextPos + float4{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		float4 CheckPosTopLeft = NextPos + float4{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

		int Color = MapColImage_->GetImagePixel(CheckPos);
		int TopRightColor = MapColImage_->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = MapColImage_->GetImagePixel(CheckPosTopLeft);



		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			SetMove(float4{ 0,MoveDir.y } *GameEngineTime::GetDeltaTime() * Speed_);
		}
	}

	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		float4 NextPos = GetPosition() + (float4{ MoveDir.x,0 } *GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		float4 CheckPosTopRight = NextPos + float4{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		float4 CheckPosTopLeft = NextPos + float4{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		float4 ForDownPos = GetPosition() + float4{0,1.f};	// �̷� ��ġ�� �Ӹ����� ����

		int CurColor = MapColImage_->GetImagePixel(GetPosition());
		int ForDownColor = MapColImage_->GetImagePixel(ForDownPos);
		int Color = MapColImage_->GetImagePixel(CheckPos);
		int TopRightColor = MapColImage_->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = MapColImage_->GetImagePixel(CheckPosTopLeft);


		// �׻� ���� �پ��ֱ�
		if (RGB(0, 0, 0) != ForDownColor && RGB(255,0,0) != ForDownColor)
		{
			SetMove(float4{ 0, 1.0f });
		}

		// ��� �ö󰡱�
		while (RGB(0, 0, 0) == Color &&
			TopRightColor != RGB(0, 0, 0) && TopLeftColor != RGB(0, 0, 0))
		{
			CheckPos.y -= 1.0f;
			Color = MapColImage_->GetImagePixel(CheckPos);
			SetMove(float4{ 0, -1.0f });
		}


		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			SetMove(float4{ MoveDir.x,0 } *GameEngineTime::GetDeltaTime() * Speed_);
		}

	}

	{
		// ���� �ö󰡱� ����
		float4 NextPos = GetPosition() + (MoveDir *GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		float4 CheckPosTopRight = NextPos + float4{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		float4 CheckPosTopLeft = NextPos + float4{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

		int CurColor = MapColImage_->GetImagePixel(GetPosition());
		int Color = MapColImage_->GetImagePixel(CheckPos);
		int TopRightColor = MapColImage_->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = MapColImage_->GetImagePixel(CheckPosTopLeft);


	}

}

