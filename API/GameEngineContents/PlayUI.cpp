#include "PlayUI.h"
#include "Define.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

PlayUI::PlayUI() 
{
}

PlayUI::~PlayUI() 
{
}

void PlayUI::Start()
{
	// ���͸� ȭ�� �߾ӿ� ���´�.
	SetPosition({ WINCX>>1, WINCY>>1 });

	// ȭ�� Ư�� ��ġ�� UI �������� �����.
	{
		//GameEngineRenderer* NewRenderer = CreateRenderer("�̹��� ��� �߰�");
		//NewRenderer->SetPivot();	// �������� ��� ��ġ ����

		//NewRenderer->CameraEffectOff();	// UI�� ī�޶��� ������ ���� �ʴ´�. EX) HP��, ������ ��
	}
}

void PlayUI::Update()
{
}

void PlayUI::Render()
{
	// DebugRectRender();
}

