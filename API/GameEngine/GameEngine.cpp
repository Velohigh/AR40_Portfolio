#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineLevel.h>  // �̰� ��� EngineLevel��

// static ��� ������ ������ �ʱ�ȭ ���־�� �Ѵ�.
std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;		// ��� ����(��)�� �����ϱ� ���� Map ��� ����
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;				// ���� ����(��) 
GameEngineLevel* GameEngine::NextLevel_ = nullptr;				// �ٲ� ����(��) 
GameEngine* GameEngine::UserContents_ = nullptr;					// ����(������)�� ���� ����
GameEngine::GameEngine() 
{
}

GameEngine::~GameEngine() 
{
}

void GameEngine::GameInit()
{
}

void GameEngine::GameLoop()
{
}

void GameEngine::GameEnd()
{
}

void GameEngine::WindowCreate()
{
	GameEngineWindow::GetInst().CreateGameWindow(nullptr, "GameWindow");
	GameEngineWindow::GetInst().ShowGameWindow();
	GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}

void GameEngine::EngineInit()
{
	UserContents_->GameInit();	// ������ �޾Ƽ�
}

void GameEngine::EngineLoop()
{
	// ���� ���ؿ��� �� �����Ӹ��� üũ�ϰ� ���� ��
	UserContents_->GameLoop();	// ������ �������ش�.

	// ���ο� ����(��)�� ������ ���� ���� ���ο� ������ �ٲ��ش�.
	if (nullptr != NextLevel_)
	{
		CurrentLevel_ = NextLevel_;
		NextLevel_ = nullptr;
	}

	if (nullptr == CurrentLevel_)
	{
		MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
	}

	// ����(��)���� �ð������� �ִ� �����̶��
	// �� �����Ӹ��� �ð��� üũ�ؾ��ϴ� �׷��ϵ�.
	CurrentLevel_->Update();

}

// ����� �޸𸮵��� ��� �����ϴ� ��.
void GameEngine::EngineEnd()
{
	// ���� ����
	UserContents_->GameEnd();	

	// ��� ����(��)�� ��ȸ�ϸ鼭 �����.
	auto iter = AllLevel_.begin();

	for (; iter != AllLevel_.end(); ++iter)
	{
		if (nullptr == iter->second)
		{
			continue;
		}

		delete iter->second;
	}

	// ������ �ı�
	GameEngineWindow::Destroy();

}

void GameEngine::ChangeLevel(const std::string& _Name)
{
	{
		// std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Name);
		auto FindIter = AllLevel_.find(_Name);

		if (AllLevel_.end() == FindIter)
		{
			MsgBoxAssert("Level Find Error");
			return;
		}

		NextLevel_ = FindIter->second;
	}
}
