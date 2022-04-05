#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include "GameEngineFile.h"
#include "GameEngineString.h"

GameEngineDirectory::GameEngineDirectory() 
{
	// 처음 실행경로로 Path_ 지정
	SetCurrentPath();
}

GameEngineDirectory::GameEngineDirectory(const std::string& _Path)
{
	Path_ = _Path;
	if (false == IsExist())	// 해당 경로가 존재하는가
	{
		MsgBoxAssert("존재 하지 않는 폴더로 디렉토리를 초기화하려고 했습니다.");
	}


}


GameEngineDirectory::~GameEngineDirectory() 
{
}

void GameEngineDirectory::MoveParent()
{
	// 상위 폴더로 경로 수정
	Path_ = Path_.parent_path();
}

void GameEngineDirectory::MoveParent(const std::string& _Name)
{
	while (false == IsRoot())
	{
		Path_ = Path_.parent_path();
		
		// 찾는 이름과 같은 폴더 경로이면 올라가는걸 멈춘다.(ex API == API)
		if (_Name == GetFileName())
		{
			break;
		}
	}

}

bool GameEngineDirectory::IsRoot()
{
	// 드라이브 폴더와 경로가 같은가?
	return Path_ == Path_.root_directory();
}

void GameEngineDirectory::Move(const std::string& _Name)
{
	std::filesystem::path CheckPath = Path_;

	CheckPath.append(_Name);	// 입력받은 경로를 추가한다.

	if (false == std::filesystem::exists(CheckPath))	// 그 폴더가 존재하지 않는다면 실행
	{
		MsgBoxAssertString(_Name + " Path is not exists");
		return;
	}

	Path_ = CheckPath;	// 폴더가 존재한다면 경로 수정.
}


std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string& _Ext)
{
	std::filesystem::directory_iterator DirIter(Path_);

	std::string Ext = _Ext;

	GameEngineString::ToUpper(Ext);

	if (Ext != "")	// 확장자가 없을경우
	{
		if (std::string::npos == Ext.find("."))	// .이 안붙어 있을 경우 , npos는 -1을 뜻하는상수.
		{
			Ext = "." + Ext;					// .을 추가해준다.
		}
	}


	std::vector<GameEngineFile> Return;

	// 디렉토리 까지 다 나오니까 File이 아닌 Entry
	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())
		{
			// 이때 재귀 돌리면 하위 폴더까지 싹다 돌릴 수 있다.
			continue;
		}


		if (Ext != "")		// 확장자가 없을때는 하지않는다.
		{
			GameEnginePath NewPath = Entry.path();	// 전체 경로
			std::string OtherExt = NewPath.GetExtension();	// 확장자
			GameEngineString::ToUpper(OtherExt);			// 확장자를 대문자로 바꾼다.

			if (OtherExt != Ext)	// 확장자가 다르다면 내가 찾는 파일이 아니다.
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

	// 디렉토리 까지 다 나오니까 File이 아닌 Entry
	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())	// 폴더라면
		{
			Return.push_back(GameEngineFile(Entry.path()));
		}
		else
		{
			continue;	// 폴더가 아니라면 넣지않는다.
		}

	}

	return Return;
}


