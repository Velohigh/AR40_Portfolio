#include "KatanaZero.h"
#include "TitleLevel.h"
#include "StageLevel.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>

KatanaZero::KatanaZero() 
{
}

KatanaZero::~KatanaZero() 
{
}

void KatanaZero::GameInit()
{
	// 윈도우 크기 설정
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 0,0 }, { 1280, 720 });

	// 디렉토리, 리소스폴더 경로 지정
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.Move("Resources");
	ResourcesDir.Move("Player");

	// 폴더안에 모든 이미지 파일을 찾는다.
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");
	// 모든 이미지 파일을 돌면서 이미지 매니저로 로드한다.
	for (size_t i = 0; i < AllImageFileList.size(); ++i)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	// 
	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("idle.bmp");
	Image->Cut({ 36, 35 });	// 이미지 한장의 픽셀크기 가로x세로


	CreateLevel<TitleLevel>("Title");
	CreateLevel<StageLevel>("Stage");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Stage");

}

void KatanaZero::GameLoop()
{
}

void KatanaZero::GameEnd()
{
}

