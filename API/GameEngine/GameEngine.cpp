#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineLevel.h>  // �̰� ������ ���������� �˼���� �Ҹ��ڰ� ȣ����� �ʾ� Leak�� �߻��Ѵ�.
#include "GameEngineImageManager.h"

// static ��� ������ ������ �ʱ�ȭ ���־�� �Ѵ�.
std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;		// ��� ����(��)�� �����ϱ� ���� Map ��� ����
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;				// ���� ����(��) 
GameEngineLevel* GameEngine::NextLevel_ = nullptr;				// �ٲ� ����(��) 
GameEngine* GameEngine::UserContents_ = nullptr;					// ����(������)�� ���� ����
GameEngineImage* GameEngine::BackBufferImage_ = nullptr;		// �����, ������ DC�� ��������� ������ �굵 ������ش�.

HDC GameEngine::BackBufferDC()
{
	return BackBufferImage_->ImageDC();
}

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
	// ������ ũ��� ���⼭ �������ش�.
	UserContents_->GameInit();	// ������ �޾Ƽ�

	// ����۸� �����.
	BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());

}

void GameEngine::EngineLoop()
{
	// ���� ���ؿ��� �� �����Ӹ��� üũ�ϰ� ���� ��
	UserContents_->GameLoop();	// ������ �������ش�.

	// ���ο� ����(��)�� ������ ���� ���� ���ο� ������ �ٲ��ش�.
	if (nullptr != NextLevel_)
	{
		if (nullptr != CurrentLevel_)
		{
			CurrentLevel_->LevelChangeEnd();
		}

		CurrentLevel_ = NextLevel_;

		if (nullptr != CurrentLevel_)
		{
			CurrentLevel_->LevelChangeStart();
		}

		NextLevel_ = nullptr;
	}

	if (nullptr == CurrentLevel_)
	{
		MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
	}

	// ����(��)���� �ð������� �ִ� �����̶��
	// �� �����Ӹ��� �ð��� üũ�ؾ��ϴ� �׷��ϵ�.
	CurrentLevel_->Update();
	CurrentLevel_->ActorUpdate();
	CurrentLevel_->ActorRender();

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


	// �̹��� �Ŵ��� �ı�
	GameEngineImageManager::Destroy();

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
