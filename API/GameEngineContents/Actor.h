#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 :
class Actor : public GameEngineActor
{
public:
	// constrcuter destructer
	Actor();
	~Actor();

	// delete Function
	Actor(const Actor& _Other) = delete;
	Actor(Actor&& _Other) noexcept = delete;
	Actor& operator=(const Actor& _Other) = delete;
	Actor& operator=(Actor&& _Other) noexcept = delete;

protected:
	inline void SetSpeed(float _Speed)
	{
		Speed_ = _Speed;
	}

protected:
	float Speed_ = 0;		// 캐릭터 속도
	float AccSpeed_ = 20.f;	// 가속력
	float4 MoveDir = float4::ZERO;			// 이동방향 벡터

private:

};

