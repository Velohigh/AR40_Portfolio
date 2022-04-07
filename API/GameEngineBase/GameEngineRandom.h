#pragma once
#include <random>

// 설명 :
// 제너레이터
// 난수를 무작위로 생성한다.

// 유니폼
// 수를 제한해주는 역할을 한다. ex) 0~100 사이의 수
class GameEngineRandom
{
	// 제네레이터 
	// 메르센 트위스터의 알고리즘으로 비트를 뒤섞는 녀석
	std::mt19937_64 mt_;

	// 이녀석으로 숫자를 제한할 수 있다.
	//std::uniform_int_distribution<int> Uniform;
public:
	int RandomInt(int _Min, int _Max)
	{
		std::uniform_int_distribution<int> Uniform(_Min, _Max);
		return Uniform(mt_);
	}

	int RandomFloat(float _Min, float _Max)
	{
		// 실수는 생성기사 Real
		std::uniform_real_distribution<float> Uniform(_Min, _Max);
		return Uniform(mt_);
	}


public:
	// constrcuter destructer
	GameEngineRandom();
	~GameEngineRandom();

	// delete Function
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;

protected:

private:

};

