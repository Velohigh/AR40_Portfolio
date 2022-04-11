#include "Grunt.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>


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

	ActorAnimationRenderer->ChangeAnimation("Grunt_Idle_Right");
	ActorAnimationRenderer->SetTransColor(RGB(255, 255, 255));	// 이미지에서 제외할 색

	AnimationName_ = "Grunt_Idle_";
	CurState_ = ActorState::Idle;
	CurDir_ = ActorDir::Right;


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
	AnimationName_ = "Grunt_Idle_";
	ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
}

void Grunt::WalkStart()
{
	AnimationName_ = "Grunt_Walk_";
	ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
}

void Grunt::RunStart()
{
}

void Grunt::AttackStart()
{
}

void Grunt::IdleUpdate()
{
}

void Grunt::WalkUpdate()
{
}

void Grunt::RunUpdate()
{
}

void Grunt::AttackUpdate()
{
}


