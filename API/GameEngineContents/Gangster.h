#pragma once
#include "Actor.h"

// 설명 :
class Gangster : public Actor
{
public:
	// constrcuter destructer
	Gangster();
	~Gangster();

	// delete Function
	Gangster(const Gangster& _Other) = delete;
	Gangster(Gangster&& _Other) noexcept = delete;
	Gangster& operator=(const Gangster& _Other) = delete;
	Gangster& operator=(Gangster&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	virtual void IdleStart() override;
	virtual void WalkStart() override;
	virtual void TurnStart() override;
	virtual void RunStart() override;
	virtual void AttackStart() override;
	virtual void HurtGroundStart() override;
	virtual void HurtFlyStart() override;


	virtual void IdleUpdate() override;
	virtual void WalkUpdate() override;
	virtual void TurnUpdate() override;
	virtual void RunUpdate() override;
	virtual void AttackUpdate() override;
	virtual void HurtGroundUpdate() override;
	virtual void HurtFlyUpdate() override;



	// Actor을(를) 통해 상속됨




};

