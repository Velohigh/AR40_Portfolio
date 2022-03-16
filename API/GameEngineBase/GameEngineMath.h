#pragma once

// 설명 : 게임 엔진에서 쓰는 수학과 관련된 모든 기능을 모아두는 클래스.
class GameEngineMath
{
private:
	// constrcuter destructer
	GameEngineMath();
	~GameEngineMath();

	// delete Function
	GameEngineMath(const GameEngineMath& _Other) = delete;
	GameEngineMath(GameEngineMath&& _Other) noexcept = delete;
	GameEngineMath& operator=(const GameEngineMath& _Other) = delete;
	GameEngineMath& operator=(GameEngineMath&& _Other) noexcept = delete;

protected:

private:

};

class float4
{
public:
	float x;
	float y;
	float z;
	float w;

public:
	int ix()
	{
		return static_cast<int>(x);
	}

	int iy()
	{
		return static_cast<int>(y);
	}

	int iz()
	{
		return static_cast<int>(z);
	}

	int iw()
	{
		return static_cast<int>(w);
	}

	int hix()
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy()
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiz()
	{
		return static_cast<int>(x * 0.5f);
	}

	float4 Half()
	{
		return { x * 0.5f, y * 0.5f, z * 0.5f , 1.0f };
	}

};

struct GameEngineRect
{
public:
	float4 Pos;
	float4 Scale;

public:
	int CenterLeft()
	{
		return Pos.ix() - Scale.hix();
	}

	int CenterRight()
	{
		return Pos.ix() + Scale.hix();
	}

	int CenterTop()
	{
		return Pos.iy() - Scale.hiy();
	}

	int CenterBot()
	{
		return Pos.iy() + Scale.hiy();
	}



public:
	GameEngineRect(float4 _Pos, float4 _Scale)
		: Pos(_Pos), Scale(_Scale)
	{

	}

};
