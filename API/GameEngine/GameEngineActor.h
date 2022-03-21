#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <vector>
#include "GameEngineEnum.h"

// 설명 :
class GameEngineRenderer;
class GameEngineLevel;
class GameEngineActor : GameEngineNameObject
{
	//// ActorBase 기능 모음
public:
	friend GameEngineLevel;		// 레벨(씬) 에서만 Actor들을 관리할 수 있도록 friend 해준다.

	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

protected:
	virtual void Start() = 0;		// Initialize, 처음한번 호출되는 초기화함수.
	virtual void Update() = 0;		// 만들어지고 계속해서 호출될 함수.
	virtual void Render() = 0;		// 출력 함수.

	void DebugRectRender();			// 디버그용 Rectangle 표시함수

	inline float4 GetPosition() { return Position_; }
	inline float4 GetScale() { return Scale_; }
	inline void SetPosition(float4 _Value) { Position_ = _Value; }
	inline void SetScale(float4 _Value) { Scale_ = _Value; }

private:
	GameEngineLevel* Level_;
	float4 Position_;
	float4 Scale_;

	// 굳이 private에 둔 이유는 friend 인 Level에서만 사용할수 있도록 하기 위해.
	// Actor에서 접근 X
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

	/////////////////////////////////////////////////// Render 기능 관련 모음
public:
	GameEngineRenderer* CreateRenderer(const std::string& _Image, RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });

private:
	std::vector<GameEngineRenderer*> RenderList_;


};

