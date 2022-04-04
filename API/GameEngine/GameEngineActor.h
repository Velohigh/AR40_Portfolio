#pragma once
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineEnum.h"
#include <list>

// �̰����� ������ Actor�� ���� ���� �״�� ���� �Ѵ�.
// #define RENDERORDERMAX 2147483647

// ���� :
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineActor : public GameEngineNameObject, public GameEngineUpdateObject
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

	inline GameEngineLevel* GetLevel()
	{
		return Level_;
	}

	// ī�޶� ����������� ��ġ
	inline float4 GetCameraEffectPosition()
	{
		return Position_ - GetLevel()->GetCameraPos();
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
	virtual void Start() = 0;		// Initialize, ó���ѹ� ȣ��Ǵ� �ʱ�ȭ�Լ�.
	virtual void Update() = 0;		// ��������� ����ؼ� ȣ��� �Լ�.
	virtual void Render() = 0;		// ��� �Լ�.
	virtual void Release();			// ���Ͱ� ����ִ� RenderList, CollisionList �� ���ó���Ǹ� �޸𸮿��� �����Ѵ�.

	void DebugRectRender();			// ����׿� Rectangle ǥ���Լ�

private:
	GameEngineLevel* Level_;		// ���Ͱ� ��������� ��(����)
	float4 Position_;				// ȭ�鿡 ��µ� ��ǥ ��ġ
	float4 Scale_;					// ȭ�鿡 ��µ� �̹��� ũ��

	// ���� private�� �� ������ friend �� Level������ ����Ҽ� �ֵ��� �ϱ� ����.
	// Actor���� ���� X
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

	/////////////////////////////////////////////////// Render ��� ���� ����
public:
	GameEngineRenderer* CreateRenderer(int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });	// �̹��� none ����
	GameEngineRenderer* CreateRenderer(const std::string& _Image, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });
	GameEngineRenderer* CreateRendererToScale(const std::string& _Image, const float4& _Scale, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });

private:
	std::list<GameEngineRenderer*>::iterator StartRenderIter;
	std::list<GameEngineRenderer*>::iterator EndRenderIter;

	std::list<GameEngineRenderer*> RenderList_;

	/////////////////////////////////////////////////// Collision ��� ���� ����
public:
	GameEngineCollision* CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot = { 0, 0 });

private:
	std::list<GameEngineCollision*> CollisionList_;

};

