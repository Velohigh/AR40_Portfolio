#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <string>
#include <list>
#include <map>

// ���漱��
class GameEngine;
class GameEngineActor;

// ���� : ����(��) �� �θ� Ŭ����
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
public:
	// constrcuter destructer
	GameEngineLevel();

	// �θ��� �Ҹ��ڿ� virtual�� ���̴� ����
	// virtual�� �ٿ��� �ڽļҸ��� -> �θ�Ҹ��� ������ ������� ȣ���Ͽ� Leak�� ���ų� �ϴ� ���� �����Ҽ� �ִ�.
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;

	// ��(����)�� �ٲ� ���� �Լ�.
	virtual void SceneChangeStart() {};		// ���� �����Ҷ� ����ϴ� �Լ�
	virtual void SceneChangeEnd() {};			// ���� ������(�ٲ�) ���� ���� ����ϴ� �Լ�.

		// Actor�� Level ���� ����� �����Ѵ�!
	template <typename ActorType>
	ActorType* CreateActor(std::string _Name, int _Order)
	{
		ActorType* NewActor = new ActorType;
		GameEngineActor* StartActor = NewActor;	// friend�� EngineActor�� ��ĳ�����Ͽ� Start()�� ȣ���Ѵ�.
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);	// ��ü�� ������ִ� ����(��)�� �־��ش�.
		StartActor->Start();		// ��ü�� �����ɶ� �� �ѹ� ȣ���.

		// Ű�� �ִ��� ã�ƺ���, ������ ������ش�. Find, insert ����� ���ÿ� �Ѵٴ� ��.
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		return nullptr;
	}

private:
	std::map<int, std::list<GameEngineActor*>> AllActor_;
	// std::map<std::string, std::list<GameEngineActor*>> AllActor_;

	void ActorUpdate();
	void ActorRender();
};

