#pragma once
#include <GameEngine/GameEngine.h>

// ���� : 
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

	// GameEngine��(��) ���� ��ӵ�
	virtual void GameInit() override;
	virtual void GameLoop() override;
	virtual void GameEnd() override;


protected:

private:
	void ResourceLoad();



};

 