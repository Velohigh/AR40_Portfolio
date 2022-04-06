#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineLevel.h>  // 이게 없으면 엔진레벨을 알수없어서 소멸자가 호출되지 않아 Leak이 발생한다.
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

// static 멤버 변수는 무조건 초기화 해주어야 한다.
std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;		// 모든 레벨(씬)을 관리하기 위한 Map 멤버 변수
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;				// 현재 레벨(씬) 
GameEngineLevel* GameEngine::NextLevel_ = nullptr;				// 바뀔 레벨(씬) 
GameEngine* GameEngine::UserContents_ = nullptr;					// 유저(개발자)가 만든 게임
GameEngineImage* GameEngine::BackBufferImage_ = nullptr;		// 백버퍼, 윈도우 DC가 만들어지는 순간에 얘도 만들어준다.
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
	// 윈도우 크기는 여기서 결정해준다.
	UserContents_->GameInit();	// 엔진이 받아서

	// 백버퍼를 만든다.
	WindowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMain", GameEngineWindow::GetHDC());
	BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());

}

void GameEngine::EngineLoop()
{
	GameEngineTime::GetInst()->Update();

	// 엔진 수준에서 매 프레임마다 체크하고 싶은 것
	UserContents_->GameLoop();	// 엔진이 실행해준다.

	// 새로운 레벨(씬)이 들어오면 현재 씬을 새로운 씬으로 바꿔준다.
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
		GameEngineTime::GetInst()->Reset();	// 씬이 바뀌고 시간을 초기화 해준다.

		// 레벨이 바뀔때 화면을 한번 흰색바탕으로 초기화 해준다.
		Rectangle(WindowMainImage_->ImageDC(), 0, 0, WindowMainImage_->GetScale().ix(), WindowMainImage_->GetScale().iy());
		Rectangle(BackBufferImage_->ImageDC(), 0, 0, BackBufferImage_->GetScale().ix(), BackBufferImage_->GetScale().iy());
	}

	if (nullptr == CurrentLevel_)
	{
		MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
	}

	// 모든 키를 순회하면서 해당 키가 Down, Press, Up, Free 상태인지 체크한다.
	// DeltaTime은 키를 누른 시간을 체크하기 위해 인자로 넘겨준다.
	GameEngineInput::GetInst()->Update(GameEngineTime::GetInst()->GetDeltaTime());

	// 레벨(씬)수준 시간제한이 있는 게임이라면
	// 매 프레임마다 시간을 체크해야하는 그런일들.
	CurrentLevel_->Update();
	CurrentLevel_->ActorUpdate();
	CurrentLevel_->ActorRender();
	CurrentLevel_->CollisionDebugRender();
	CurrentLevel_->ActorRelease();

	//WindowMainImage_->BitCopy(BackBufferImage_, { 0,0 }, { 0, 0 }, WindowMainImage_->GetScale());
	WindowMainImage_->BitCopy(BackBufferImage_);

}

// 사용한 메모리들을 모두 정리하는 곳.
void GameEngine::EngineEnd()
{
	// 게임 종료
	UserContents_->GameEnd();	

	// 모든 레벨(씬)을 순회하면서 지운다.
	auto iter = AllLevel_.begin();

	for (; iter != AllLevel_.end(); ++iter)
	{
		if (nullptr == iter->second)
		{
			continue;
		}

		delete iter->second;
	}

	// 싱글톤으로 구현한 요소들 파괴
	GameEngineImageManager::Destroy();
	GameEngineInput::Destroy();
	GameEngineTime::Destory();
	// 윈도우 파괴
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
