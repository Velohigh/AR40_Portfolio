#pragma once
#include "GameEngineImage.h"
#include "GameEngineFolderImage.h"
#include <map>
#include <GameEngineBase/GameEngineMath.h>

// 설명 :
class GameEngineImageManager
{
private:
	static GameEngineImageManager* Inst_;

public:
	static GameEngineImageManager* GetInst()
	{
		return Inst_;
	}
	
	static void Destroy()
	{
		if (nullptr == Inst_)
		{
			return;
		}
		delete Inst_;
		Inst_ = nullptr;
	}

private:
	// constrcuter destructer
	GameEngineImageManager();
	~GameEngineImageManager();

	// delete Function
	GameEngineImageManager(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager(GameEngineImageManager&& _Other) noexcept = delete;
	GameEngineImageManager& operator=(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager& operator=(GameEngineImageManager&& _Other) noexcept = delete;


/// <summary>
/// 일반이미지
/// </summary>
public:
	// Map으로 관리하는 이미지를 찾는다.
	GameEngineImage* Find(const std::string& _Name);

	GameEngineImage* Create(const std::string& _Name, const float4& _Scale);
	GameEngineImage* Create(const std::string& _Name, HDC _DC);

	// 경로와 이름을 인자로 받아서
	// 해당 경로로 이미지 불러오고 이름을 키값으로 하여 
	// Map<이름, 이미지> 로 넣어준다.
	GameEngineImage* Load(const std::string& _Path);
	GameEngineImage* Load(const std::string& _Path, const std::string& _Name);


private:
	std::map < std::string, GameEngineImage* > AllRes;

	/// <summary>
/// 일반이미지
/// </summary>
public:
	GameEngineFolderImage* FolderImageFind(const std::string& _Name);
	GameEngineFolderImage* FolderImageLoad(const std::string& _Path);
	GameEngineFolderImage* FolderImageLoad(const std::string& _Path, const std::string& _Name);


private:
	std::map<std::string, GameEngineFolderImage*> AllFolderRes;

};

