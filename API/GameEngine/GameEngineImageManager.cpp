#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineImageManager* GameEngineImageManager::Inst_ = new GameEngineImageManager;
GameEngineImageManager::GameEngineImageManager() 
{
}

GameEngineImageManager::~GameEngineImageManager() 
{
	std::map<std::string, GameEngineImage*>::iterator iter = AllRes_.begin();

	for (; iter != AllRes_.end(); ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, float4 _Scale)
{

	if (AllRes_.find(_Name) != AllRes_.end())
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� �߽��ϴ�.");
		return nullptr;
	}
	
	GameEngineImage* NewImage = new GameEngineImage;
	NewImage->SetName(_Name);

	if (false == NewImage->Create(_Scale))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "�̹����� �����ϴµ� �����߽��ϴ�.").c_str());
		return nullptr;
	}

	AllRes_.emplace(_Name, NewImage);

	return NewImage;

}

