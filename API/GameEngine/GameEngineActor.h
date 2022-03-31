#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineEnum.h"
#include <list>

// 설명 :
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineActor : public GameEngineNameObject, public GameEngineUpdateObject
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

	inline GameEngineLevel* GetLevel()
	{
		return Level_;
	}

	inline float4 GetPosition()
	{
		return Position_;
	}
	inline float4 GetScale()
	{
		return Scale_;
	}

	inline void SetMove(float4 _Value)
	{
		Position_ += _Value;
	}

	inline void SetPosition(float4 _Value)
	{
		Position_ = _Value;
	}
	inline void SetScale(float4 _Value)
	{
		Scale_ = _Value;
	}

protected:
	virtual void Start() = 0;		// Initialize, 처음한번 호출되는 초기화함수.
	virtual void Update() = 0;		// 만들어지고 계속해서 호출될 함수.
	virtual void Render() = 0;		// 출력 함수.

	void DebugRectRender();			// 디버그용 Rectangle 표시함수

private:
	GameEngineLevel* Level_;		// 액터가 만들어지는 씬(레벨)
	float4 Position_;				// 화면에 출력될 좌표 위치
	float4 Scale_;					// 화면에 출력될 이미지 크기

	// 굳이 private에 둔 이유는 friend 인 Level에서만 사용할수 있도록 하기 위해.
	// Actor에서 접근 X
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

	/////////////////////////////////////////////////// Render 기능 관련 모음
public:
	GameEngineRenderer* CreateRenderer(RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });	// 이미지 none 세팅
	GameEngineRenderer* CreateRenderer(const std::string& _Image, RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });
	GameEngineRenderer* CreateRendererToScale(const std::string& _Image, const float4& _Scale, RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });


	// RenderList를 순회하면서 Renderer 의 Render()를 실행해준다.
	void Renderering();

private:
	std::list<GameEngineRenderer*>::iterator StartRenderIter;
	std::list<GameEngineRenderer*>::iterator EndRenderIter;

	std::list<GameEngineRenderer*> RenderList_;

	/////////////////////////////////////////////////// Collision 기능 관련 모음
public:
	GameEngineCollision* CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot = { 0, 0 });

private:
	std::list<GameEngineCollision*> CollisionList_;

};

