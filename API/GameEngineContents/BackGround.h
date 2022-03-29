#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 :
class GameEngineRenderer;
class BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	GameEngineRenderer* GetRenderer()
	{
		return Image_;
	}

protected:
	// GameEngineActor을(를) 통해 상속됨
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;



private:
	GameEngineRenderer* Image_;



};

