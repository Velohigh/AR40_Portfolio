#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Actor.h"

enum class PlayerDir
{
	Left,
	Right,
	END

};

enum class PlayerState
{
	Idle,
	IdleToRun,
	Run,
	RunToIdle,
	Jump,
	Landing,
	Attack,
	Fall,
	Dodge,
	END
};

// ���� :
class Mouse;
class GameEngineImage;
class GameEngineCollision;
class Player : public Actor
{
public:
	static Player* MainPlayer;	// �����ϱ� ���� static���� �������ش�.
	// static std::vector<InventoryItem> ;

	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	GameEngineRenderer* PlayerAnimationRenderer;	// �ִϸ��̼� ������
	std::string AnimationName_;						// ����� �ִϸ��̼�
	PlayerDir CurDir_;								// ���� �ٶ󺸰� �ִ� ����
	std::string ChangeDirText;

private:
	float JumpPower_ = 450.f;
	float Gravity_ = 10.f;		// �߷�
	float AccGravity_ = 2200.f;	// �߷� ���ӵ�
	GameEngineImage* MapColImage_;					// �� �浹�� �̹���
	GameEngineCollision* PlayerCollision_;			// ��Ʈ�ڽ� �ݸ���
	Mouse* Mouse_ = nullptr;
	int AttackCount_ = 0;
	float StateTime[static_cast<int>(PlayerState::END)];		// �ش� ���°� �ǰ� ���� �ð�


	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

	void LevelChangeStart() override;


	// ī�޶�
	void CameraLock();			// �� ������ �̵��� ī�޶� �̵� ���

	// �ݸ���
	void CollisionDeathCheck();	// �浹�� �ݸ��� ���ó��
	void CollisionCheck();		// �浹 üũ
	 
	// ����׿�
	virtual void DebugRender() override;


	//////////////////////
	////	FSM
private:
	PlayerState CurState_;

	bool IsMoveKey();	// ���� Ű(wasd)�� �������� Ȯ���ϴ� �Լ�, �����ٸ� true

protected:
	void DirAnimationCheck();
	void ChangeState(PlayerState _State);
	void PlayerStateUpdate();

private:
	void IdleStart();
	void IdleToRunStart();
	void RunStart();
	void RunToIdleStart();
	void JumpStart();
	void LandingStart();
	void AttackStart();
	void FallStart();
	void DodgeStart();

	void IdleUpdate();
	void IdleToRunUpdate();
	void RunUpdate();
	void RunToIdleUpdate();
	void JumpUpdate();
	void LandingUpdate();
	void AttackUpdate();
	void FallUpdate();
	void DodgeUpdate();


	void OnGroundUpdate();

	// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
	void MapCollisionCheckMoveAir();
	void MapCollisionCheckMoveGround();

};

