#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <Windows.h>

GameEngineActor::GameEngineActor()
	: Level_(nullptr)
	, Position_()
	, Scale_()
{
}

GameEngineActor::~GameEngineActor() 
{
}

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(Position_, Scale_);
	
	Rectangle(GameEngineWindow::GetHDC(), 
		DebugRect.CenterLeft(), DebugRect.CenterTop(), 
		DebugRect.CenterRight(), DebugRect.CenterBot()
	);
}
