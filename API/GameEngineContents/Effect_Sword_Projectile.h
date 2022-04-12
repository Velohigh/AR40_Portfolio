#pragma once
#include "Actor.h"

// Ό³Έν :
class Effect_Sword_Projectile : public Actor
{
public:
	// constrcuter destructer
	Effect_Sword_Projectile();
	~Effect_Sword_Projectile();

	// delete Function
	Effect_Sword_Projectile(const Effect_Sword_Projectile& _Other) = delete;
	Effect_Sword_Projectile(Effect_Sword_Projectile&& _Other) noexcept = delete;
	Effect_Sword_Projectile& operator=(const Effect_Sword_Projectile& _Other) = delete;
	Effect_Sword_Projectile& operator=(Effect_Sword_Projectile&& _Other) noexcept = delete;

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

