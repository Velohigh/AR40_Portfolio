#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

// ���� :
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

	bool Load(const std::string& _Path);


	// GetObject�� ���� �̹����� ũ�⸦ �޴� �Լ�
	inline float4 GetScale()
	{
		return float4(static_cast<float>(Info_.bmWidth), static_cast<float>(Info_.bmHeight));
	}

	inline HDC ImageDC()
	{
		return ImageDC_;
	}

	// �ٸ� �̹����� ���ڷ� �޾Ƽ� ����޴´�.
	void BitCopy(GameEngineImage* _Other);
	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos);	// ����ϰ� ���� ��ġ�� ���ڷ� �޴� �Լ�, ���Ǽ��� ����.
	void BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos);	// �̹����� �߾� �������� ����
	void BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);	// �̹����� �߾ӱ��� + Pivot ����ġ ����
	void BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos);		// �̹����� �� �������� ����.
	void BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);	// �̹����� �� ���� ���� + Pivot ����ġ ����
	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale);


protected:

private:
	HDC ImageDC_;
	HBITMAP BitMap_;
	HBITMAP OldBitMap_;
	BITMAP Info_;

	void ImageScaleCheck();

};

