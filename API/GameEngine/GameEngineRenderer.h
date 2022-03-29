#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
// ���� :
class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	inline void SetTransColor(unsigned int _Color)
	{
		TransColor_ = _Color;
	}

	inline void SetPivot(const float4& _Pos)
	{
		RenderPivot_ = _Pos;
	}

	inline void SetType(const RenderPivot& _Type)
	{
		PivotType_ = _Type;
	}

	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}

	void SetImageScale();


	inline void SetScale(const float4& _Scale)
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}

	void SetImage(const std::string& _Name);

	void SetIndex(size_t _Index, float4 _Scale = { -1.0f, -1.0f });

protected:
	void Render();

private:
	GameEngineImage* Image_;	
	RenderPivot PivotType_;		// ���� bot ��, �̹��� ������� �߽����� ����Ұ��ΰ�
	RenderScaleMode ScaleMode_;	// ENUM(Image, User), ������ �������� �⺻������ �����ΰ�, ���α׷��Ӱ� ������ USER������ �����ΰ�.

	// ȭ�鿡�� ����� ��ǥ�� ũ��
	float4 RenderPivot_;		// �׷��� DC�� ������
	float4 RenderScale_;		// ��� ũ��� �׸����ΰ�.

	// �̹������� �߶� ��ǥ�� ũ��
	float4 RenderImagePivot_;	// ����������� �̹��� ���� ��ǥ
	float4 RenderImageScale_;	// ����������� �̹��� ��ĭ�� ũ��

	unsigned int TransColor_;	// TransParents ���� �� ������ RGB ��

};

