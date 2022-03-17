#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage() 
{
}

GameEngineImage::~GameEngineImage() 
{
}

bool GameEngineImage::Create(float4 _Scale)
{
	if (true == _Scale.IsZero2D())
	{
		MsgBoxAssert("크기가 0인 이미지를 만들려고 했습니다.");
		return false;
	}

	// 먼저 비트맵을 만든다.
	// 이미지 크기만한.
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

	// 비트맵을 조작할 DC도 만든다.
	// 그러나 DC는 만들어질때 기본 비트맵을 가지고 만들어진다.
	ImageDC_ = CreateCompatibleDC(nullptr);

	// ImageDC에 붙어있는 비트맵을 #2로 바꿔줘, 기본 생성 비트맵은 OldBitMap으로 받아준다.
	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;

}

void GameEngineImage::ImageScaleCheck()
{
	// 함수를 통해 전달된 비트맵의 크기를 자동으로 조사하여 BITMAP의 정보를 #3 에 저장하는 함수.
	GetObject(BitMap_, sizeof(BITMAP), &Info_);

}

