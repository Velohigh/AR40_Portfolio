#include "Gangster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>

extern float4 g_AttackDir;

Gangster::Gangster() 
{
}

Gangster::~Gangster() 
{
}

void Gangster::Start()
{
	SetScale({ 36,70 });

	// ��Ʈ�ڽ�
	ActorCollision_ = CreateCollision("GangsterHitBox", { 36,70 }, { 0,-35 });

	ActorAnimationRenderer = CreateRenderer();

	ActorAnimationRenderer->CreateFolderAnimation("spr_gangster_idle_left", "Gangster_Idle_Left", 0, 7, 0.12f, true);
	ActorAnimationRenderer->CreateFolderAnimation("spr_gangster_idle_right", "Gangster_Idle_Right", 0, 7, 0.12f, true);

	ActorAnimationRenderer->CreateFolderAnimation("spr_gangsterhurtground_left", "Gangster_HurtGround_Left", 0, 13, 0.07f, false);
	ActorAnimationRenderer->CreateFolderAnimation("spr_gangsterhurtground_right", "Gangster_HurtGround_Right", 0, 7, 0.07f, false);

	ActorAnimationRenderer->CreateFolderAnimation("spr_gangsterhurtfly_left", "Gangster_HurtFly_Left", 0, 1, 0.4f, false);
	ActorAnimationRenderer->CreateFolderAnimation("spr_gangsterhurtfly_right", "Gangster_HurtFly_Right", 0, 1, 0.4f, false);


	ActorAnimationRenderer->ChangeAnimation("Gangster_Idle_Right");
	ActorAnimationRenderer->SetTransColor(RGB(255, 255, 255));	// �̹������� ������ ��

	AnimationName_ = "Gangster_Idle_";
	CurState_ = ActorState::Idle;
	CurDir_ = ActorDir::Right;


	ActorAnimationRenderer->SetPivotType(RenderPivot::BOT);

	// �浹 �� ����
	if (strcmp(GetLevel()->GetNameConstPtr(), "Stage1") == 0)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("room_factory_2_ColMap.bmp");
	}

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�.");
	}

}

void Gangster::Update()
{
	DirAnimationCheck();
	ActorStateUpdate();

}

void Gangster::Render()
{
	DebugRender();
}

void Gangster::IdleStart()
{
	AnimationName_ = "Gangster_Idle_";
	ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(0.f);

}

void Gangster::WalkStart()
{
}

void Gangster::RunStart()
{
	AnimationName_ = "Gangster_Walk_";
	ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);

}

void Gangster::AttackStart()
{
}

void Gangster::HurtGroundStart()
{
	StateTime[static_cast<int>(ActorState::HurtGround)] = 0.f;
	AnimationName_ = "Gangster_HurtGround_";
	ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);

}

void Gangster::HurtFlyStart()
{
	SetPosition(GetPosition() + float4{ 0,-2 });
	StateTime[static_cast<int>(ActorState::HurtGround)] = 0.f;
	AnimationName_ = "Gangster_HurtFly_";
	ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(0.f);

	MoveDir = g_AttackDir * 800;	// �¾����� �˹�

}

void Gangster::TurnStart()
{
}
///////////////////////////////////////////////////////
///////////////////////// Update
void Gangster::IdleUpdate()
{
	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}
}

void Gangster::WalkUpdate()
{

	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}

	// �¿� �̵�
	if (CurDir_ == ActorDir::Right)
	{
		MoveDir = float4::RIGHT;
	}

	else if (CurDir_ == ActorDir::Left)
	{
		MoveDir = float4::LEFT;
	}

	MapCollisionCheckMoveGround();
}

void Gangster::TurnUpdate()
{

	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}
}


void Gangster::RunUpdate()
{
	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}
}

void Gangster::AttackUpdate()
{
	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}
}


void Gangster::HurtGroundUpdate()
{
	if (true == ActorAnimationRenderer->IsEndAnimation())
	{
		ActorCollision_->Death();
	}

	MoveDir += -MoveDir * GameEngineTime::GetDeltaTime() * 3.4;

	if (1.f >= MoveDir.Len2D())
	{
		MoveDir = float4::ZERO;
	}

	MapCollisionCheckMoveGroundDie();
}

void Gangster::HurtFlyUpdate()
{
	// ���߿� �� �����ϰ�� �߷¿����� �޴´�.
// �߷� ���ӵ��� ���� ���� �ӵ�.
	{
		// �������ǿ��� ���ϴ� ��ġ�� �ȼ��� ������ ���� �� �ִ�.
		int RColor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
		Gravity_ += AccGravity_ * GameEngineTime::GetDeltaTime();
		if (RGB(0, 0, 0) == RColor || RGB(255, 0, 0) == RColor)	// ���� ���� ��� 
		{
			ChangeState(ActorState::HurtGround);
			return;
		}
		MoveDir += float4::DOWN * Gravity_ * GameEngineTime::GetDeltaTime();
	}

	MapCollisionCheckMoveAirDie();
}



