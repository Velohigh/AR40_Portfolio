#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <string>

// 설명 : 레벨(씬) 의 부모 클래스
class GameEngineLevel : public GameEngineNameObject
{
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

private:
	// Actor는 Level 에서 만들고 관리한다!
	template <typename ActorType>
	ActorType* CreateActor(std::string _Name)
	{
		return nullptr;
	}
};

