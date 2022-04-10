#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

// ���� :
class Stage1Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Stage1Level();
	~Stage1Level();

	// delete Function
	Stage1Level(const Stage1Level& _Other) = delete;
	Stage1Level(Stage1Level&& _Other) noexcept = delete;
	Stage1Level& operator=(const Stage1Level& _Other) = delete;
	Stage1Level& operator=(Stage1Level&& _Other) noexcept = delete;

	GameEngineSoundPlayer BgmPlayer;
	float	BgmTime;

protected:
	// GameEngineLevel��(��) ���� ��ӵ�
	virtual void Loading() override;
	virtual void Update() override;
	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd() override;


private:




};

