#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngine.h"

GameEngineRenderer::GameEngineRenderer() 
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "존재하지 않는 이미지를 랜더러에 세팅하려고 했습니다.");
		return;
	}

	Image_ = FindImage;

}

void GameEngineRenderer::Render()
{
	GameEngine::BackBufferImage()->BitCopyCenter(Image_, GetPosition());
}

