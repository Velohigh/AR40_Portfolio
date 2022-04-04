#pragma once
#include <GameEngine/GameEngineActor.h>

enum PlayerState
{
	Idle,
	Attack,
	Fall,
	Dodge,
	Move,
	Max
};

// ���� :
class GameEngineImage;
class GameEngineCollision;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:

private:
	float Speed_;		// ĳ���� �ӵ�
	float Gravity_;		// �߷�
	float AccGravity_;	// �߷� ���ӵ�
	GameEngineImage* MapColImage_;
	GameEngineCollision* PlayerCollision_;

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

	// Ű
	void KeyCheck();			

	// ī�޶�
	void CameraLock();			// �� ������ �̵��� ī�޶� �̵� ���

	// �ݸ���
	void CollisionDeathCheck();	// �浹�� �ݸ��� ���ó��
	void CollisionCheck();		// �浹 üũ
	 

	//////////////////////
	////	FSM
private:
	PlayerState CurState_;

	bool IsMoveKey();	// ���� Ű(wasd)�� �������� Ȯ���ϴ� �Լ�, �����ٸ� true

public:
	void ChangeState(PlayerState _State);
	void StateUpdate();

private:
	void IdleStart();
	void AttackStart();
	void FallStart();
	void DodgeStart();
	void MoveStart();

	void IdleUpdate();
	void AttackUpdate();
	void FallUpdate();
	void DodgeUpdate();
	void MoveUpdate();
};

