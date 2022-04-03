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
		// ������ ����
		std::list<GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
		std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			// ������ ������ �ʼ�! �ι� �̻���� �� �ִ�.
			if (nullptr == (*StartIter))
			{
				continue;
			}
			delete (*StartIter);
			(*StartIter) = nullptr;
		}
	}

	{
		// �ݸ��� ����
		std::list<GameEngineCollision*>::iterator StartIter = CollisionList_.begin();
		std::list<GameEngineCollision*>::iterator EndIter = CollisionList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			// ������ ������ �ʼ�! �ι� �̻���� �� �ִ�.
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


// �̹��� ���� None ����, �ϴ� �������� ����� �� �Ŀ� �̹����� �ִ´�.
GameEngineRenderer* GameEngineActor::CreateRenderer(RenderPivot _PivotType /*= RenderPivot::CENTER*/, const float4& _PivotPos /*= { 0,0 }*/)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	// NewRenderer->SetImageScale();
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);

	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

// ȭ�� ��°� �̹��� �������� �Ȱ��� ũ��� �������� �����.
GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _Image, RenderPivot _PivotType /*= RenderPivot::CENTER*/, const float4& _PivotPos /*= { 0,0 }*/)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer;
	
	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);			// �̹����� �����ָ鼭, RenderScale �� �̹��� ũ�� 1������ �ִ´�.
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);

	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

// ȭ�鿡 ��µ� ũ�⸦ Scale�� ���� �������� �����.
GameEngineRenderer* GameEngineActor::CreateRendererToScale(
	const std::string& _Image, const float4& _Scale,
	RenderPivot _PivotType /*= RenderPivot::CENTER*/, const float4& _PivotPos /*= { 0,0 }*/
)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);		
	NewRenderer->SetImage(_Image);		// �̹����� ���ϰ�, RenderScale_�� �̹��� ũ��� �Ȱ��� �����.
	NewRenderer->SetScale(_Scale);		// ȭ�鿡 ��µ� ũ�⸦ ���Ѵ�. (RenderScale_)
	NewRenderer->SetPivot(_PivotPos);	// ȭ�鿡 ��µ� ��ǥ�� ���Ѵ�. (RenderPivot_)
	NewRenderer->SetPivotType(_PivotType);	// ��ǥ�� Center , Bot �� �̹����� ��� �߽����� ������� ���Ѵ�.

	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

void GameEngineActor::Renderering()
{
	StartRenderIter = RenderList_.begin();
	EndRenderIter = RenderList_.end();

	for (; StartRenderIter != EndRenderIter; ++StartRenderIter)
	{
		if (false == (*StartRenderIter)->IsUpdate())	// ������, ���Ͱ� ������Ʈ ���°� �ƴ϶��
		{
			continue;
		}

		(*StartRenderIter)->Render();
	}
}

GameEngineCollision* GameEngineActor::CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot)
{
	GameEngineCollision* NewCollision = new GameEngineCollision();
	NewCollision->SetActor(this);
	NewCollision->SetScale(_Scale);
	NewCollision->SetPivot(_Pivot);

	GetLevel()->AddCollision(_GroupName, NewCollision);	// �ݸ����� �������� �����Ѵ�! ����,������ ���Ϳ��� �Ѵ�!!! �ٽ��ѹ� �޸�.
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
			// ������ ������ �ʼ�! �ι� �̻���� �� �ִ�.
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
			// ������ ������ �ʼ�! �ι� �̻���� �� �ִ�.
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
