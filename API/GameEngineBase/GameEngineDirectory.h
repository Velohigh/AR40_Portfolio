#pragma once
#include "GameEnginePath.h"


// ���� :
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
	// �Է¹��� �̸��� �������� ���� ������.
	void MoveParent(const std::string& _Name);
	
	// �ֻ��� ����������� Ȯ���Ѵ�. ������ ã�� �� ���⶧����, 
	bool IsRoot();

	// �Է¹��� ������ �̵��Ѵ�.
	void Move(const std::string& _Name);

	// �ش� ������ ��� �̹��� ������ �ε��Ѵ�.
	std::vector<GameEngineFile> GetAllFile(const std::string& _Ext = "");

protected:

private:

};

