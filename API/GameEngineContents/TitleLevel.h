#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include "Level.h"

// Ό³Έν :
class TitleLevel : public Level
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	virtual void Loading() override;
	virtual void Update() override;
	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd() override;

private:
	GameEngineSoundPlayer BgmPlayer;
	GameEngineSoundPlayer RainSound;



};

