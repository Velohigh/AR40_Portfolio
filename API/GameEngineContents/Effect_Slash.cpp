#include "Effect_Slash.h"
#include <GameEngine/GameEngineRenderer.h>
#include <Windows.h>
#include "Player.h"

Effect_Slash::Effect_Slash() 
{
}

Effect_Slash::~Effect_Slash() 
{
}

void Effect_Slash::Start()
{
	ActorAnimationRenderer = CreateRenderer();
	ActorAnimationRenderer->CreateFolderAnimation("spr_slash", "Slash", 0, 4, 0.0392f, false);

	ActorAnimationRenderer->ChangeAnimation("Slash");
	ActorAnimationRenderer->SetTransColor(RGB(255, 255, 255));	// 이미지에서 제외할 색

	ActorAnimationRenderer->SetPivotType(RenderPivot::BOT);

}

void Effect_Slash::Update()
{
	SetPosition(Player::MainPlayer->GetPosition());

	if (true == ActorAnimationRenderer->IsEndAnimation())
	{
		Death();
	}

}

void Effect_Slash::Render()
{
}

void Effect_Slash::IdleStart()
{
}

void Effect_Slash::RunStart()
{
}

void Effect_Slash::AttackStart()
{
}

void Effect_Slash::IdleUpdate()
{
}

void Effect_Slash::RunUpdate()
{
}

void Effect_Slash::AttackUpdate()
{
}

void Effect_Slash::HurtGroundStart()
{
}

void Effect_Slash::HurtFlyStart()
{
}

void Effect_Slash::HurtGroundUpdate()
{
}

void Effect_Slash::HurtFlyUpdate()
{
}

