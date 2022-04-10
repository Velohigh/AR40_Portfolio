#pragma once
#include "GameEngineNameObject.h"
#include "ThirdParty/inc/fmod.hpp"
#include <map>

// 설명 :
class GameEngineSoundPlayer;
class GameEngineSound : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

protected:
	bool Load(const std::string& _Path);


private:
	FMOD::Sound* Sound;


	/// ///////////////////////////	매니지먼트 사운드 기능
public:
	// 이 사운드를 재생할거고, 컨트롤 하고 싶다
	static GameEngineSoundPlayer SoundPlayControl(const std::string& _Name);

	// 그냥 사운드 1회 재생, 멈추거나 이런건 할수 없다.
	static void SoundPlayOneShot(const std::string& _Name);
	static void Update();


	/////////////////////////////// 리소스 매니지먼트
public:

	static GameEngineSound* FindRes(const std::string& _Name);
	static GameEngineSound* LoadRes(const std::string& _Path);
	static GameEngineSound* LoadRes(const std::string& _Path, const std::string& _Name);

	static void AllResourcesDestroy();


private:
	static std::map<std::string, GameEngineSound*> AllRes;

};

	// 사운드 재생을 제어하는 클래스
class GameEngineSound;
class GameEngineSoundPlayer
{
	friend GameEngineSound;

public:
	void Stop();

	GameEngineSoundPlayer(const GameEngineSoundPlayer& _Other);

private:
	GameEngineSound* Sound_;
	FMOD::Channel* ControlHandle_;


	GameEngineSoundPlayer(GameEngineSound* Sound, FMOD::Channel* ControlHandle);

public:
	GameEngineSoundPlayer();
	~GameEngineSoundPlayer();
};