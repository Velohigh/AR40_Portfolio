#include "Bullet.h"
#include <GameEngineBase/GameEngineTime.h>

Bullet::Bullet() 
{
}

Bullet::~Bullet() 
{
}

void Bullet::Start()
{
	CreateRenderer("Idle.bmp");
	Death(2.0f);	// 액터가 일정 시간후 사망한다.
}

void Bullet::Update()
{
	//Time -= GameEngineTime::GetDeltaTime();

	//if (0.0f >= Time)
	//{
	//	Death();
	//	return;
	//}

	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 200.0f);
}

void Bullet::Render()
{
}

