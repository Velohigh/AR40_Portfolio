#include "KatanaZero.h"
#include "TitleLevel.h"
#include "StageLevel.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>

KatanaZero::KatanaZero() 
{
}

KatanaZero::~KatanaZero() 
{
}

void KatanaZero::GameInit()
{
	// ������ ũ�� ����
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 0,0 }, { 1280, 720 });

	// ���丮, ���ҽ����� ��� ����
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.Move("Resources");
	ResourcesDir.Move("Player");

	// �����ȿ� ��� �̹��� ������ ã�´�.
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");
	// ��� �̹��� ������ ���鼭 �̹��� �Ŵ����� �ε��Ѵ�.
	for (size_t i = 0; i < AllImageFileList.size(); ++i)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	// 
	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("idle.bmp");
	Image->Cut({ 36, 35 });	// �̹��� ������ �ȼ�ũ�� ����x����


	CreateLevel<TitleLevel>("Title");
	CreateLevel<StageLevel>("Stage");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Stage");

}

void KatanaZero::GameLoop()
{
}

void KatanaZero::GameEnd()
{
}

