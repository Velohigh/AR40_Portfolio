#pragma once
#include <random>

// ���� :
// ���ʷ�����
// ������ �������� �����Ѵ�.

// ������
// ���� �������ִ� ������ �Ѵ�. ex) 0~100 ������ ��
class GameEngineRandom
{
	// ���׷����� 
	// �޸��� Ʈ�������� �˰������� ��Ʈ�� �ڼ��� �༮
	std::mt19937_64 mt_;

	// �̳༮���� ���ڸ� ������ �� �ִ�.
	//std::uniform_int_distribution<int> Uniform;
public:
	int RandomInt(int _Min, int _Max)
	{
		std::uniform_int_distribution<int> Uniform(_Min, _Max);
		return Uniform(mt_);
	}

	int RandomFloat(float _Min, float _Max)
	{
		// �Ǽ��� ������� Real
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

