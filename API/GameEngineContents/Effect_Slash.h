#pragma once
#include "Actor.h"

// Ό³Έν :
class Effect_Slash : public Actor
{
public:
	// constrcuter destructer
	Effect_Slash();
	~Effect_Slash();

	// delete Function
	Effect_Slash(const Effect_Slash& _Other) = delete;
	Effect_Slash(Effect_Slash&& _Other) noexcept = delete;
	Effect_Slash& operator=(const Effect_Slash& _Other) = delete;
	Effect_Slash& operator=(Effect_Slash&& _Other) noexcept = delete;

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


	virtual void HurtGroundStart() override;
	virtual void HurtFlyStart() override;

	virtual void HurtGroundUpdate() override;
	virtual void HurtFlyUpdate() override;

};

