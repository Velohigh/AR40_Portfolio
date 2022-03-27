#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineEnum.h"
#include <list>

// ���� :
class GameEngineRenderer;
class GameEngineLevel;
class GameEngineActor : public GameEngineNameObject
{
	//// ActorBase ��� ����
public:
	friend GameEngineLevel;		// ����(��) ������ Actor���� ������ �� �ֵ��� friend ���ش�.

	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

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
	virtual void Start() = 0;		// Initialize, ó���ѹ� ȣ��Ǵ� �ʱ�ȭ�Լ�.
	virtual void Update() = 0;		// ��������� ����ؼ� ȣ��� �Լ�.
	virtual void Render() = 0;		// ��� �Լ�.

	void DebugRectRender();			// ����׿� Rectangle ǥ���Լ�

private:
	GameEngineLevel* Level_;
	float4 Position_;
	float4 Scale_;

	// ���� private�� �� ������ friend �� Level������ ����Ҽ� �ֵ��� �ϱ� ����.
	// Actor���� ���� X
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

	/////////////////////////////////////////////////// Render ��� ���� ����
public:
	GameEngineRenderer* CreateRenderer(const std::string& _Image, RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });
	GameEngineRenderer* CreateRendererToScale(const std::string& _Image, const float4& _Scale, RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });


	// RenderList�� ��ȸ�ϸ鼭 Renderer �� Render()�� �������ش�.
	void Renderering();

private:
	std::list<GameEngineRenderer*>::iterator StartRenderIter;
	std::list<GameEngineRenderer*>::iterator EndRenderIter;

	std::list<GameEngineRenderer*> RenderList_;


};

