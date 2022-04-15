#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class GameEngineRenderer;
class BackGround : public GameEngineActor
{
	static BackGround* CurBackGround;

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

	void SetIsTitle(bool _Value)
	{
		IsTitle = _Value;
	}


protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

	GameEngineRenderer* BackAnimationRenderer_ = nullptr;	// �ִϸ��̼� ������


private:
	GameEngineRenderer* Image_;
	bool IsTitle = false;


};

