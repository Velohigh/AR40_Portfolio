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
	Attack,
	Fall,
	Dodge,
	END
};

// 설명 :
class GameEngineImage;
class GameEngineCollision;
class Player : public Actor
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
	GameEngineRenderer* PlayerAnimationRenderer;	// 애니메이션 렌더러
	std::string AnimationName_;						// 재생할 애니메이션
	PlayerDir CurDir_;								// 현재 바라보고 있는 방향
	std::string ChangeDirText;

private:
	float JumpPower_ = 450.f;
	float Gravity_ = 10.f;		// 중력
	float AccGravity_ = 1500.f;	// 중력 가속도
	GameEngineImage* MapColImage_;					// 맵 충돌용 이미지
	GameEngineCollision* PlayerCollision_;			// 히트박스 콜리전

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

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
	void AttackStart();
	void FallStart();
	void DodgeStart();

	void IdleUpdate();
	void IdleToRunUpdate();
	void RunUpdate();
	void RunToIdleUpdate();
	void JumpUpdate();
	void AttackUpdate();
	void FallUpdate();
	void DodgeUpdate();
};

