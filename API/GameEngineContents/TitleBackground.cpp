#include "TitleBackground.h"
#include <GameEngineBase/GameEngineWindow.h>

TitleBackground::TitleBackground() 
{
}

TitleBackground::~TitleBackground() 
{
}

void TitleBackground::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());
}

void TitleBackground::Update()
{
}

void TitleBackground::Render()
{
	DebugRectRender();
}

