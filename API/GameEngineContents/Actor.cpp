#include "Actor.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>

Actor::Actor() 
	: CurState_(ActorState::Idle), PreState_(ActorState::Idle)
{
}

Actor::~Actor() 
{
}

void Actor::DirAnimationCheck()
{

	if (PreDir_ != CurDir_)
	{

		if (CurDir_ == ActorDir::Right)
		{
			ChangeDirText = "Right";
		}
		else if (CurDir_ == ActorDir::Left)
		{
			ChangeDirText = "Left";
		}

		ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
		PreDir_ = CurDir_;
	}

}

void Actor::ChangeState(ActorState _State)
{
	if (_State != CurState_)	// ���°� �ٲ� �ѹ��� ��������ش�.
	{
		switch (_State)
		{
		case ActorState::Idle:
			IdleStart();
			break;
		case ActorState::Walk:
			WalkStart();
			break;
		case ActorState::Turn:
			TurnStart();
			break;
		case ActorState::Run:
			RunStart();
			break;
		case ActorState::Attack:
			AttackStart();
			break;
		case ActorState::HurtGround:
			HurtGroundStart();
			break;
		case ActorState::HurtFly:
			HurtFlyStart();
			break;
		case ActorState::END:
			break;
		default:
			break;
		}
	}
	CurState_ = _State;
}

void Actor::ActorStateUpdate()
{
	switch (CurState_)
	{
	case ActorState::Idle:
		IdleUpdate();
		break;
	case ActorState::Walk:
		WalkUpdate();
		break;
	case ActorState::Turn:
		TurnUpdate();
		break;
	case ActorState::Run:
		RunUpdate();
		break;
	case ActorState::Attack:
		AttackUpdate();
		break;
	case ActorState::HurtGround:
		HurtGroundUpdate();
		break;
	case ActorState::HurtFly:
		HurtFlyUpdate();
		break;
	case ActorState::END:
		break;
	default:
		break;
	}

}

void Actor::DebugRender()
{
	// ����׿�

	if (GetAsyncKeyState(VK_F1))
	{
		bDebugRender_ = true;
	}
	else if (GetAsyncKeyState(VK_F2))
	{
		bDebugRender_ = false;
	}

	if (true == bDebugRender_)
	{

		TCHAR szBuff[64] = "";
		TCHAR StateBuff[64] = {};

		{
			if (CurState_ == ActorState::Idle)
				sprintf_s(StateBuff, "STATE : Idle");
			else if (CurState_ == ActorState::Walk)
				sprintf_s(StateBuff, "STATE : Walk");
			else if (CurState_ == ActorState::Run)
				sprintf_s(StateBuff, "STATE : Run");
			else if (CurState_ == ActorState::Attack)
				sprintf_s(StateBuff, "STATE : Attack");
		}

		sprintf_s(szBuff, "Player X: %d, Y: %d", GetPosition().ix(), GetPosition().iy());
		TextOut(GameEngine::GetInst().BackBufferDC(), GetCameraEffectPosition().ix(), GetCameraEffectPosition().iy() - 120, szBuff, static_cast<int>(strlen(szBuff)));
		TextOut(GameEngine::GetInst().BackBufferDC(), GetCameraEffectPosition().ix(), GetCameraEffectPosition().iy() - 100, StateBuff, static_cast<int>(strlen(StateBuff)));

	}
}

bool Actor::IsHit()
{
	// ������ ��Ʈ�ڽ��� �÷��̾� ���ݿ� �ε����ٸ�
	if (true == ActorCollision_->CollisionCheck("PlayerAttack", CollisionType::Rect, CollisionType::Rect))
	{
		return true;
	}
	return false;
}


void Actor::MapCollisionCheckMoveGround()
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
		float4 ForDownPos = GetPosition() + float4{ 0,1.f };	// �̷� ��ġ�� �Ӹ����� ����

		int CurColor = MapColImage_->GetImagePixel(GetPosition());
		int ForDownColor = MapColImage_->GetImagePixel(ForDownPos);
		int Color = MapColImage_->GetImagePixel(CheckPos);
		int TopRightColor = MapColImage_->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = MapColImage_->GetImagePixel(CheckPosTopLeft);


		// �׻� ���� �پ��ֱ�
		if (RGB(0, 0, 0) != ForDownColor && RGB(255, 0, 0) != ForDownColor)
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

}

void Actor::MapCollisionCheckMoveAir()
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

void Actor::MapCollisionCheckMoveGroundDie()
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


		if (RGB(0, 0, 0) != Color && RGB(255, 0, 0) != Color &&
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

void Actor::MapCollisionCheckMoveAirDie()
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
