#include "Actor.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngine.h>

Actor::Actor() 
{
}

Actor::~Actor() 
{
}

void Actor::DirAnimationCheck()
{

	if (PreDir_ != CurDir_)
	{

		if (CurDir_ == ActorDir::Right)
		{
			ChangeDirText = "Right";
		}
		else if (CurDir_ == ActorDir::Left)
		{
			ChangeDirText = "Left";
		}

		ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
		PreDir_ = CurDir_;
	}

}

void Actor::ChangeState(ActorState _State)
{
	if (_State != CurState_)	// 상태가 바뀔때 한번만 실행시켜준다.
	{
		switch (_State)
		{
		case ActorState::Idle:
			IdleStart();
			break;
		case ActorState::Walk:
			IdleStart();
			break;
		case ActorState::Run:
			RunStart();
			break;
		case ActorState::Attack:
			AttackStart();
			break;
		case ActorState::END:
			break;
		default:
			break;
		}
	}
	CurState_ = _State;
}

void Actor::ActorStateUpdate()
{
	switch (CurState_)
	{
	case ActorState::Idle:
		IdleUpdate();
		break;
	case ActorState::Walk:
		WalkUpdate();
		break;
	case ActorState::Run:
		RunUpdate();
		break;
	case ActorState::Attack:
		AttackUpdate();
		break;
	case ActorState::END:
		break;
	default:
		break;
	}

}

void Actor::DebugRender()
{
	// 디버그용
	if (GetAsyncKeyState(VK_F1))
	{

		TCHAR szBuff[64] = "";
		TCHAR StateBuff[64] = {};

		{
			if (CurState_ == ActorState::Idle)
				sprintf_s(StateBuff, "STATE : Idle");
			else if (CurState_ == ActorState::Run)
				sprintf_s(StateBuff, "STATE : Run");
		}

		sprintf_s(szBuff, "Player X: %d, Y: %d", GetPosition().ix(), GetPosition().iy());
		TextOut(GameEngine::GetInst().BackBufferDC(), GetCameraEffectPosition().ix(), GetCameraEffectPosition().iy() - 120, szBuff, static_cast<int>(strlen(szBuff)));
		TextOut(GameEngine::GetInst().BackBufferDC(), GetCameraEffectPosition().ix(), GetCameraEffectPosition().iy() - 100, StateBuff, static_cast<int>(strlen(StateBuff)));

	}
}
