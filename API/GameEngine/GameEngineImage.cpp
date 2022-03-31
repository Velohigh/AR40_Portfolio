#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

// 이미지 라이브러리
#pragma comment(lib, "msimg32.lib")

GameEngineImage::GameEngineImage()
	: ImageDC_(nullptr), BitMap_(nullptr), OldBitMap_(nullptr), Info_()
{
}

GameEngineImage::~GameEngineImage() 
{
	// window에서 할당해온녀석들은 릭으로 체크가 안되지만
	// 지워주는게 깔끔하다.
	// 당연히 윈도우에게 할당해왔으므로 윈도우의 함수를 이용해서 지워야한다.
	if (nullptr != BitMap_)
	{
		DeleteObject(BitMap_);
		BitMap_ = nullptr;
	}

	if (nullptr != OldBitMap_)
	{
		DeleteObject(OldBitMap_);
		OldBitMap_ = nullptr;
	}

	if (nullptr != ImageDC_)
	{
		DeleteDC(ImageDC_);
		ImageDC_ = nullptr;
	}

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


bool GameEngineImage::Create(HDC _DC)
{
	ImageDC_ = _DC;
	ImageScaleCheck();
	return true;
}

bool GameEngineImage::Load(const std::string& _Path)
{
	BitMap_ = static_cast<HBITMAP>(LoadImageA(
		nullptr,	// NULL 넣으면 기본으로 세팅해줌.
		_Path.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE
		));

	if (nullptr == BitMap_)
	{
		MsgBoxAssertString(_Path + " 이미지 로드에 실패했습니다. 여러분들이 살펴봐야할 문제 1.경로 2.디버깅");
	}

	// 비트맵을 조작할 DC도 만든다.
	// 그러나 DC는 만들어질때 기본 비트맵을 가지고 만들어진다.
	ImageDC_ = CreateCompatibleDC(nullptr);

	// ImageDC에 붙어있는 비트맵을 #2로 바꿔줘, 기본 생성 비트맵은 OldBitMap으로 받아준다.
	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();
	return true;

}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	BitCopy(_Other, { 0, 0 }, _Other->GetScale(), { 0, 0 });
}

// 다른 이미지가 들어와서
void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot)
{
	// 윈도우에서 지원해주는 일반적인 dc vs dc의 복사함수입니다.
	BitBlt(
		ImageDC_, // 여기에 복사해라.
		_CopyPos.ix(), // 내 이미지의 이 부분 x
		_CopyPos.iy(), // 내 이미지의 이 부분 y 에 복사해라
		_CopyScale.ix(), // 내 이미지의 이 크기만큼 x
		_CopyScale.iy(), // 내 이미지의 이 크기만큼 y
		_Other->ImageDC_, // 복사하려는 대상은
		_OtherPivot.ix(), // 복사하려는 대상의 시작점X
		_OtherPivot.iy(),// 복사하려는 대상의 시작점Y
		SRCCOPY // 복사하라는 명령
	);
}

void GameEngineImage::ImageScaleCheck()
{
	// DC 내부에 박혀있는 BITMAP을 꺼내오는 함수
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
	// 함수를 통해 전달된 비트맵의 크기를 자동으로 조사하여 BITMAP의 정보를 #3 에 저장하는 함수.
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}

//void GameEngineImage::Cut(const float4&, const float4& _CutScale)
//{
//}

void GameEngineImage::CutCount(int _x, int _y)
{
	float4 Scale = { GetScale().x / _x, GetScale().y / _y };
	Cut(Scale);
}

void GameEngineImage::Cut(const float4& _CutSize)
{
	//// 이미지를 딱맞게 잘라야 쓸수있다.
	//if (0 != (GetScale().ix() % _CutSize.ix()))
	//{
	//	MsgBoxAssert("자를수 있는 수치가 딱 맞아떨어지지 않습니다.");
	//}

	//if (0 != (GetScale().iy() % _CutSize.iy()))
	//{
	//	MsgBoxAssert("자를수 있는 수치가 딱 맞아떨어지지 않습니다.");
	//}

	int XCount = GetScale().ix() / _CutSize.ix();
	int YCount = GetScale().iy() / _CutSize.iy();

	for (int y = 0; y < YCount; y++)
	{
		for (int x = 0; x < XCount; x++)
		{
			CutPivot_.push_back({ static_cast<float>(x * _CutSize.ix()), static_cast<float>(y * _CutSize.iy()) });
			CutScale_.push_back(_CutSize);
		}
	}

}

int GameEngineImage::GetImagePixel(int _x, int _y)
{
	// 맵 바깥의 Pixel 을 달라고 하면 검은색(갈수 없는곳) 을 리턴한다.
	if (0 > _x || 0 > _y)
	{
		return RGB(0, 0, 0);
	}

	if (GetScale().ix() <= _x || GetScale().iy() <= _y)
	{
		return RGB(0, 0, 0);
	}

	return GetPixel(ImageDC_ ,_x, _y);	// 이미지의 x,y 픽셀의 색상 정보를 가져온다.
}


//////////////////////////////////////////////////////////////////////// Trans

// 다른 이미지가 들어와서
void GameEngineImage::TransCopy(GameEngineImage* _Other, const float4& _CopyPos,
	const float4& _CopyScale,
	const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor)
{
	// 윈도우에서 지원해주는 일반적인 dc vs dc의 복사함수입니다.
	TransparentBlt(
		ImageDC_, // 여기에 복사해라.
		_CopyPos.ix(), // 내 이미지의 이 부분 x
		_CopyPos.iy(), // 내 이미지의 이 부분 y 에 복사해라
		_CopyScale.ix(), // 내 이미지의 이 크기만큼 x
		_CopyScale.iy(), // 내 이미지의 이 크기만큼 y
		_Other->ImageDC_, // 복사하려는 대상은
		_OtherPivot.ix(), // 복사하려는 대상의 시작점X
		_OtherPivot.iy(), // 복사하려는 대상의 시작점Y
		_OtherScale.ix(), // 복사하려는 대상의 크기X
		_OtherScale.iy(), // 복사하려는 대상의 크기Y
		_TransColor // 복사하라는 명령
	);
}