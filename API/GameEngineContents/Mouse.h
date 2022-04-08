#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Mouse : public GameEngineActor
{
public:
	// constrcuter destructer
	Mouse();
	~Mouse();

	// delete Function
	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

protected:

private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

};

