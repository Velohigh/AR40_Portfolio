#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include "Level.h"

// ���� :
class Stage1Level : public Level
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



protected:
	// GameEngineLevel��(��) ���� ��ӵ�
	virtual void Loading() override;
	virtual void Update() override;
	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd() override;


private:




};

