#include "Gangster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>


Gangster::Gangster() 
{
}

Gangster::~Gangster() 
{
}

void Gangster::Start()
{
	SetScale({ 36,70 });

	// 히트박스
	ActorCollision_ = CreateCollision("GangsterHitBox", { 36,70 }, { 0,-35 });

	ActorAnimationRenderer = CreateRenderer();

	ActorAnimationRenderer->CreateFolderAnimation("spr_gangster_idle_left", "Gangster_Idle_Left", 0, 7, 0.12f, true);
	ActorAnimationRenderer->CreateFolderAnimation("spr_gangster_idle_right", "Gangster_Idle_Right", 0, 7, 0.12f, true);

	ActorAnimationRenderer->CreateFolderAnimation("spr_gangsterhurtground_left", "Gangster_HurtGround_Left", 0, 13, 0.07f, false);
	ActorAnimationRenderer->CreateFolderAnimation("spr_gangsterhurtground_right", "Gangster_HurtGround_Right", 0, 7, 0.07f, false);

	ActorAnimationRenderer->CreateFolderAnimation("spr_gangsterhurtfly_left", "Gangster_HurtFly_Left", 0, 1, 0.4f, false);
	ActorAnimationRenderer->CreateFolderAnimation("spr_gangsterhurtfly_right", "Gangster_HurtFly_Right", 0, 1, 0.4f, false);


	ActorAnimationRenderer->ChangeAnimation("Gangster_Idle_Right");
	ActorAnimationRenderer->SetTransColor(RGB(255, 255, 255));	// 이미지에서 제외할 색

	AnimationName_ = "Gangster_Idle_";
	CurState_ = ActorState::Idle;
	CurDir_ = ActorDir::Right;


	ActorAnimationRenderer->SetPivotType(RenderPivot::BOT);

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
	SetSpeed(0.f);	// @@@나중에 수정

}

void Gangster::HurtFlyStart()
{
	StateTime[static_cast<int>(ActorState::HurtGround)] = 0.f;
	AnimationName_ = "Gangster_HurtFly_";
	ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(0.f);	// @@@나중에 수정

}

void Gangster::TurnStart()
{
}
///////////////////////////////////////////////////////
///////////////////////// Update
void Gangster::IdleUpdate()
{
	// 플레이어 공격에 맞으면 사망
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtGround);
		return;
	}
}

void Gangster::WalkUpdate()
{
	// 플레이어 공격에 맞으면 사망
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtGround);
		return;
	}
}

void Gangster::TurnUpdate()
{
}


void Gangster::RunUpdate()
{
}

void Gangster::AttackUpdate()
{
}


void Gangster::HurtGroundUpdate()
{
	if (true == ActorAnimationRenderer->IsEndAnimation())
	{
		ActorCollision_->Death();
	}
}

void Gangster::HurtFlyUpdate()
{
}



