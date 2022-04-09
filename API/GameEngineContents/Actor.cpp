#include "Actor.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

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