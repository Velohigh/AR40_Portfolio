#include "Effect_JumpCloud.h"
#include <GameEngine/GameEngineRenderer.h>
#include <Windows.h>

Effect_JumpCloud::Effect_JumpCloud() 
{
}

Effect_JumpCloud::~Effect_JumpCloud() 
{
}

void Effect_JumpCloud::Start()
{
	ActorAnimationRenderer = CreateRenderer();
	ActorAnimationRenderer->CreateFolderAnimation("spr_jumpcloud", "JumpCloud", 0, 3, 0.06f, false);

	ActorAnimationRenderer->ChangeAnimation("JumpCloud");
	ActorAnimationRenderer->SetTransColor(RGB(255, 255, 255));	// 이미지에서 제외할 색

	ActorAnimationRenderer->SetPivotType(RenderPivot::BOT);

}

void Effect_JumpCloud::Update()
{
	if (true == ActorAnimationRenderer->IsEndAnimation())
	{
		Death();
	}
}

void Effect_JumpCloud::Render()
{
}

void Effect_JumpCloud::IdleStart()
{
}

void Effect_JumpCloud::RunStart()
{
}

void Effect_JumpCloud::AttackStart()
{
}

void Effect_JumpCloud::IdleUpdate()
{
}

void Effect_JumpCloud::RunUpdate()
{
}

void Effect_JumpCloud::AttackUpdate()
{
}

