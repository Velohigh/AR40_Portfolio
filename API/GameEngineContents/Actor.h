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

// ���� :
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
	GameEngineRenderer* ActorAnimationRenderer = nullptr;	// �ִϸ��̼� ������
	std::string AnimationName_;						// ����� �ִϸ��̼�
	ActorDir CurDir_ = ActorDir::END;			// ���� �ٶ󺸰� �ִ� ����
	ActorDir PreDir_ = ActorDir::END;			// ������ �ٶ󺸰� �ִ� ����
	std::string ChangeDirText;

protected:
	float Speed_ = 0;		// ĳ���� �ӵ�
	float AccSpeed_ = 20.f;	// ���ӷ�
	float Gravity_ = 10.f;		// �߷�
	float AccGravity_ = 1500.f;	// �߷� ���ӵ�

	GameEngineImage* MapColImage_ = nullptr;					// �� �浹�� �̹���
	GameEngineCollision* ActorCollision_ = nullptr;			// ��Ʈ�ڽ� �ݸ���
	float4 MoveDir = float4::ZERO;			// �̵����� ����

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

