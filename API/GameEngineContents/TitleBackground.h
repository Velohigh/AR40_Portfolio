#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class TitleBackground : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleBackground();
	~TitleBackground();

	// delete Function
	TitleBackground(const TitleBackground& _Other) = delete;
	TitleBackground(TitleBackground&& _Other) noexcept = delete;
	TitleBackground& operator=(const TitleBackground& _Other) = delete;
	TitleBackground& operator=(TitleBackground&& _Other) noexcept = delete;

protected:
	// GameEngineActor��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:




};

