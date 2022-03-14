#pragma once
#include <GameEngine/GameEngineLevel.h>

// 설명 :
class EndingLevel : public GameEngineLevel
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
	// GameEngineLevel을(를) 통해 상속됨
	virtual void Loading() override;
	virtual void Update() override;

private:







};

