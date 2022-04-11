#pragma once
#include "Actor.h"

// Ό³Έν :
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


	virtual void IdleUpdate() override;
	virtual void WalkUpdate() override;
	virtual void TurnUpdate() override;
	virtual void RunUpdate() override;
	virtual void AttackUpdate() override;


};

