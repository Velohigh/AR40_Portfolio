#include "Grunt.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>


Grunt::Grunt() 
{
}

Grunt::~Grunt() 
{
}

void Grunt::Start()
{
	SetScale({ 36,70 });

	// 히트박스
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


	ActorAnimationRenderer->ChangeAnimation("Grunt_Idle_Right");
	ActorAnimationRenderer->SetTransColor(RGB(255, 255, 255));	// 이미지에서 제외할 색

	AnimationName_ = "Grunt_Idle_";
	CurState_ = ActorState::Idle;
	CurDir_ = ActorDir::Right;
	ChangeDirText = "Right";


	ActorAnimationRenderer->SetPivotType(RenderPivot::BOT);
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
	SetSpeed(0.f);	// @@@나중에 수정

}

void Grunt::HurtFlyStart()
{
}

void Grunt::IdleUpdate()
{
	// 정찰 행동
	StateTime[static_cast<int>(ActorState::Idle)] += GameEngineTime::GetDeltaTime();
	if (StateTime[static_cast<int>(ActorState::Idle)] >= 2 && bPatrol_ == true)
	{
		ChangeState(ActorState::Turn);
		return;
	}

	// 플레이어 공격에 맞으면 사망
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtGround);
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

	// 플레이어 공격에 맞으면 사망
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtGround);
		return;
	}

	// 좌우 이동
	if (CurDir_ == ActorDir::Right)
	{
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
	}

	else if (CurDir_ == ActorDir::Left)
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
	}
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

	// 플레이어 공격에 맞으면 사망
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtGround);
		return;
	}
}


void Grunt::RunUpdate()
{
	// 플레이어 공격에 맞으면 사망
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtGround);
		return;
	}
}

void Grunt::AttackUpdate()
{
	// 플레이어 공격에 맞으면 사망
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtGround);
		return;
	}
}

void Grunt::HurtGroundUpdate()
{
	if (true == ActorAnimationRenderer->IsEndAnimation())
	{
		ActorCollision_->Death();
	}
	
}

void Grunt::HurtFlyUpdate()
{
}



