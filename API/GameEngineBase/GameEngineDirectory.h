#pragma once
#include "GameEnginePath.h"


// 설명 :
class GameEngineFile;
class GameEngineDirectory : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	GameEngineDirectory(const std::string& _Path);
	~GameEngineDirectory();

	// delete Function
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	void MoveParent();
	// 입력받은 이름의 폴더까지 상위 폴더로.
	void MoveParent(const std::string& _Name);
	
	// 최상위 폴더경로인지 확인한다. 무한정 찾을 수 없기때문에, 
	bool IsRoot();

	// 입력받은 폴더로 이동한다.
	void Move(const std::string& _Name);

	// 해당 폴더의 모든 이미지 파일을 로딩한다.
	std::vector<GameEngineFile> GetAllFile(const std::string& _Ext = "");

protected:

private:

};

