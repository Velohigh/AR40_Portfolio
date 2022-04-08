#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
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
	float Speed_ = 0;		// ĳ���� �ӵ�
	float AccSpeed_ = 20.f;	// ���ӷ�
	float4 MoveDir = float4::ZERO;			// �̵����� ����

private:

};

