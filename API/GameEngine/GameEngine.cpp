#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineLevel.h>  // 이게 없어서 EngineLevel을

// static 멤버 변수는 무조건 초기화 해주어야 한다.
std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;		// 모든 레벨(씬)을 관리하기 위한 Map 멤버 변수
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;				// 현재 레벨(씬) 
GameEngineLevel* GameEngine::NextLevel_ = nullptr;				// 바뀔 레벨(씬) 
GameEngine* GameEngine::UserContents_ = nullptr;					// 유저(개발자)가 만든 게임
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
	UserContents_->GameInit();	// 엔진이 받아서
}

void GameEngine::EngineLoop()
{
	// 엔진 수준에서 매 프레임마다 체크하고 싶은 것
	UserContents_->GameLoop();	// 엔진이 실행해준다.

	// 새로운 레벨(씬)이 들어오면 현재 씬을 새로운 씬으로 바꿔준다.
	if (nullptr != NextLevel_)
	{
		CurrentLevel_ = NextLevel_;
		NextLevel_ = nullptr;
	}

	if (nullptr == CurrentLevel_)
	{
		MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
	}

	// 레벨(씬)수준 시간제한이 있는 게임이라면
	// 매 프레임마다 시간을 체크해야하는 그런일들.
	CurrentLevel_->Update();

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

	// 윈도우 파괴
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
