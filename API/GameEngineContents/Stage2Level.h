#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class Stage2Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Stage2Level();
	~Stage2Level();

	// delete Function
	Stage2Level(const Stage2Level& _Other) = delete;
	Stage2Level(Stage2Level&& _Other) noexcept = delete;
	Stage2Level& operator=(const Stage2Level& _Other) = delete;
	Stage2Level& operator=(Stage2Level&& _Other) noexcept = delete;

protected:
	virtual void Loading() override;
	virtual void Update() override;
	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd() override;

private:





};

