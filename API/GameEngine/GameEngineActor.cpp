#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <Windows.h>
#include "GameEngine.h"
#include "GameEngineRenderer.h"

GameEngineActor::GameEngineActor()
	: Level_(nullptr)
	, Position_()
	, Scale_()
{
}

GameEngineActor::~GameEngineActor() 
{
	// 렌더러 삭제
	std::list<GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
	std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		// 안전한 지우기는 필수! 두번 이상들어올 수 있다.
		if (nullptr == (*StartIter))
		{
			continue;
		}
		delete (*StartIter);
		(*StartIter) = nullptr;
	}
}

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(Position_, Scale_);
	
	Rectangle(GameEngine::BackBufferDC(),
		DebugRect.CenterLeft(), DebugRect.CenterTop(), 
		DebugRect.CenterRight(), DebugRect.CenterBot()
	);
}

GameEngineRenderer* GameEngineActor::CreateRenderer(
	const std::string& _Image,
	RenderPivot _PivotType /*= RenderPivot::CENTER*/,
	const float4& _PivotPos /*= { 0,0 }*/
)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer;
	
	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetType(_PivotType);

	RenderList_.push_back(NewRenderer);

	return NewRenderer;
}

void GameEngineActor::Renderering()
{
	StartRenderIter = RenderList_.begin();
	EndRenderIter = RenderList_.end();

	for (; StartRenderIter != EndRenderIter; ++StartRenderIter)
	{
		(*StartRenderIter)->Render();
	}
}
