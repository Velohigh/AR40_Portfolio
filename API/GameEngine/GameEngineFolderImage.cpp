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
	// ���丮, ���ҽ����� ��� ����
	GameEngineDirectory ResourcesDir = GameEngineDirectory(_Path);;
	//ResourcesDir.MoveParent("API");
	//ResourcesDir.Move("Resources");
	//ResourcesDir.Move("Player");

	// �����ȿ� ��� �̹��� ������ ã�´�.
	std::vector<GameEngineFile> PlayerImageFileList = ResourcesDir.GetAllFile("bmp");
	// ��� �̹��� ������ ���鼭 �̹��� �Ŵ����� �ε��Ѵ�.

	for (size_t i = 0; i < PlayerImageFileList.size(); ++i)
	{
		// GameEngineImageManager::GetInst()->Load(PlayerImageFileList[i].GetFullPath());

		GameEngineImage* Image = new GameEngineImage();
		
		// Image->Load();

		// Images_.push_back();
	}
}
