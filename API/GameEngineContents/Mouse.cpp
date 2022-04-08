#include "Mouse.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <Windows.h>

Mouse::Mouse() 
{
}

Mouse::~Mouse() 
{
}

void Mouse::Start()
{
}

void Mouse::Update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(GameEngineWindow::GetHWND(), &pt);

	SetPosition({ static_cast<float>(pt.x),static_cast<float>(pt.y) });

}

void Mouse::Render()
{
	Rectangle(GameEngine::BackBufferDC(),
		GetPosition().ix() - 20, GetPosition().iy() - 20,
		GetPosition().ix() + 20, GetPosition().iy() + 20);
}

