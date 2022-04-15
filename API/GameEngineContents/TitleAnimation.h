#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 :
class TitleAnimation : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleAnimation();
	~TitleAnimation();

	// delete Function
	TitleAnimation(const TitleAnimation& _Other) = delete;
	TitleAnimation(TitleAnimation&& _Other) noexcept = delete;
	TitleAnimation& operator=(const TitleAnimation& _Other) = delete;
	TitleAnimation& operator=(TitleAnimation&& _Other) noexcept = delete;

protected:

private:


	// GameEngineActor을(를) 통해 상속됨
	virtual void Start() override;

	virtual void Update() override;

	virtual void Render() override;

};

