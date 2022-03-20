#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

// 설명 :
class GameEngineImage : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineImage();
	~GameEngineImage();

	// delete Function
	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;

	bool Create(float4 _Scale);
	bool Create(HDC _DC);


	// GetObject로 얻은 이미지의 크기를 받는 함수
	inline float4 GetScale()
	{
		return float4(static_cast<float>(Info_.bmWidth), static_cast<float>(Info_.bmHeight));
	}

	inline HDC ImageDC()
	{
		return ImageDC_;
	}

	// 다른 이미지를 인자로 받아서 복사받는다.
	void BitCopy(GameEngineImage* _Other);
	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale);


protected:

private:
	HDC ImageDC_;
	HBITMAP BitMap_;
	HBITMAP OldBitMap_;
	BITMAP Info_;

	void ImageScaleCheck();

};

