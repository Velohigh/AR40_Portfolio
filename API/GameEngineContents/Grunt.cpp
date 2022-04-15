#include "Grunt.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>

extern float4 g_AttackDir;

Grunt::Grunt() 
{
}

Grunt::~Grunt() 
{
}

void Grunt::Start()
{
	SetScale({ 36,70 });

	// ��Ʈ�ڽ�
	ActorCollision_ = CreateCollision("GruntHitBox", { 36,70 }, { 0,-35 });

	ActorAnimationRenderer = CreateRenderer();

	ActorAnimationRenderer->CreateFolderAnimation("spr_grunt_idle_left", "Grunt_Idle_Left", 0, 7, 0.11f, true);
	ActorAnimationRenderer->CreateFolderAnimation("spr_grunt_idle_right", "Grunt_Idle_Right", 0, 7, 0.11f, true);

	ActorAnimationRenderer->CreateFolderAnimation("spr_grunt_walk_left", "Grunt_Walk_Left", 0, 9, 0.07f, true);
	ActorAnimationRenderer->CreateFolderAnimation("spr_grunt_walk_right", "Grunt_Walk_Right", 0, 9, 0.07f, true);

	ActorAnimationRenderer->CreateFolderAnimation("spr_grunt_turn_left", "Grunt_Turn_Left", 0, 7, 0.06f, true);
	ActorAnimationRenderer->CreateFolderAnimation("spr_grunt_turn_right", "Grunt_Turn_Right", 0, 7, 0.06f, true);

	ActorAnimationRenderer->CreateFolderAnimation("spr_grunt_hurtground_left", "Grunt_HurtGround_Left", 0, 15, 0.06f, false);
	ActorAnimationRenderer->CreateFolderAnimation("spr_grunt_hurtground_right", "Grunt_HurtGround_Right", 0, 15, 0.06f, false);

	ActorAnimationRenderer->CreateFolderAnimation("spr_grunt_hurtfly_left", "Grunt_HurtFly_Left", 0, 1, 0.4f, false);
	ActorAnimationRenderer->CreateFolderAnimation("spr_grunt_hurtfly_right", "Grunt_HurtFly_Right", 0, 1, 0.4f, false);

	ActorAnimationRenderer->ChangeAnimation("Grunt_Idle_Right");
	ActorAnimationRenderer->SetTransColor(RGB(255, 255, 255));	// �̹������� ������ ��

	AnimationName_ = "Grunt_Idle_";
	CurState_ = ActorState::Idle;
	CurDir_ = ActorDir::Right;
	ChangeDirText = "Right";


	ActorAnimationRenderer->SetPivotType(RenderPivot::BOT);


	if (strcmp(GetLevel()->GetNameConstPtr(),"Stage1") == 0)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("room_factory_2_ColMap.bmp");
	}

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�.");
	}

}

void Grunt::Update()
{

	DirAnimationCheck();
	ActorStateUpdate();

}

void Grunt::Render()
{
	DebugRender();
}




//////////////////////////////	
////	FSM
void Grunt::IdleStart()
{
	StateTime[static_cast<int>(ActorState::Idle)] = 0.f;
	AnimationName_ = "Grunt_Idle_";
	ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(0.f);
}

void Grunt::WalkStart()
{
	StateTime[static_cast<int>(ActorState::Walk)] = 0.f;
	AnimationName_ = "Grunt_Walk_";
	ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(80.f);
}

void Grunt::TurnStart()
{
	StateTime[static_cast<int>(ActorState::Turn)] = 0.f;
	AnimationName_ = "Grunt_Turn_";
	ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(0.f);
}

void Grunt::RunStart()
{
}

void Grunt::AttackStart()
{
}

void Grunt::HurtGroundStart()
{
	StateTime[static_cast<int>(ActorState::HurtGround)] = 0.f;
	AnimationName_ = "Grunt_HurtGround_";
	ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);

}

void Grunt::HurtFlyStart()
{
	SetPosition(GetPosition() + float4{ 0,-2 });
	StateTime[static_cast<int>(ActorState::HurtGround)] = 0.f;
	AnimationName_ = "Grunt_HurtFly_";
	ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(0.f);

	MoveDir = g_AttackDir * 800;

}

void Grunt::IdleUpdate()
{
	// ���� �ൿ
	StateTime[static_cast<int>(ActorState::Idle)] += GameEngineTime::GetDeltaTime();
	if (StateTime[static_cast<int>(ActorState::Idle)] >= 2 && bPatrol_ == true)
	{
		ChangeState(ActorState::Turn);
		return;
	}

	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}
}

void Grunt::WalkUpdate()
{
	StateTime[static_cast<int>(ActorState::Walk)] += GameEngineTime::GetDeltaTime();

	if (StateTime[static_cast<int>(ActorState::Walk)] >= 5)
	{
		ChangeState(ActorState::Idle);
		return;
	}

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

void Grunt::TurnUpdate()
{
	if (true == ActorAnimationRenderer->IsEndAnimation())
	{
		ChangeState(ActorState::Walk);
		if (CurDir_ == ActorDir::Right)
		{
			CurDir_ = ActorDir::Left;
		}
		else if (CurDir_ == ActorDir::Left)
		{
			CurDir_ = ActorDir::Right;
		}
		return;
	}

	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}
}


void Grunt::RunUpdate()
{
	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}
}

void Grunt::AttackUpdate()
{
	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}
}

void Grunt::HurtGroundUpdate()
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

void Grunt::HurtFlyUpdate()
{

	// ���߿� �� �����ϰ�� �߷¿����� �޴´�.
	// �߷� ���ӵ��� ���� ���� �ӵ�.
	{
		// �������ǿ��� ���ϴ� ��ġ�� �ȼ��� ������ ���� �� �ִ�.
		int RColor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
		Gravity_ += AccGravity_ * GameEngineTime::GetDeltaTime();
		if (MoveDir.y > 0.f)
		{
			if (RGB(0, 0, 0) == RColor || RGB(255, 0, 0) == RColor)	// ���� ���� ��� 
			{
				ChangeState(ActorState::HurtGround);
				return;
			}
		}
		MoveDir += float4::DOWN * Gravity_ * GameEngineTime::GetDeltaTime();
	}

	MapCollisionCheckMoveAirDie();

}



