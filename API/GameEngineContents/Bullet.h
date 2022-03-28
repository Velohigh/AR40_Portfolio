#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class Bullet : public GameEngineActor
{
public:
	// constrcuter destructer
	Bullet();
	~Bullet();

	// delete Function
	Bullet(const Bullet& _Other) = delete;
	Bullet(Bullet&& _Other) noexcept = delete;
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

	float Time;

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:



	
};

