#pragma once
#include "Actor.h"

// ???? :
class Effect_DustCloud : public Actor
{
public:
	// constrcuter destructer
	Effect_DustCloud();
	~Effect_DustCloud();

	// delete Function
	Effect_DustCloud(const Effect_DustCloud& _Other) = delete;
	Effect_DustCloud(Effect_DustCloud&& _Other) noexcept = delete;
	Effect_DustCloud& operator=(const Effect_DustCloud& _Other) = delete;
	Effect_DustCloud& operator=(Effect_DustCloud&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	virtual void IdleStart() override;
	virtual void RunStart() override;
	virtual void AttackStart() override;
	virtual void HurtGroundStart() override;
	virtual void HurtFlyStart() override;


	virtual void IdleUpdate() override;
	virtual void RunUpdate() override;
	virtual void AttackUpdate() override;
	virtual void HurtGroundUpdate() override;
	virtual void HurtFlyUpdate() override;


	float4 Temp = {};

};

