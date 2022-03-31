#pragma once
#include <GameEngine/GameEngineActor.h>

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

};

