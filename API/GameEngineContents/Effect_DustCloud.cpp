#include "Effect_DustCloud.h"
#include <GameEngine/GameEngineRenderer.h>
#include <Windows.h>
#include <random>

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
	ActorAnimationRenderer->SetTransColor(RGB(255, 255, 255));	// �̹������� ������ ��

	ActorAnimationRenderer->SetPivotType(RenderPivot::CENTER);

	// �ܺ� ����̽� ���������� �������� �޾ƿ´�.
	std::random_device rd;
	std::mt19937_64 mt_(rd());	// ���������� �õ带 �����Ѵ�.

	std::uniform_int_distribution<int> IntRange(80, 300);	// ���� ����

	Speed_ = static_cast<float>(IntRange(mt_));

	std::uniform_real_distribution<float> FloatRange(0, 0.7f);

	Temp = float4{ 0,FloatRange(mt_) };
}

void Effect_DustCloud::Update()
{
	if (CurDir_ == ActorDir::Right)
	{
		SetMove((float4::RIGHT - Temp) * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else if (CurDir_ == ActorDir::Left)
	{
		SetMove((float4::LEFT - Temp) * GameEngineTime::GetDeltaTime() * Speed_);
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

void Effect_DustCloud::HurtGroundStart()
{
}

void Effect_DustCloud::HurtFlyStart()
{
}

void Effect_DustCloud::HurtGroundUpdate()
{
}

void Effect_DustCloud::HurtFlyUpdate()
{
}

