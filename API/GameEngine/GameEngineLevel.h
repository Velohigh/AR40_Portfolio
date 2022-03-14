#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <string>

// ���� : ����(��) �� �θ� Ŭ����
class GameEngineLevel : public GameEngineNameObject
{
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

private:
	// Actor�� Level ���� ����� �����Ѵ�!
	template <typename ActorType>
	ActorType* CreateActor(std::string _Name)
	{
		return nullptr;
	}
};

