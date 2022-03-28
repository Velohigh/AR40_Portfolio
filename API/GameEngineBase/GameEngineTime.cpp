#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime* GameEngineTime::Inst_ = new GameEngineTime;
GameEngineTime::GameEngineTime()
{
}

GameEngineTime::~GameEngineTime() 
{
}

void GameEngineTime::Reset()
{
	// 시작 시점의 CPU 클럭 수
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&PrevCount_));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));
	// 타이머의 주파수를 얻어온다.
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&SecondCount_));
	Update();

}
void GameEngineTime::Update()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));
	RealDeltaTime_ = (static_cast<double>(CurrentCount_) - static_cast<double>(PrevCount_)) / static_cast<double>(SecondCount_);
	PrevCount_ = CurrentCount_;
	DeltaTime_ = static_cast<float>(RealDeltaTime_);	// float 형을 쓰는이유 : double은 느리니까..
}

