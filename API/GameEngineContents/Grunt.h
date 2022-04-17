#pragma once
#include "Actor.h"


// 설명 :
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
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	GameEngineRenderer* NewBloodAnimation = nullptr;

private:
	///////////////////////////////
	////	FSM
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

