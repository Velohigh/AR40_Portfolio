#pragma once
#include <filesystem>

// 설명 :
class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(const std::filesystem::path& _Path);
	~GameEnginePath();

	// delete Function
	GameEnginePath(const GameEnginePath& _Other) = delete;
	GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	// 현재 폴더 경로
	void SetCurrentPath();

	// 유효한 경로인가?
	bool IsExist ();

	// 확장자를 알아내는 함수.
	std::string GetExtension();

	// 파일 이름을 알아내는 함수. (ex. Idle.bmp)
	std::string GetFileName();

	//
	std::string GetFullPath();

protected:
	std::filesystem::path Path_;

private:

};

