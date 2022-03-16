#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

// ���� :
class GameEngineLevel;
class GameEngineActor : GameEngineNameObject
{
	friend GameEngineLevel;		// ����(��) ������ Actor���� ������ �� �ֵ��� friend ���ش�.
public:

	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

protected:
	virtual void Start() = 0;		// Initialize, ó���ѹ� ȣ��Ǵ� �ʱ�ȭ�Լ�.
	virtual void Update() = 0;		// ��������� ����ؼ� ȣ��� �Լ�.
	virtual void Render() = 0;		// ��� �Լ�.

	void DebugRectRender();			// ����׿� Rectangle ǥ���Լ�

	inline float4 GetPosition() { return Position_; }
	inline float4 GetScale() { return Scale_; }
	inline void SetPosition(float4 _Value) { Position_ = _Value; }
	inline void SetScale(float4 _Value) { Scale_ = _Value; }

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


};
