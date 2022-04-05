#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include "GameEngineFile.h"
#include "GameEngineString.h"

GameEngineDirectory::GameEngineDirectory() 
{
	// ó�� �����η� Path_ ����
	SetCurrentPath();
}

GameEngineDirectory::GameEngineDirectory(const std::string& _Path)
{
	Path_ = _Path;
	if (false == IsExist())	// �ش� ��ΰ� �����ϴ°�
	{
		MsgBoxAssert("���� ���� �ʴ� ������ ���丮�� �ʱ�ȭ�Ϸ��� �߽��ϴ�.");
	}


}


GameEngineDirectory::~GameEngineDirectory() 
{
}

void GameEngineDirectory::MoveParent()
{
	// ���� ������ ��� ����
	Path_ = Path_.parent_path();
}

void GameEngineDirectory::MoveParent(const std::string& _Name)
{
	while (false == IsRoot())
	{
		Path_ = Path_.parent_path();
		
		// ã�� �̸��� ���� ���� ����̸� �ö󰡴°� �����.(ex API == API)
		if (_Name == GetFileName())
		{
			break;
		}
	}

}

bool GameEngineDirectory::IsRoot()
{
	// ����̺� ������ ��ΰ� ������?
	return Path_ == Path_.root_directory();
}

void GameEngineDirectory::Move(const std::string& _Name)
{
	std::filesystem::path CheckPath = Path_;

	CheckPath.append(_Name);	// �Է¹��� ��θ� �߰��Ѵ�.

	if (false == std::filesystem::exists(CheckPath))	// �� ������ �������� �ʴ´ٸ� ����
	{
		MsgBoxAssertString(_Name + " Path is not exists");
		return;
	}

	Path_ = CheckPath;	// ������ �����Ѵٸ� ��� ����.
}


std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string& _Ext)
{
	std::filesystem::directory_iterator DirIter(Path_);

	std::string Ext = _Ext;

	GameEngineString::ToUpper(Ext);

	if (Ext != "")	// Ȯ���ڰ� �������
	{
		if (std::string::npos == Ext.find("."))	// .�� �Ⱥپ� ���� ��� , npos�� -1�� ���ϴ»��.
		{
			Ext = "." + Ext;					// .�� �߰����ش�.
		}
	}


	std::vector<GameEngineFile> Return;

	// ���丮 ���� �� �����ϱ� File�� �ƴ� Entry
	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())
		{
			// �̶� ��� ������ ���� �������� �ϴ� ���� �� �ִ�.
			continue;
		}


		if (Ext != "")		// Ȯ���ڰ� �������� �����ʴ´�.
		{
			GameEnginePath NewPath = Entry.path();	// ��ü ���
			std::string OtherExt = NewPath.GetExtension();	// Ȯ����
			GameEngineString::ToUpper(OtherExt);			// Ȯ���ڸ� �빮�ڷ� �ٲ۴�.

			if (OtherExt != Ext)	// Ȯ���ڰ� �ٸ��ٸ� ���� ã�� ������ �ƴϴ�.
			{
				continue;
			}
		}


		Return.push_back(GameEngineFile(Entry.path()));

	}

	return Return;
}


std::vector<GameEngineFile> GameEngineDirectory::GetAllFolder()
{
	std::filesystem::directory_iterator DirIter(Path_);

	std::vector<GameEngineFile> Return;

	// ���丮 ���� �� �����ϱ� File�� �ƴ� Entry
	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())	// �������
		{
			Return.push_back(GameEngineFile(Entry.path()));
		}
		else
		{
			continue;	// ������ �ƴ϶�� �����ʴ´�.
		}

	}

	return Return;
}


