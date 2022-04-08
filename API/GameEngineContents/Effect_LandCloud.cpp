#include "Effect_LandCloud.h"
#include <GameEngine/GameEngineRenderer.h>
#include <Windows.h>

Effect_LandCloud::Effect_LandCloud() 
{
}

Effect_LandCloud::~Effect_LandCloud() 
{
}

void Effect_LandCloud::Start()
{
	ActorAnimationRenderer = CreateRenderer();
	ActorAnimationRenderer->CreateFolderAnimation("spr_landcloud", "LandCloud", 0, 6, 0.06f, false);

	ActorAnimationRenderer->ChangeAnimation("LandCloud");
	ActorAnimationRenderer->SetTransColor(RGB(255, 0, 255));	// 이미지에서 제외할 색

	ActorAnimationRenderer->SetPivotType(RenderPivot::BOT);
}

void Effect_LandCloud::Update()
{
	if (true == ActorAnimationRenderer->IsEndAnimation())
	{
		Death();
	}
}

void Effect_LandCloud::Render()
{
}

void Effect_LandCloud::IdleStart()
{
}

void Effect_LandCloud::RunStart()
{
}

void Effect_LandCloud::AttackStart()
{
}

void Effect_LandCloud::IdleUpdate()
{
}

void Effect_LandCloud::RunUpdate()
{
}

void Effect_LandCloud::AttackUpdate()
{
}

