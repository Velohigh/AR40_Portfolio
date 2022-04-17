#include "Effect_Blood_Remain.h"
#include <GameEngine/GameEngineRenderer.h>
#include <Windows.h>
#include <random>

extern float4 g_AttackDir;

Effect_Blood_Remain::Effect_Blood_Remain() 
{
}

Effect_Blood_Remain::~Effect_Blood_Remain() 
{
}

void Effect_Blood_Remain::Start()
{
	ActorRenderer_ = CreateRenderer();

	// 오른쪽방향 공격일경우
	if (g_AttackDir.x >= 0)
	{
		ActorRenderer_->SetPivot({ 70.f, -10.f });
		ActorRenderer_->SetImage("effect_blood_remain1_right.bmp");
	}
	else if (g_AttackDir.x < 0)
	{
		ActorRenderer_->SetPivot({ -70.f, -10.f });
		ActorRenderer_->SetImage("effect_blood_remain1_left.bmp");
	}

	ActorRenderer_->SetTransColor(RGB(255, 0, 255));	// 이미지에서 제외할 색

	ActorRenderer_->SetPivotType(RenderPivot::BOT);

}

void Effect_Blood_Remain::Update()
{
}

void Effect_Blood_Remain::Render()
{
}

