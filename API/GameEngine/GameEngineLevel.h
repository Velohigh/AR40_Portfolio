#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <string>
#include <list>
#include <map>

// 전방선언
class GameEngine;
class GameEngineActor;

// 설명 : 레벨(씬) 의 부모 클래스
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
public:
	// constrcuter destructer
	GameEngineLevel();

	// 부모의 소멸자에 virtual을 붙이는 이유
	// virtual을 붙여야 자식소멸자 -> 부모소멸자 순으로 순서대로 호출하여 Leak이 남거나 하는 일을 방지할수 있다.
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;

	// 씬(레벨)이 바뀔때 쓰는 함수.
	virtual void SceneChangeStart() {};		// 씬이 시작할때 사용하는 함수
	virtual void SceneChangeEnd() {};			// 씬이 끝날때(바뀔때) 이전 씬이 사용하는 함수.

		// Actor는 Level 에서 만들고 관리한다!
	template <typename ActorType>
	ActorType* CreateActor(std::string _Name, int _Order)
	{
		ActorType* NewActor = new ActorType;
		GameEngineActor* StartActor = NewActor;	// friend인 EngineActor로 업캐스팅하여 Start()를 호출한다.
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);	// 객체를 만들어주는 레벨(씬)을 넣어준다.
		StartActor->Start();		// 객체가 생성될때 딱 한번 호출됨.

		// 키가 있는지 찾아보고, 없으면 만들어준다. Find, insert 기능을 동시에 한다는 뜻.
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

