#pragma once
#include <list>
#include <map>
#include <vector>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>


class GameEngineActor;
struct ChangeOrderItem
{
	GameEngineActor* TargetObject;	// �̳༮�� Order��
	int ChangeOrder;				// �̷��� �ٲ��
};

// ���� :
class GameEngine;
class GameEngineActor;
class GameEngineCollision;
class GameEngineRenderer;
class Level;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
	friend GameEngineActor;
	friend GameEngineCollision;
	friend GameEngineRenderer;
	friend Level;	// UserCustom

public:
	// constrcuter destructer
	GameEngineLevel();

	// ������ ����� �˾ƾ� �մϴ�.
	// �̰� ���� �߿��ϱ� ����
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	// Actor�� Level ���� ����� �����Ѵ�!
	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0, const std::string& _Name = "")
	{
		ActorType* NewActor = new ActorType();
		GameEngineActor* StartActor = NewActor;	// friend�� EngineActor�� ��ĳ�����Ͽ� Start()�� ȣ���Ѵ�.
		NewActor->GameEngineUpdateObject::SetOrder(_Order);
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);	// ��ü�� ������ִ� ����(��)�� �־��ش�.
		StartActor->Start();		// ��ü�� �����ɶ� �� �ѹ� ȣ���.

		// Ű�� �ִ��� ã�ƺ���, ������ ������ش�. Find, insert ����� ���ÿ� �Ѵٴ� ��.
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);
		
		return NewActor;
	}

	inline float4 GetCameraPos()
	{
		return CameraPos_;
	}

	inline void MoveCameraPos(const float4& _Value)
	{
		CameraPos_ += _Value;
	}

	inline void SetCameraPos(const float4& _Value)
	{
		CameraPos_ = _Value;
	}

	template<typename ConvertType>
	ConvertType* FindActor(const std::string& _Name)
	{
		return dynamic_cast<ConvertType*>(FindActor(_Name));
	}

	GameEngineActor* FindActor(const std::string& _Name);

	void RegistActor(const std::string& _Name, GameEngineActor* _Actor);

protected:
	// �����Լ�
	// ��������鼭 ���ҽ��� ���͸� ���鶧 ���
	virtual void Loading() = 0;
	// �� ������ ���� �����϶� �ؾ������� �����Ѵ�.
	virtual void Update() = 0;
	// ���ͼ��ؿ��� ������ �����Ҷ� �����ϴ� �Լ�
	void ActorLevelChangeStart();
	// Current���� => Next������ �����Ҷ� ���緹���� �����ϴ� �Լ�.
	virtual void LevelChangeStart() = 0;
	// ���ͼ��ؿ��� ������ ������ �����ϴ� �Լ�
	void ActorLevelChangeEnd();
	// Current���� => Next������ �����Ҷ� ���������� �����ϴ� �Լ�.
	virtual void LevelChangeEnd() = 0;


private:
	// std::vector�� �����ϴ°� �� ���ٰ� �����մϴ�.
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	// ����ڰ� ���� ������ ��Ͻ�Ų ���͵�
	std::map<std::string, GameEngineActor*> RegistActor_;

	std::vector<ChangeOrderItem> ChangeOrderList;

	float4 CameraPos_;

	void ActorUpdate();
	void ActorRender();
	void CollisionDebugRender();
	void ActorRelease();

private:
	std::map<int, std::list<GameEngineRenderer*>> AllRenderer_;
	void AddRenderer(GameEngineRenderer* _Renderer);
	
	void ChangeUpdateOrder(GameEngineActor* _Actor, int _NewOrder);

	void ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder);


public:


private:
	// Collision
	// ������ ���Ͱ� ������, ���� ����� Level
	// ���⼭ �Ժη� GameEngineCollision*�� delete �ϴ� ���� ������ �ȵȴ�.
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName,GameEngineCollision* _Collision);

};

