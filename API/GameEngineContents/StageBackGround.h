#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class StageBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	StageBackGround();
	~StageBackGround();

	// delete Function
	StageBackGround(const StageBackGround& _Other) = delete;
	StageBackGround(StageBackGround&& _Other) noexcept = delete;
	StageBackGround& operator=(const StageBackGround& _Other) = delete;
	StageBackGround& operator=(StageBackGround&& _Other) noexcept = delete;


protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:


};

