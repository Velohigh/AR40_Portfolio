#pragma once
#include <map>
#include <string>

// ���ӿ���.
// ���� ����ü�� ������, Loop, ������ ����ϰ� �� �༮.
// �������̽��� ������ ���̴�. (� �÷� ¥����!~!)
class GameEngineLevel;
class GameEngine
{
public:
	// constrcuter destructer
	GameEngine();
	~GameEngine();

	// delete Function
	GameEngine(const GameEngine& _Other) = delete;
	GameEngine(GameEngine&& _Other) noexcept = delete;
	GameEngine& operator=(const GameEngine& _Other) = delete;
	GameEngine& operator=(GameEngine&& _Other) noexcept = delete;

	// ���� ���� �Լ�.
	// �ڽĿ��� ������ �������̵�� ���� ����.
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;




protected:
	// ���ø����� ����(��)�� ������ش�. ��� ���� ��������� �𸣴ϱ�.
	// ����� MAP���� ���� �̸��� Ű������, �ش���� �����Ҵ��� �������ּҸ� Value �� �־��ش�.
	template <typename LevelType>
	void CreateLevel(const std::string& _Name)
	{
		LevelType* NewLevel = new LevelType;
		NewLevel->SetName(_Name);
		NewLevel->Loading();		// Level �� ��������� ���� �ε�
		AllLevel_.emplace(_Name, NewLevel);

	}

private:
	// ��� ����(��)�� ������ ��� ����
	// ��� ���� �θ� �����Ϳ� ��ĳ�����Ͽ� �����Ѵ�.
	std::map<std::string, GameEngineLevel*> AllLevel_;

};

