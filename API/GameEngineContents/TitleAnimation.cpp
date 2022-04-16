#include "TitleAnimation.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Define.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

TitleAnimation::TitleAnimation() 
{
}

TitleAnimation::~TitleAnimation() 
{
}

void TitleAnimation::Start()
{
	{
		SetPosition({ 0,0 });	
		SetScale(GameEngineWindow::GetScale());
		BackAnimationRenderer_ = CreateRenderer(static_cast<int>(ORDER::UI));		// ��׶���� �������� �̹����� �޶����Ƿ� None �̹����� ó���� �������ش�.

		BackAnimationRenderer_->SetPivot({ WINCX >> 1, WINCY >> 1 });
	}

	if (strcmp(GetLevel()->GetNameConstPtr(), "Title") == 0)
	{
		BackAnimationRenderer_->CreateFolderAnimation("TitleAnimation_0", "TitleAnimation_0", 0, 229, 0.033f, true);
		BackAnimationRenderer_->CreateFolderAnimation("TitleAnimation_1", "TitleAnimation_1", 0, 229, 0.033f, true);
		BackAnimationRenderer_->CreateFolderAnimation("TitleAnimation_2", "TitleAnimation_2", 0, 229, 0.033f, true);
		BackAnimationRenderer_->CreateFolderAnimation("TitleAnimation_3", "TitleAnimation_3", 0, 229, 0.033f, true);
		BackAnimationRenderer_->CreateFolderAnimation("TitleAnimation_4", "TitleAnimation_4", 0, 229, 0.033f, true);

		BackAnimationRenderer_->SetPivot({ WINCX >> 1, WINCY >> 1 });
		BackAnimationRenderer_->SetScale({ WINCX, WINCY });

		BackAnimationRenderer_->ChangeAnimation("TitleAnimation_0");
		BackAnimationRenderer_->SetTransColor(RGB(255, 255, 255));	// �̹������� ������ ��
	}

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Jump", VK_SPACE);	//virtual key (������ Ű)
		GameEngineInput::GetInst()->CreateKey("Dodge", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("Attack", VK_LBUTTON);	// VK_LBUTTON ���콺 ��Ŭ��

		GameEngineInput::GetInst()->CreateKey("Arrow_Up", VK_UP);
		GameEngineInput::GetInst()->CreateKey("Arrow_Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Arrow_Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Arrow_Right", VK_RIGHT);

		GameEngineInput::GetInst()->CreateKey("Enter", VK_RETURN);

		GameEngineInput::GetInst()->CreateKey("Fire", 'Q');
		GameEngineInput::GetInst()->CreateKey("DebugRender", VK_F1);
	}


}

void TitleAnimation::Update()
{
	// ����
	if (true == GameEngineInput::GetInst()->IsDown("Arrow_Down") ||
		true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		if (iSelect < 4)
		iSelect += 1;
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Arrow_Up") ||
		true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{
		if (iSelect > 0)
			iSelect -= 1;
	}


	//  ���� �ٲ���
	if (iSelect != iPreSelect)
	{
		if (iSelect == 0)
		{
			BackAnimationRenderer_->ChangeAnimation("TitleAnimation_0");
		}
		else if (iSelect == 1)
		{
			BackAnimationRenderer_->ChangeAnimation("TitleAnimation_1");
		}

		else if (iSelect == 2)
		{
			BackAnimationRenderer_->ChangeAnimation("TitleAnimation_2");
		}
		else if (iSelect == 3)
		{
			BackAnimationRenderer_->ChangeAnimation("TitleAnimation_3");
		}
		else if (iSelect == 4)
		{
			BackAnimationRenderer_->ChangeAnimation("TitleAnimation_4");
		}
		iPreSelect = iSelect;
	}

	if (iSelect == 0 &&
		(true == GameEngineInput::GetInst()->IsDown("Enter") || true == GameEngineInput::GetInst()->IsDown("Jump")))
	{
		// ���� ü����
		GameEngine::GetInst().ChangeLevel("Stage1");
	}

}

void TitleAnimation::Render()
{
}

