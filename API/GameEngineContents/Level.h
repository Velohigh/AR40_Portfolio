#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

// Ό³Έν :
class Player;
class Level : public GameEngineLevel
{
public:
	friend Player;
	// constrcuter destructer
	Level();
	~Level();

	// delete Function
	Level(const Level& _Other) = delete;
	Level(Level&& _Other) noexcept = delete;
	Level& operator=(const Level& _Other) = delete;
	Level& operator=(Level&& _Other) noexcept = delete;


	inline void SetBgmOn(bool _Value)
	{
		BgmOn = _Value;
	}

	inline void SetBgmTime(float _Value)
	{
		BgmTime = _Value;
	}

	inline std::map<int, std::list<GameEngineActor*>> GetAllActor()
	{
		return AllActor_;
	}

protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;
	virtual void LevelChangeStart() = 0;
	virtual void LevelChangeEnd() = 0;

	GameEngineSoundPlayer BgmPlayer;
	bool	BgmOn = false;
	float	BgmTime = 0.f;

private:

};

