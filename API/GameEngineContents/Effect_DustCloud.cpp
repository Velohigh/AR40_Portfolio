#include "Effect_DustCloud.h"
#include <GameEngine/GameEngineRenderer.h>
#include <Windows.h>

Effect_DustCloud::Effect_DustCloud() 
{
}

Effect_DustCloud::~Effect_DustCloud() 
{
}

void Effect_DustCloud::Start()
{
	ActorAnimationRenderer = CreateRenderer();
	ActorAnimationRenderer->CreateFolderAnimation("spr_dustcloud", "DustCloud", 0, 6, 0.06f, false);

	ActorAnimationRenderer->ChangeAnimation("DustCloud");
	ActorAnimationRenderer->SetTransColor(RGB(255, 255, 255));	// 이미지에서 제외할 색

	ActorAnimationRenderer->SetPivotType(RenderPivot::BOT);

	Speed_ = 100.f;

}

void Effect_DustCloud::Update()
{
	if (CurDir_ == ActorDir::Right)
	{
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else if (CurDir_ == ActorDir::Left)
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
	}

	if (true == ActorAnimationRenderer->IsEndAnimation())
	{
		Death();
	}
}

void Effect_DustCloud::Render()
{
}

void Effect_DustCloud::IdleStart()
{
}

void Effect_DustCloud::RunStart()
{
}

void Effect_DustCloud::AttackStart()
{
}

void Effect_DustCloud::IdleUpdate()
{
}

void Effect_DustCloud::RunUpdate()
{
}

void Effect_DustCloud::AttackUpdate()
{
}

