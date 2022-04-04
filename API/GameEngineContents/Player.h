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

// 설명 :
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
	float Speed_;		// 캐릭터 속도
	float Gravity_;		// 중력
	float AccGravity_;	// 중력 가속도
	GameEngineImage* MapColImage_;
	GameEngineCollision* PlayerCollision_;

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

	// 키
	void KeyCheck();			

	// 카메라
	void CameraLock();			// 맵 끝까지 이동시 카메라 이동 잠금

	// 콜리전
	void CollisionDeathCheck();	// 충돌시 콜리전 사망처리
	void CollisionCheck();		// 충돌 체크
	 

	//////////////////////
	////	FSM
private:
	PlayerState CurState_;

	bool IsMoveKey();	// 무브 키(wasd)를 눌렀는지 확인하는 함수, 눌렀다면 true

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

