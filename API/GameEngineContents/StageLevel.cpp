#include "StageLevel.h"
#include "Player.h"

enum class ORDER
{
	BACKGROUND,
	PLAYER,
	MONSTER,
	UI
};

StageLevel::StageLevel() 
{
}

StageLevel::~StageLevel() 
{
}

void StageLevel::Loading()
{
}

void StageLevel::Update()
{
}

void StageLevel::LevelChangeStart()
{
	CreateActor<Player>("Player", (int)ORDER::PLAYER);
}

void StageLevel::LevelChangeEnd()
{
}

