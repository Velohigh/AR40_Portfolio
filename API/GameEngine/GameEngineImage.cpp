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
		MsgBoxAssert("ũ�Ⱑ 0�� �̹����� ������� �߽��ϴ�.");
		return false;
	}

	// ���� ��Ʈ���� �����.
	// �̹��� ũ�⸸��.
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

	// ��Ʈ���� ������ DC�� �����.
	// �׷��� DC�� ��������� �⺻ ��Ʈ���� ������ ���������.
	ImageDC_ = CreateCompatibleDC(nullptr);

	// ImageDC�� �پ��ִ� ��Ʈ���� #2�� �ٲ���, �⺻ ���� ��Ʈ���� OldBitMap���� �޾��ش�.
	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;

}

void GameEngineImage::ImageScaleCheck()
{
	// �Լ��� ���� ���޵� ��Ʈ���� ũ�⸦ �ڵ����� �����Ͽ� BITMAP�� ������ #3 �� �����ϴ� �Լ�.
	GetObject(BitMap_, sizeof(BITMAP), &Info_);

}

