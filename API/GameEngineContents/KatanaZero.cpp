#include "KatanaZero.h"
#include "TitleLevel.h"
#include "Stage1Level.h"
#include "Stage2Level.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Define.h"

KatanaZero::KatanaZero() 
{
}

KatanaZero::~KatanaZero() 
{
}

void KatanaZero::GameInit()
{
	// ������ ũ�� ����
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 0,0 }, { WINCX, WINCY });

	{
		// 
		// ���丮, ���ҽ����� ��� ����
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Player");

		// �����ȿ� ��� �̹��� ������ ã�´�.
		std::vector<GameEngineFile> PlayerImageFileList = ResourcesDir.GetAllFile("bmp");
		// ��� �̹��� ������ ���鼭 �̹��� �Ŵ����� �ε��Ѵ�.

		for (size_t i = 0; i < PlayerImageFileList.size(); ++i)
		{
			GameEngineImageManager::GetInst()->Load(PlayerImageFileList[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Title");

		std::vector<GameEngineFile> TitleImageFileList = ResourcesDir.GetAllFile("bmp");

		for (size_t i = 0; i < TitleImageFileList.size(); ++i)
		{
			GameEngineImageManager::GetInst()->Load(TitleImageFileList[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Stage");

		std::vector<GameEngineFile> StageImageFileList = ResourcesDir.GetAllFile("bmp");

		for (size_t i = 0; i < StageImageFileList.size(); ++i)
		{
			GameEngineImageManager::GetInst()->Load(StageImageFileList[i].GetFullPath());
		}
	}

	// Title

	// Stage

	// Player
	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("idle_Ani.bmp");
	Image->Cut({ 36, 35 });	// �̹��� ������ �ȼ�ũ�� ����x����

	// ���� ü���� Ű�� �������� �����д�! �� �������� ���� ������, ������ ��緹������ ����Ұ��̱� ����.
	if (false == GameEngineInput::GetInst()->IsKey("Stage1"))
	{
		GameEngineInput::GetInst()->CreateKey("Stage1", '1');
		GameEngineInput::GetInst()->CreateKey("Stage2", '2');
		GameEngineInput::GetInst()->CreateKey("Ending", '3');
	}

	CreateLevel<TitleLevel>("Title");
	CreateLevel<Stage1Level>("Stage1");
	CreateLevel<Stage2Level>("Stage2");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Title");

}

void KatanaZero::GameLoop()
{
}

void KatanaZero::GameEnd()
{
}

