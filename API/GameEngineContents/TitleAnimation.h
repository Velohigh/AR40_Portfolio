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
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	GameEngineRenderer* BackAnimationRenderer_ = nullptr;	// 애니메이션 렌더러
	int iSelect = 0;
	int iPreSelect = 0;
	bool isStart = false;
};

