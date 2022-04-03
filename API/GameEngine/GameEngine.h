#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>

// ���ӿ���.
// ���� ����ü�� ������, Loop, ������ ����ϰ� �� �༮.
// �������̽��� ������ ���̴�. (� �÷� ¥����!~!)
class GameEngineImage;
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

	static inline GameEngineImage* BackBufferImage()
	{
		return BackBufferImage_;
	}

	static HDC BackBufferDC();

	// ���� ���� �Լ�.
	// �ڽĿ��� ������ �������̵�� ���� ����.
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;

	template <typename GameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		GameType UserGame;
		UserContents_ = &UserGame;

		WindowCreate();
		EngineEnd();
	}

	static GameEngine& GetInst()
	{
		if (nullptr == UserContents_)
		{
			MsgBoxAssert("GameEngine ERROR Engine Is Not Start");
		}

		return *UserContents_;
	}

	// ����(��) ��ȯ
	void ChangeLevel(const std::string& _Name);

protected:
	// ���ø����� ����(��)�� ������ش�. ��� ���� ��������� �𸣴ϱ�.
	// ����� MAP���� ���� �̸��� Ű������, �ش���� �����Ҵ��� �������ּҸ� Value �� �־��ش�.
	template <typename LevelType>
	void CreateLevel(const std::string& _Name)
	{
		LevelType* NewLevel = new LevelType;
		GameEngineLevel* Level = NewLevel;
		NewLevel->SetName(_Name);
		Level->Loading();		// �θ� �����Ϳ� �ڽ������͸� �����Ͽ� Loading�� �ҷ��´�.
								// GameEngine�� GameEngineLevel �� Friend �̱� ������ Protected�� ������ �����ϴ�.
		AllLevel_.emplace(_Name, NewLevel);

	}

private:
	// ��� ����(��)�� ������ ��� ����
	// ��� ���� �θ� �����Ϳ� ��ĳ�����Ͽ� �����Ѵ�.
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngine* UserContents_;

	static GameEngineImage* WindowMainImage_; // �׷����� ȭ�鿡 ��¥ ������ �Ǵ� �̹���
	static GameEngineImage* BackBufferImage_; // �������� �ذ��Ϸ��� ���۷� ����ϴ� �̹���

	static void WindowCreate();
	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();
};

