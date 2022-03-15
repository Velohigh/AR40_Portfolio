#include "TitleLogo.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <Windows.h>

TitleLogo::TitleLogo() 
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
}

void TitleLogo::Update()
{
}

void TitleLogo::Render()
{
	Rectangle(GameEngineWindow::GETDC(), 100, 100, 1000, 500);
}

