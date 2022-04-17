#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν :
class GameEngineRenderer;
class Effect_Blood_Remain : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_Blood_Remain();
	~Effect_Blood_Remain();

	// delete Function
	Effect_Blood_Remain(const Effect_Blood_Remain& _Other) = delete;
	Effect_Blood_Remain(Effect_Blood_Remain&& _Other) noexcept = delete;
	Effect_Blood_Remain& operator=(const Effect_Blood_Remain& _Other) = delete;
	Effect_Blood_Remain& operator=(Effect_Blood_Remain&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	GameEngineRenderer* ActorRenderer_;


};

