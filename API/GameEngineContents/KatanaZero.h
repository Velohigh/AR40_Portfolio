#pragma once
#include <GameEngine/GameEngine.h>

// 설명 : 
class KatanaZero : public GameEngine
{
public:
	// constrcuter destructer
	KatanaZero();
	~KatanaZero();

	// delete Function
	KatanaZero(const KatanaZero& _Other) = delete;
	KatanaZero(KatanaZero&& _Other) noexcept = delete;
	KatanaZero& operator=(const KatanaZero& _Other) = delete;
	KatanaZero& operator=(KatanaZero&& _Other) noexcept = delete;

	// GameEngine을(를) 통해 상속됨
	virtual void GameInit() override;
	virtual void GameLoop() override;
	virtual void GameEnd() override;


protected:

private:
	void ResourceLoad();



};

 