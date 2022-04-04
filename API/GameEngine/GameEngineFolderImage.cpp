#include "GameEngineFolderImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include "GameEngineImageManager.h"


GameEngineFolderImage::GameEngineFolderImage()
{

}

GameEngineFolderImage::~GameEngineFolderImage()
{

}

bool GameEngineFolderImage::Load(const std::string& _Path)
{
	// 디렉토리, 리소스폴더 경로 지정
	GameEngineDirectory ResourcesDir = GameEngineDirectory(_Path);;
	//ResourcesDir.MoveParent("API");
	//ResourcesDir.Move("Resources");
	//ResourcesDir.Move("Player");

	// 폴더안에 모든 이미지 파일을 찾는다.
	std::vector<GameEngineFile> PlayerImageFileList = ResourcesDir.GetAllFile("bmp");
	// 모든 이미지 파일을 돌면서 이미지 매니저로 로드한다.

	for (size_t i = 0; i < PlayerImageFileList.size(); ++i)
	{
		// GameEngineImageManager::GetInst()->Load(PlayerImageFileList[i].GetFullPath());

		GameEngineImage* Image = new GameEngineImage();
		
		// Image->Load();

		// Images_.push_back();
	}
}
