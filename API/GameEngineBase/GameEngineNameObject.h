#pragma once
#include <string>

// 설명 : 어떤 얘가 이름을 가지기 위한 클래스
// EngineActor와 EngineLevel 을 자식으로 가진다.
class GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineNameObject();
	~GameEngineNameObject();

	// delete Function
	GameEngineNameObject(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject(GameEngineNameObject&& _Other) noexcept = delete;
	GameEngineNameObject& operator=(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject& operator=(GameEngineNameObject&& _Other) noexcept = delete;


	inline void SetName(const std::string& _Name)
	{
		Name_ = _Name;
	}

	// 단순 값 복사용
	std::string GetNameCopy()
	{
		return Name_;
	}

	const std::string& GetNameConstRef()
	{
		return Name_;
	}

	const char* GetNameConstPtr()
	{
		return Name_.c_str();
	}

protected:



private:
	std::string Name_;

};

