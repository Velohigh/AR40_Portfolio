#include "Effect_Sword_Projectile.h"
#include <GameEngine/GameEngineRenderer.h>
#include <Windows.h>


Effect_Sword_Projectile::Effect_Sword_Projectile() 
{
}

Effect_Sword_Projectile::~Effect_Sword_Projectile() 
{
}

void Effect_Sword_Projectile::Start()
{
	ActorAnimationRenderer = CreateRenderer();
	ActorAnimationRenderer->CreateFolderAnimation("spr_sword_projectile", "SwordProjectile", 0, 2, 0.06f, false);

	ActorAnimationRenderer->ChangeAnimation("SwordProjectile");
	ActorAnimationRenderer->SetTransColor(RGB(255, 255, 255));	// 이미지에서 제외할 색

	ActorAnimationRenderer->SetPivotType(RenderPivot::BOT);

}

void Effect_Sword_Projectile::Update()
{
	if (true == ActorAnimationRenderer->IsEndAnimation())
	{
		Death();
	}
}

void Effect_Sword_Projectile::Render()
{
}

void Effect_Sword_Projectile::IdleStart()
{
}

void Effect_Sword_Projectile::RunStart()
{
}

void Effect_Sword_Projectile::AttackStart()
{
}

void Effect_Sword_Projectile::IdleUpdate()
{
}

void Effect_Sword_Projectile::RunUpdate()
{
}

void Effect_Sword_Projectile::AttackUpdate()
{
}

