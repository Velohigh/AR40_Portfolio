#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineLevel.h>  // �̰� ������ ���������� �˼���� �Ҹ��ڰ� ȣ����� �ʾ� Leak�� �߻��Ѵ�.
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

// static ��� ������ ������ �ʱ�ȭ ���־�� �Ѵ�.
std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;		// ��� ����(��)�� �����ϱ� ���� Map ��� ����
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;				// ���� ����(��) 
GameEngineLevel* GameEngine::NextLevel_ = nullptr;				// �ٲ� ����(��) 
GameEngine* GameEngine::UserContents_ = nullptr;					// ����(������)�� ���� ����
GameEngineImage* GameEngine::BackBufferImage_ = nullptr;		// �����, ������ DC�� ��������� ������ �굵 ������ش�.
GameEngineImage* GameEngine::WindowMainImage_ = nullptr;

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
	WindowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMain", GameEngineWindow::GetHDC());
	BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());

}

void GameEngine::EngineLoop()
{
	GameEngineTime::GetInst()->Update();

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
		GameEngineTime::GetInst()->Reset();	// ���� �ٲ�� �ð��� �ʱ�ȭ ���ش�.

		// ������ �ٲ� ȭ���� �ѹ� ����������� �ʱ�ȭ ���ش�.
		Rectangle(WindowMainImage_->ImageDC(), 0, 0, WindowMainImage_->GetScale().ix(), WindowMainImage_->GetScale().iy());
		Rectangle(BackBufferImage_->ImageDC(), 0, 0, BackBufferImage_->GetScale().ix(), BackBufferImage_->GetScale().iy());
	}

	if (nullptr == CurrentLevel_)
	{
		MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
	}

	// ��� Ű�� ��ȸ�ϸ鼭 �ش� Ű�� Down, Press, Up, Free �������� üũ�Ѵ�.
	// DeltaTime�� Ű�� ���� �ð��� üũ�ϱ� ���� ���ڷ� �Ѱ��ش�.
	GameEngineInput::GetInst()->Update(GameEngineTime::GetInst()->GetDeltaTime());

	// ����(��)���� �ð������� �ִ� �����̶��
	// �� �����Ӹ��� �ð��� üũ�ؾ��ϴ� �׷��ϵ�.
	CurrentLevel_->Update();
	CurrentLevel_->ActorUpdate();
	CurrentLevel_->ActorRender();
	CurrentLevel_->CollisionDebugRender();
	CurrentLevel_->ActorRelease();

	//WindowMainImage_->BitCopy(BackBufferImage_, { 0,0 }, { 0, 0 }, WindowMainImage_->GetScale());
	WindowMainImage_->BitCopy(BackBufferImage_);

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

	// �̱������� ������ ��ҵ� �ı�
	GameEngineImageManager::Destroy();
	GameEngineInput::Destroy();
	GameEngineTime::Destory();
	// ������ �ı�
	GameEngineWindow::Destroy();

}

void GameEngine::ChangeLevel(const std::string& _Name)
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
