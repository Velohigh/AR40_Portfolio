#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
// 설명 :
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
	RenderPivot PivotType_;		// 센터 bot 등, 이미지 어느곳을 중심으로 출력할것인가
	RenderScaleMode ScaleMode_;	// ENUM(Image, User), 엔진이 정의해준 기본값으로 쓸것인가, 프로그래머가 정의한 USER값으로 쓸것인가.

	// 화면에서 출력할 좌표와 크기
	float4 RenderPivot_;		// 그려질 DC의 시작점
	float4 RenderScale_;		// 어느 크기로 그릴것인가.

	// 이미지에서 잘라낼 좌표와 크기
	float4 RenderImagePivot_;	// 복사받으려는 이미지 시작 좌표
	float4 RenderImageScale_;	// 복사받으려는 이미지 한칸의 크기

	unsigned int TransColor_;	// TransParents 에서 쓸 제외할 RGB 값

};

