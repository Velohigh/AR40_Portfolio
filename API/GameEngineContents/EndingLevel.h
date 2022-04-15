#pragma once
#include "Level.h"


// Ό³Έν :
class EndingLevel : public Level
{
public:
	// constrcuter destructer
	EndingLevel();
	~EndingLevel();

	// delete Function
	EndingLevel(const EndingLevel& _Other) = delete;
	EndingLevel(EndingLevel&& _Other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;

protected:
	virtual void Loading() override;
	virtual void Update() override;
	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd() override;

private:









};

