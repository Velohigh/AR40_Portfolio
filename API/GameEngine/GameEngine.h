#pragma once
#include <map>
#include <string>

// 게임엔진.
// 게임 그자체의 시작점, Loop, 끝점을 담당하게 될 녀석.
// 인터페이스만 제공할 것이다. (어떤 꼴로 짜야해!~!)
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

	// 순수 가상 함수.
	// 자식에서 무조건 오버라이드로 쓰는 문법.
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;




protected:
	// 템플릿으로 레벨(씬)을 만들어준다. 어떠한 씬을 만들어줄지 모르니까.
	// 만들고 MAP으로 레벨 이름을 키값으로, 해당씬의 동적할당한 포인터주소를 Value 로 넣어준다.
	template <typename LevelType>
	void CreateLevel(const std::string& _Name)
	{
		LevelType* NewLevel = new LevelType;
		NewLevel->SetName(_Name);
		NewLevel->Loading();		// Level 이 만들어지는 순간 로딩
		AllLevel_.emplace(_Name, NewLevel);

	}

private:
	// 모든 레벨(씬)을 관리할 멤버 변수
	// 모든 씬은 부모 포인터에 업캐스팅하여 관리한다.
	std::map<std::string, GameEngineLevel*> AllLevel_;

};

