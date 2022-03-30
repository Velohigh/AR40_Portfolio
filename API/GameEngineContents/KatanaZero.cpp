#include "KatanaZero.h"
#include "TitleLevel.h"
#include "Stage1Level.h"
#include "Stage2Level.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Define.h"

KatanaZero::KatanaZero() 
{
}

KatanaZero::~KatanaZero() 
{
}

void KatanaZero::GameInit()
{
	// 윈도우 크기 설정
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 0,0 }, { WINCX, WINCY });

	{
		// 
		// 디렉토리, 리소스폴더 경로 지정
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Player");

		// 폴더안에 모든 이미지 파일을 찾는다.
		std::vector<GameEngineFile> PlayerImageFileList = ResourcesDir.GetAllFile("bmp");
		// 모든 이미지 파일을 돌면서 이미지 매니저로 로드한다.

		for (size_t i = 0; i < PlayerImageFileList.size(); ++i)
		{
			GameEngineImageManager::GetInst()->Load(PlayerImageFileList[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Title");

		std::vector<GameEngineFile> TitleImageFileList = ResourcesDir.GetAllFile("bmp");

		for (size_t i = 0; i < TitleImageFileList.size(); ++i)
		{
			GameEngineImageManager::GetInst()->Load(TitleImageFileList[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Stage");

		std::vector<GameEngineFile> StageImageFileList = ResourcesDir.GetAllFile("bmp");

		for (size_t i = 0; i < StageImageFileList.size(); ++i)
		{
			GameEngineImageManager::GetInst()->Load(StageImageFileList[i].GetFullPath());
		}
	}

	// Title

	// Stage

	// Player
	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("idle_Ani.bmp");
	Image->Cut({ 36, 35 });	// 이미지 한장의 픽셀크기 가로x세로

	// 레벨 체인지 키를 엔진에서 만들어둔다! 각 레벨에서 만들어도 되지만, 어차피 모든레벨에서 사용할것이기 때문.
	if (false == GameEngineInput::GetInst()->IsKey("Stage1"))
	{
		GameEngineInput::GetInst()->CreateKey("Stage1", '1');
		GameEngineInput::GetInst()->CreateKey("Stage2", '2');
		GameEngineInput::GetInst()->CreateKey("Ending", '3');
	}

	CreateLevel<TitleLevel>("Title");
	CreateLevel<Stage1Level>("Stage1");
	CreateLevel<Stage2Level>("Stage2");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Title");

}

void KatanaZero::GameLoop()
{
}

void KatanaZero::GameEnd()
{
}

