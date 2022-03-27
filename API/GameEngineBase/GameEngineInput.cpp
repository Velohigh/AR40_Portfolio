#include "GameEngineInput.h"
#include "GameEngineDebug.h"

//////////////////////////////////////////////////
void GameEngineInput::GameEngineKey::Update()
{
	if (true == KeyCheck())	// 키를 입력받았다.
	{
		if (true == Free_)
		{
			Down_ = true;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
		else if (true == Press_)
		{
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
	}
	else               // 키를 입력 받지 않았다.
	{
		if (true == Press_)	// 현재 키를 입력 X , 방금까지 누르고 있었다. 즉 키에서 손을 땟다.
		{
			Down_ = false;
			Press_ = false;
			Up_ = true;
			Free_ = false;
		}
		else if (true == Up_)	// 현재 키를 입력 X , 키에서 손을 땟고, Up_이 true이다. 즉, 아무것도 입력하고 있지 않은 상태
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	}
}



/// //////////////////////////////////////////

GameEngineInput* GameEngineInput::Inst_ = new GameEngineInput();

GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
}

bool GameEngineInput::IsKey(std::string _Name)
{
	if (AllInputKey_.end() != AllInputKey_.find(_Name))
	{
		return true;
	}

	return false;
}

void GameEngineInput::CreateKey(std::string _Name, int _Key)
{
	if (AllInputKey_.end() != AllInputKey_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 이름의 키를 또 만들려고 했습니다.");
		return;
	}

	if ('a' <= _Key && 'z' >= _Key)
	{
		_Key = std::toupper(_Key);
	}

	AllInputKey_.insert(std::make_pair(_Name, GameEngineKey()));
	AllInputKey_[_Name].Key_ = _Key;
	AllInputKey_[_Name].Reset();
}

void GameEngineInput::Update()
{
	// 맵에 지정된 모든 키를 업데이트 돌려준다.
	std::map<std::string, GameEngineKey>::iterator KeyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator KeyUpdateEnd = AllInputKey_.end();

	for (; KeyUpdateStart != KeyUpdateEnd; ++KeyUpdateStart)
	{
		GameEngineKey& CurrentKey = KeyUpdateStart->second;

		CurrentKey.Update();
	}


}

bool GameEngineInput::IsDown(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}

	return AllInputKey_[_Name].Down_;
}
bool GameEngineInput::IsUp(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[_Name].Up_;
}
bool GameEngineInput::IsPress(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[_Name].Press_;
}
bool GameEngineInput::IsFree(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[_Name].Free_;
}