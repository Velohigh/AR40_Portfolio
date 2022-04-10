#pragma once
#include <GameEngine/GameEngineActor.h>

enum class ActorDir
{
	Left,
	Right,
	END

};

enum class ActorState
{
	Idle,
	Walk,
	Run,
	Attack,
	END
};

// 설명 :
class GameEngineImage;
class GameEngineCollision;
class Actor : public GameEngineActor
{
public:
	friend GameEngineLevel;

	// constrcuter destructer
	Actor();
	~Actor();

	// delete Function
	Actor(const Actor& _Other) = delete;
	Actor(Actor&& _Other) noexcept = delete;
	Actor& operator=(const Actor& _Other) = delete;
	Actor& operator=(Actor&& _Other) noexcept = delete;

public:
	inline void SetSpeed(float _Speed)
	{
		Speed_ = _Speed;
	}

	inline void SetDir(ActorDir _Dir)
	{
		CurDir_ = _Dir;
	}

	inline ActorDir GetDir()
	{
		return CurDir_;
	}

protected:
	GameEngineRenderer* ActorAnimationRenderer = nullptr;	// 애니메이션 렌더러
	std::string AnimationName_;						// 재생할 애니메이션
	ActorDir CurDir_ = ActorDir::END;			// 현재 바라보고 있는 방향
	ActorDir PreDir_ = ActorDir::END;			// 이전에 바라보고 있던 방향
	std::string ChangeDirText;

protected:
	float Speed_ = 0;		// 캐릭터 속도
	float AccSpeed_ = 20.f;	// 가속력
	float Gravity_ = 10.f;		// 중력
	float AccGravity_ = 1500.f;	// 중력 가속도

	GameEngineImage* MapColImage_ = nullptr;					// 맵 충돌용 이미지
	GameEngineCollision* ActorCollision_ = nullptr;			// 히트박스 콜리전
	float4 MoveDir = float4::ZERO;			// 이동방향 벡터

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
private:

/// ////////////////////////////////////
/// 	FSM
protected:
	ActorState CurState_;

protected:
	virtual void DirAnimationCheck();
	virtual void ChangeState(ActorState _State);
	virtual void ActorStateUpdate();

protected:
	virtual void IdleStart() = 0;
	virtual void WalkStart() {};
	virtual void RunStart() = 0;
	virtual void AttackStart() = 0;

	virtual void IdleUpdate() = 0;
	virtual void WalkUpdate() {};
	virtual void RunUpdate() = 0;
	virtual void AttackUpdate() = 0;

};

