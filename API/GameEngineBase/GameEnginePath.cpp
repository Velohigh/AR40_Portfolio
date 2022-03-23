#include "GameEnginePath.h"

GameEnginePath::GameEnginePath() 
{
}

GameEnginePath::GameEnginePath(const std::filesystem::path& _Path)
{
	Path_ = _Path;
}



GameEnginePath::~GameEnginePath() 
{
}

void GameEnginePath::SetCurrentPath()
{
	// 현재 폴더 경로
	Path_ = std::filesystem::current_path();
}

bool GameEnginePath::IsExist()
{
	// 해당 경로가 존재하는가
	return std::filesystem::exists(Path_);
}

std::string GameEnginePath::GetExtension()
{
	// 확장자를 리턴한다. ex. EXE, bmp
	return Path_.extension().string();
}

std::string GameEnginePath::GetFileName()
{
	return Path_.filename().string();
}

std::string GameEnginePath::GetFullPath()
{
	return Path_.string();
}