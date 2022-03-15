#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� :
class StageLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	StageLevel();
	~StageLevel();

	// delete Function
	StageLevel(const StageLevel& _Other) = delete;
	StageLevel(StageLevel&& _Other) noexcept = delete;
	StageLevel& operator=(const StageLevel& _Other) = delete;
	StageLevel& operator=(StageLevel&& _Other) noexcept = delete;

protected:
	// GameEngineLevel��(��) ���� ��ӵ�
	virtual void Loading() override;
	virtual void Update() override;
	virtual void SceneChangeStart() override;
	virtual void SceneChangeEnd() override;


private:




};

