#pragma once
#include "Actor.h"

// Ό³Έν :
class Effect_LandCloud : public Actor
{
public:
	// constrcuter destructer
	Effect_LandCloud();
	~Effect_LandCloud();

	// delete Function
	Effect_LandCloud(const Effect_LandCloud& _Other) = delete;
	Effect_LandCloud(Effect_LandCloud&& _Other) noexcept = delete;
	Effect_LandCloud& operator=(const Effect_LandCloud& _Other) = delete;
	Effect_LandCloud& operator=(Effect_LandCloud&& _Other) noexcept = delete;

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

