#pragma once
#include "Actor.h"


// Ό³Έν :
class Grunt : public Actor
{
public:
	// constrcuter destructer
	Grunt();
	~Grunt();

	// delete Function
	Grunt(const Grunt& _Other) = delete;
	Grunt(Grunt&& _Other) noexcept = delete;
	Grunt& operator=(const Grunt& _Other) = delete;
	Grunt& operator=(Grunt&& _Other) noexcept = delete;

protected:


private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;


	///////////////////////////////
	////	FSM
	virtual void IdleStart() override;
	virtual void WalkStart() override;
	virtual void RunStart() override;
	virtual void AttackStart() override;

	virtual void IdleUpdate() override;
	virtual void WalkUpdate() override;
	virtual void RunUpdate() override;
	virtual void AttackUpdate() override;

};

