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

GameEngineImage* GameEngineImageManager::Find(const std::string& _Name)
{

	std::map<std::string, GameEngineImage*>::iterator Finditer = AllRes_.find(_Name);

	if (Finditer == AllRes_.end())	// 못찾았다면
	{
		//MsgBoxAssert("못 찾았다.");
		return nullptr;
	}

	return Finditer->second;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name,const float4& _Scale)
{

	if (AllRes_.find(_Name) != AllRes_.end())
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 또 만들려고 했습니다.");
		return nullptr;
	}
	
	GameEngineImage* NewImage = new GameEngineImage;
	NewImage->SetName(_Name);

	if (false == NewImage->Create(_Scale))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "이미지를 생성하는데 실패했습니다.").c_str());
		return nullptr;
	}

	AllRes_.emplace(_Name, NewImage);

	return NewImage;

}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, HDC _DC)
{
	if (AllRes_.find(_Name) != AllRes_.end())
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 또 만들려고 했습니다.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage;
	NewImage->SetName(_Name);

	if (false == NewImage->Create(_DC))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "이미지를 생성하는데 실패했습니다.").c_str());
		return nullptr;
	}

	AllRes_.emplace(_Name, NewImage);

	return NewImage;
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path)
{
	// 무시
	// Create();
	return nullptr;
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path,const std::string& _Name)
{
	if (AllRes_.find(_Name) != AllRes_.end())
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 또 만들려고 했습니다.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage;
	NewImage->SetName(_Name);

	if (false == NewImage->Load(_Path))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "이미지를 생성하는데 실패했습니다.").c_str());
		return nullptr;
	}

	AllRes_.emplace(_Name, NewImage);

	return NewImage;
}

