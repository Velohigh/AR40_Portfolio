#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <Windows.h>
#include "GameEngine.h"
#include "GameEngineRenderer.h"
#include "GameEngineCollision.h"

GameEngineActor::GameEngineActor()
	: Level_(nullptr)
	, Position_()
	, Scale_()
{
}

GameEngineActor::~GameEngineActor() 
{
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

	{
		// 콜리전 삭제
		std::list<GameEngineCollision*>::iterator StartIter = CollisionList_.begin();
		std::list<GameEngineCollision*>::iterator EndIter = CollisionList_.end();

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
}

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(Position_, Scale_);
	
	Rectangle(GameEngine::BackBufferDC(),
		DebugRect.CenterLeft(), DebugRect.CenterTop(), 
		DebugRect.CenterRight(), DebugRect.CenterBot()
	);
}


// 이미지 세팅 None 버전, 일단 렌더러를 만들고 그 후에 이미지를 넣는다.
GameEngineRenderer* GameEngineActor::CreateRenderer(
	int _Order, 
	RenderPivot _PivotType /*= RenderPivot::CENTER*/, 
	const float4& _PivotPos /*= { 0,0 }*/)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	if (_Order != static_cast<int>(EngineMax::RENDERORDERMAX))
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(_Order);	// 순수하게 Order값 세팅
	}
	else
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(GetOrder());
	}
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);

	GetLevel()->AddRenderer(NewRenderer);	// 렌더러 출력은 레벨에서 하므로, 레벨에 넣어준다.
	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

// 화면 출력과 이미지 스케일을 똑같은 크기로 렌더러를 만든다.
GameEngineRenderer* GameEngineActor::CreateRenderer(
	const std::string& _Image,
	int _Order/* = static_cast<int>(EngineMax::RENDERORDERMAX)*/, 
	RenderPivot _PivotType /*= RenderPivot::CENTER*/, 
	const float4& _PivotPos /*= { 0,0 }*/)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer;
	
	NewRenderer->SetActor(this);
	if (_Order != static_cast<int>(EngineMax::RENDERORDERMAX))
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(_Order);
	}
	else
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(GetOrder());
	}
	NewRenderer->SetImage(_Image);			// 이미지를 정해주면서, RenderScale 에 이미지 크기 1배율로 넣는다.
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);

	GetLevel()->AddRenderer(NewRenderer);	// 렌더러 출력은 레벨에서 하므로, 레벨에 넣어준다.
	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

// 화면에 출력될 크기를 Scale로 맞춰 렌더러를 만든다.
GameEngineRenderer* GameEngineActor::CreateRendererToScale(
	const std::string& _Image, const float4& _Scale,
	int _Order/* = static_cast<int>(EngineMax::RENDERORDERMAX)*/,
	RenderPivot _PivotType /*= RenderPivot::CENTER*/, const float4& _PivotPos /*= { 0,0 }*/
)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);		

	if (_Order != static_cast<int>(EngineMax::RENDERORDERMAX))
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(_Order);
	}
	else
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(GetOrder());
	}

	NewRenderer->SetImage(_Image);		// 이미지를 정하고, RenderScale_을 이미지 크기와 똑같이 맞춘다.
	NewRenderer->SetScale(_Scale);		// 화면에 출력될 크기를 정한다. (RenderScale_)
	NewRenderer->SetPivot(_PivotPos);	// 화면에 출력될 좌표를 정한다. (RenderPivot_)
	NewRenderer->SetPivotType(_PivotType);	// 좌표를 Center , Bot 등 이미지를 어디를 중심으로 출력할지 정한다.

	GetLevel()->AddRenderer(NewRenderer);	// 렌더러 출력은 레벨에서 하므로, 레벨에 넣어준다.
	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineCollision* GameEngineActor::CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot)
{
	GameEngineCollision* NewCollision = new GameEngineCollision();
	NewCollision->SetActor(this);
	NewCollision->SetScale(_Scale);
	NewCollision->SetPivot(_Pivot);

	GetLevel()->AddCollision(_GroupName, NewCollision);	// 콜리전은 레벨에서 관리한다! 생성,삭제는 액터에서 한다!!! 다시한번 메모.
	CollisionList_.push_back(NewCollision);

	return NewCollision;
}

void GameEngineActor::Release()
{
	{
		std::list<GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
		std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();

		for (; StartIter != EndIter;)
		{
			// 안전한 지우기는 필수! 두번 이상들어올 수 있다.
			if (false == (*StartIter)->IsDeath())
			{
				++StartIter;
				continue;
			}
			delete (*StartIter);
			StartIter = RenderList_.erase(StartIter);
		}
	}

	{
		std::list<GameEngineCollision*>::iterator StartIter = CollisionList_.begin();
		std::list<GameEngineCollision*>::iterator EndIter = CollisionList_.end();

		for (; StartIter != EndIter;)
		{
			// 안전한 지우기는 필수! 두번 이상들어올 수 있다.
			if (false == (*StartIter)->IsDeath())
			{
				++StartIter;
				continue;
			}
			delete (*StartIter);
			StartIter = CollisionList_.erase(StartIter);
		}
	}
}
