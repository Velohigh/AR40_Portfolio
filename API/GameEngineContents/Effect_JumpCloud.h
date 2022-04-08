#pragma once
#include "Actor.h"

// Ό³Έν :
class Effect_JumpCloud : public Actor
{
public:
	// constrcuter destructer
	Effect_JumpCloud();
	~Effect_JumpCloud();

	// delete Function
	Effect_JumpCloud(const Effect_JumpCloud& _Other) = delete;
	Effect_JumpCloud(Effect_JumpCloud&& _Other) noexcept = delete;
	Effect_JumpCloud& operator=(const Effect_JumpCloud& _Other) = delete;
	Effect_JumpCloud& operator=(Effect_JumpCloud&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:


	virtual void IdleStart() override;
	virtual void RunStart() override;
	virtual void AttackStart() override;
	virtual void IdleUpdate() override;
	virtual void RunUpdate() override;
	virtual void AttackUpdate() override;

};

