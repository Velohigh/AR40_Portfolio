#include "Gangster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>


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

void Gangster::IdleUpdate()
{
}

void Gangster::WalkUpdate()
{
}

void Gangster::RunUpdate()
{
}

void Gangster::AttackUpdate()
{
}

void Gangster::HurtGroundStart()
{
}

void Gangster::HurtFlyStart()
{
}

void Gangster::HurtGroundUpdate()
{
}

void Gangster::HurtFlyUpdate()
{
}

void Gangster::TurnStart()
{
}

void Gangster::TurnUpdate()
{
}

