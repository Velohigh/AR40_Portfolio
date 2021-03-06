#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Effect_JumpCloud.h"
#include "Effect_LandCloud.h"
#include "Effect_DustCloud.h"
#include "Effect_Slash.h"
#include "ContentsEnums.h"
#include "Mouse.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineSound.h>
#include <random>
#include "Level.h"

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서
#include "Bullet.h"						// 총알을 만들고 싶다.
#include <time.h>

extern float4 g_AttackDir;

void Player::IdleStart()
{
	// 애니메이션 체인지
	AnimationName_ = "Idle_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(0.f);
}

void Player::IdleToRunStart()
{
	AnimationName_ = "Idle_To_Run_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(200.f);
}

void Player::AttackStart()
{
	std::random_device rd;
	std::mt19937_64 mt_(rd());
	std::uniform_int_distribution<int> IntRange(0, 2);
	int Num = IntRange(mt_);

	// 어택 사운드 랜덤 재생
	if (Num == 0)
	{
		GameEngineSoundPlayer NewSound = GameEngineSound::SoundPlayControl("sound_player_slash_1.wav");
		NewSound.Volume(0.9f);
	}
	else if (Num == 1)
	{
		GameEngineSoundPlayer NewSound = GameEngineSound::SoundPlayControl("sound_player_slash_2.wav");
		NewSound.Volume(0.9f);
	}
	else if (Num == 2)
	{
		GameEngineSoundPlayer NewSound = GameEngineSound::SoundPlayControl("sound_player_slash_3.wav");
		NewSound.Volume(0.9f);
	}

	// 어택 이펙트
	Effect_Slash* NewEffect = GetLevel()->CreateActor<Effect_Slash>((int)ORDER::Effect);
	NewEffect->SetPosition(GetPosition());

	// 공격 방향은 마우스 방향 고정
	AnimationName_ = "Attack_";
	if (Mouse_->GetPosition().x >= (GetCameraEffectPosition() + float4{ 0,-35 }).x)
	{
		CurDir_ = PlayerDir::Right;
		ChangeDirText = "Right";
	}
	else if (Mouse_->GetPosition().x < (GetCameraEffectPosition() + float4{ 0,-35 }).x)
	{
		CurDir_ = PlayerDir::Left;
		ChangeDirText = "Left";
	}
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);

	// 플레이어->마우스 방향 벡터 획득
	float4 AttackDir = Mouse_->GetPosition() - (GetCameraEffectPosition() + float4{ 0,-35 });
	AttackDir.Normal2D();

	// 전역 변수 공격방향에 저장.
	g_AttackDir = AttackDir;

	// 공격판정 콜리전 생성
	PlayerAttackCollision_ = CreateCollision("PlayerAttack", { 76, 76 }, AttackDir * 66 + float4{ 0,-35 });

	MoveDir = float4::ZERO;
	// 공중에서 최초 한번의 공격일때만 y축 전진성을 부여한다.
	if (AttackCount_ <= 0)
	{
		MoveDir = AttackDir * 480.f;
		++AttackCount_;
	}
	else if (AttackCount_ >= 1)
	{
		// 플레이어는 2회 공격이후 y축 이동 제한, 공중 무한 날기 방지용
		if (AttackDir.y < 0)
		{
			MoveDir = float4{ AttackDir.x, 0 } * 480.f;
		}
		else
		{
			MoveDir = float4{ AttackDir.x, AttackDir.y} * 480.f;
		}
	}
	Gravity_ = 10.f;	// 공격 후 중력 초기화

}

void Player::FallStart()
{
	AnimationName_ = "Fall_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
}

void Player::DodgeStart()
{

	// 닷지 사운드
	{
		GameEngineSoundPlayer NewSound = GameEngineSound::SoundPlayControl("sound_player_roll.wav");
		NewSound.Volume(0.4f);
	}
	{
		GameEngineSoundPlayer NewSound = GameEngineSound::SoundPlayControl("sound_player_roll_real.wav");
		NewSound.Volume(0.74f);
	}

	StateTime[static_cast<int>(PlayerState::Dodge)] = 0.f;

	AnimationName_ = "Dodge_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(680.f);

}

void Player::PlaySongStart()
{
	StateTime[static_cast<int>(PlayerState::PlaySong)] = 0.f;
	bPlaySongOntShot[0] = false;
	bPlaySongOntShot[1] = false;
	bPlaySongOntShot[2] = false;

	AnimationName_ = "PlaySong_right";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_);
}

void Player::RunStart()
{
	// 런스타트 사운드
	{
		GameEngineSoundPlayer NewSound = GameEngineSound::SoundPlayControl("sound_player_prerun.wav");
		NewSound.Volume(0.35f);
	}

	StateTime[static_cast<int>(PlayerState::Run)] = 0.f;

	for (int i = 0; i < 5; ++i)
	{
		Effect_DustCloud* NewEffect = GetLevel()->CreateActor<Effect_DustCloud>((int)ORDER::Effect);
		NewEffect->SetPosition(GetPosition());
		if (CurDir_ == PlayerDir::Right)
			NewEffect->SetDir(ActorDir::Left);
		else if (CurDir_ == PlayerDir::Left)
			NewEffect->SetDir(ActorDir::Right);
	}

	AnimationName_ = "Run_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(450.f);
}

void Player::RunToIdleStart()
{
	AnimationName_ = "Run_To_Idle_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(100.f);

}

void Player::JumpStart()
{
	// 점프 이펙트
	Effect_JumpCloud* NewEffect = GetLevel()->CreateActor<Effect_JumpCloud>((int)ORDER::Effect);
	NewEffect->SetPosition(GetPosition());

	// 점프 사운드
	{
		GameEngineSoundPlayer NewSound = GameEngineSound::SoundPlayControl("sound_player_jump.wav");
		NewSound.Volume(0.65f);
	}


	SetPosition(GetPosition() + float4{0, -3});
	AnimationName_ = "Jump_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	MoveDir *= Speed_;
	MoveDir += float4::UP * JumpPower_;	// 점프 파워

	StateTime[static_cast<int>(PlayerState::Jump)] = 0.f;
	IsLongJump = false;
}

void Player::LandingStart()
{
	// 착지 이펙트
	Effect_LandCloud* NewEffect = GetLevel()->CreateActor<Effect_LandCloud>((int)ORDER::Effect);
	NewEffect->SetPosition(GetPosition());

	// 착지 사운드
	{
		GameEngineSoundPlayer NewSound = GameEngineSound::SoundPlayControl("sound_player_land.wav");
		NewSound.Volume(1.f);
	}

	AnimationName_ = "Landing_";
	PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	MoveDir = float4::ZERO;
	SetSpeed(0.f);
	AttackCount_ = 0;
}

////////////////////////////////////////
// StateUpdate
void Player::IdleUpdate()
{
	// 이동키를 누르면 IdleToRun 상태로
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::IdleToRun);
		return;
	}

	// 아래쪽에 지형이 없다면 Fall상태로
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,10 });
	int Rcolor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump && 
		Rcolor != RGB(255, 0, 0) &&
		Rcolor != RGB(0,0,0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// 충돌맵 빨간색이면 아래로 이동 가능
	if (Rcolor == RGB(255, 0, 0) &&
		true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		SetPosition(GetPosition() + float4{ 0, 2 });
	}

	// 점프키를 누르면 Jump 상태로
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ 점프 추가.
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	// 공격키를 누르면 공격상태로
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// @@@ 회피 추가.
	{
		ChangeState(PlayerState::Dodge);
		return;
	}

	if (0.5f <= GameEngineInput::GetInst()->GetTime("Fire"))	// @@@ 0.5초 이상 누를시 총알쏘기 -> 게이지 관련 추가
	{
		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());
	}

}

void Player::IdleToRunUpdate()
{
	// 애니메이션 종료후 Run 모션으로
	if (true == PlayerAnimationRenderer->IsEndAnimation())
	{
		ChangeState(PlayerState::Run);
		return;
	}

	// 이동키를 안눌렀다면 Idle 상태로
	if (false == IsMoveKey())				// 이동키를 안눌렀다면
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	// 점프키를 누르면 Jump 상태로
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ 점프 추가.
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	// 회피키를 누르면 Dodge 상태로
	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// @@@ 회피 추가.
	{
		ChangeState(PlayerState::Dodge);
		return;
	}

	// 공격
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	// 아래 지형이 없다면 Fall 상태로
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,10 });
	int Rcolor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump && 
		Rcolor != RGB(255, 0, 0) &&
		Rcolor != RGB(0,0,0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// 충돌맵 빨간색이면 아래로 이동 가능
	if (Rcolor == RGB(255, 0, 0) &&
		true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		SetPosition(GetPosition() + float4{ 0, 2 });
	}


	MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}

	MapCollisionCheckMoveGround();
}


void Player::AttackUpdate()
{
	if (true == PlayerAnimationRenderer->IsEndAnimation() &&
		PlayerAttackCollision_ != nullptr)
	{
		PlayerAttackCollision_->Death();
	}

	// 공격 끝날시 Fall 상태로
	if (true == PlayerAnimationRenderer->IsEndAnimation())
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	MapCollisionCheckMoveAir();

}
void Player::FallUpdate()
{
	// 공중에 뜬 상태일경우 중력영향을 받는다.
	// 중력 가속도에 따른 낙하 속도.
	{
		// 내포지션에서 원하는 위치의 픽셀의 색상을 구할 수 있다.
		int Color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
		Gravity_ += AccGravity_ * GameEngineTime::GetDeltaTime();
		if (RGB(0, 0, 0) == Color || RGB(255,0,0) == Color)	// 땅에 닿을 경우 
		{
			Gravity_ = 10.0f;
			MoveDir.Normal2D();
			

			ChangeState(PlayerState::Landing);	
			return;
		}
		SetMove(float4::DOWN * Gravity_ * GameEngineTime::GetDeltaTime());
	}
	

	// 공격
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * 2000.f;
		float4 TempX = { MoveDir.x,0,0 };

		if (TempX.Len2D() >= 450.f)
		{
			TempX.Range2D(450.f);
			MoveDir.x = TempX.x;
		}
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * 2000.f;
		float4 TempX = { MoveDir.x,0,0 };

		if (TempX.Len2D() >= 450.f)
		{
			TempX.Range2D(450.f);
			MoveDir.x = TempX.x;
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * 4000;
	}

	MapCollisionCheckMoveAir();

}

void Player::DodgeUpdate()
{

	// 닷지 구름 이펙트 생성
	StateTime[static_cast<int>(PlayerState::Dodge)] += GameEngineTime::GetDeltaTime();
	if (0.02f <= StateTime[static_cast<int>(PlayerState::Dodge)])
	{
		Effect_DustCloud* NewEffect = GetLevel()->CreateActor<Effect_DustCloud>((int)ORDER::Effect);
		NewEffect->SetPosition(GetPosition());
		if (CurDir_ == PlayerDir::Right)
			NewEffect->SetDir(ActorDir::Left);
		else if (CurDir_ == PlayerDir::Left)
			NewEffect->SetDir(ActorDir::Right);
		StateTime[static_cast<int>(PlayerState::Dodge)] = 0.f;
	}

	// 닷지 종료시 RunToIdle 상태로
	if (true == PlayerAnimationRenderer->IsEndAnimation())
	{
		ChangeState(PlayerState::RunToIdle);
		return;
	}



	// 점프키를 누르면 Jump 상태로
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ 점프 추가.
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	MapCollisionCheckMoveGround();

}
void Player::PlaySongUpdate()
{
	// 애니메이션이 끝나면 Idle 상태로
	if (true == PlayerAnimationRenderer->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	if (4 == PlayerAnimationRenderer->CurrentAnimation()->WorldCurrentFrame() &&
		bPlaySongOntShot[2] == false)
	{
		GameEngineSound::SoundPlayOneShot("sound_playerheadphones.wav");
		bPlaySongOntShot[2] = true;
	}

	GameEngineSoundPlayer CasetteSound = GameEngineSound::SoundPlayControl("sound_playercasette_rewind.wav");
	CasetteSound.Stop();
	// 특정 모션 카세트 테이프 감는 사운드 재생
	if (13 == PlayerAnimationRenderer->CurrentAnimation()->WorldCurrentFrame() &&
		bPlaySongOntShot[0] == false)
	{
		CasetteSound = GameEngineSound::SoundPlayControl("sound_playercasette_rewind.wav");
		bPlaySongOntShot[0] = true;
	}

	// 카세트 테이프 재생
	if (27 == PlayerAnimationRenderer->CurrentAnimation()->WorldCurrentFrame() &&
		bPlaySongOntShot[1] == false)
	{
		CasetteSound.Stop();
		GameEngineSound::SoundPlayOneShot("sound_playercasette_play.wav");
		bPlaySongOntShot[1] = true;
		static_cast<Level*>(GetLevel())->SetBgmTime(0.5f);
		static_cast<Level*>(GetLevel())->SetBgmOn(true);
	}


}
void Player::RunUpdate()
{

	StateTime[static_cast<int>(PlayerState::Run)] += GameEngineTime::GetDeltaTime();

	// 런 사운드
	if (0.35f <= StateTime[static_cast<int>(PlayerState::Run)])
	{
		GameEngineSound::SoundPlayOneShot("sound_player_running_2.wav");
		StateTime[static_cast<int>(PlayerState::Run)] = 0.f;
	}

	// 이동키를 안누르면 Idle 상태로
	if (false == IsMoveKey())
	{
		ChangeState(PlayerState::RunToIdle);
		return;
	}

	// 점프키를 누르면 Jump 상태로
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ 점프 추가.
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	// 아래쪽에 지형이 없다면 Fall상태로
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,10 });
	int Rcolor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump &&
		Rcolor != RGB(255,0,0) &&
		Rcolor != RGB(0,0,0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// 충돌맵 빨간색이면 아래로 이동 가능
	if (Rcolor == RGB(255, 0, 0) &&
		true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		SetPosition(GetPosition() + float4{ 0, 2 });
	}

	// 회피키를 누르면 Dodge 상태로
	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// @@@ 회피 추가.
	{
		ChangeState(PlayerState::Dodge);
		return;
	}

	// 공격
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}

	MapCollisionCheckMoveGround();
}

void Player::RunToIdleUpdate()
{
	// 이동키를 누르면 Run 상태로
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::IdleToRun);
		return;
	}

	// 점프키를 누르면 Jump 상태로
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ 점프 추가.
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	// 아래쪽에 지형이 없다면 Fall상태로
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,10 });
	int Rcolor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump && 
		Rcolor != RGB(255, 0, 0) &&
		Rcolor != RGB(0,0,0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// 충돌맵 빨간색이면 아래로 이동 가능
	if (Rcolor == RGB(255, 0, 0) &&
		true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		SetPosition(GetPosition() + float4{ 0, 2 });
	}

	// 회피키를 누르면 Dodge 상태로
	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// @@@ 회피 추가.
	{
		ChangeState(PlayerState::Dodge);
		return;
	}

	// 공격
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}


	// 이동키를 안누르고, 애니메이션이 끝까지 재생되면 Idle 상태로
	if (false == IsMoveKey() && 
		true == PlayerAnimationRenderer->IsEndAnimation())				
	{
		ChangeState(PlayerState::Idle);
		return;
	}
	else if (false == IsMoveKey() &&
		false == PlayerAnimationRenderer->IsEndAnimation())
	{
		float4 MoveDir = float4::ZERO;

		if (CurDir_ == PlayerDir::Left)
		{
			MoveDir = float4::LEFT;
		}

		else if (CurDir_ == PlayerDir::Right)
		{
			MoveDir = float4::RIGHT;
		}

		MapCollisionCheckMoveGround();
	}

	// 멈추는중에 다시 이동키를 누르면
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::IdleToRun);
		return;
	}

}

void Player::JumpUpdate()
{
	StateTime[static_cast<int>(PlayerState::Jump)] += GameEngineTime::GetDeltaTime();
	if (StateTime[static_cast<int>(PlayerState::Jump)] > 0.f &&
		StateTime[static_cast<int>(PlayerState::Jump)] <= 0.15f &&
		true == GameEngineInput::GetInst()->IsPress("Jump"))
	{
		MoveDir += float4::UP * GameEngineTime::GetDeltaTime() * LongJumpPower_;
	}



	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * 1500.f;

	float4 TempY = { 0,MoveDir.y,0 };

	if (30.0f >= TempY.Len2D())
	{
		MoveDir.y = 0;
		//MoveDir.Normal2D();
		ChangeState(PlayerState::Fall);
		return;
	}

	// 공격
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		ChangeState(PlayerState::Fall);
		return;
	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * 2000.f;
		float4 TempX = { MoveDir.x,0,0 };

		if (TempX.Len2D() >= 450.f)
		{
			TempX.Range2D(450.f);
			MoveDir.x = TempX.x;
		}
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * 2000.f;
		float4 TempX = { MoveDir.x,0,0 };

		if (TempX.Len2D() >= 450.f)
		{
			TempX.Range2D(450.f);
			MoveDir.x = TempX.x;
		}
	}

	// 검은 땅에 닿을 경우 
	int Color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (RGB(0, 0, 0) == Color)
	{
		Gravity_ = 10.0f;
		MoveDir.Normal2D();

		Effect_LandCloud* NewEffect = GetLevel()->CreateActor<Effect_LandCloud>((int)ORDER::UI);
		NewEffect->SetPosition(GetPosition());

		ChangeState(PlayerState::Landing);
		return;
	}


	MapCollisionCheckMoveAir();

}

void Player::LandingUpdate()
{
	if (true == PlayerAnimationRenderer->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	// 이동키를 누르면 IdleToRun 상태로
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::IdleToRun);
		return;
	}

	//// 아래쪽에 지형이 없다면 Fall상태로
	int color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,10 });
	int Rcolor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
	if (color != RGB(0, 0, 0) && CurState_ != PlayerState::Jump &&
		Rcolor != RGB(255, 0, 0) &&
		Rcolor != RGB(0, 0, 0))
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	// 회피키를 누르면 Dodge 상태로
	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// @@@ 회피 추가.
	{
		ChangeState(PlayerState::Dodge);
		return;
	}

	// 공격
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}


	// 충돌맵 빨간색이면 아래로 이동 가능
	if (Rcolor == RGB(255, 0, 0) &&
		true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		SetPosition(GetPosition() + float4{ 0, 2 });
	}

	// 점프키를 누르면 Jump 상태로
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ 점프 추가.
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

}

void Player::OnGroundUpdate()
{



}

void Player::MapCollisionCheckMoveGround()
{
	{
		// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
		float4 NextPos = GetPosition() + (float4{ 0,MoveDir.y } *GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,0 };	// 미래 위치의 발기준 색상
		float4 CheckPosTopRight = NextPos + float4{ 18,-80 };	// 미래 위치의 머리기준 색상
		float4 CheckPosTopLeft = NextPos + float4{ -18,-80 };	// 미래 위치의 머리기준 색상

		int Color = MapColImage_->GetImagePixel(CheckPos);
		int TopRightColor = MapColImage_->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = MapColImage_->GetImagePixel(CheckPosTopLeft);



		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			SetMove(float4{ 0,MoveDir.y } *GameEngineTime::GetDeltaTime() * Speed_);
		}
	}

	{
		// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
		float4 NextPos = GetPosition() + (float4{ MoveDir.x,0 } *GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,0 };	// 미래 위치의 발기준 색상
		float4 CheckPosTopRight = NextPos + float4{ 18,-80 };	// 미래 위치의 머리기준 색상
		float4 CheckPosTopLeft = NextPos + float4{ -18,-80 };	// 미래 위치의 머리기준 색상
		float4 ForDownPos = GetPosition() + float4{0,1.f};	// 미래 위치의 머리기준 색상

		int CurColor = MapColImage_->GetImagePixel(GetPosition());
		int ForDownColor = MapColImage_->GetImagePixel(ForDownPos);
		int Color = MapColImage_->GetImagePixel(CheckPos);
		int TopRightColor = MapColImage_->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = MapColImage_->GetImagePixel(CheckPosTopLeft);


		// 항상 땅에 붙어있기
		if (RGB(0, 0, 0) != ForDownColor && RGB(255,0,0) != ForDownColor)
		{
			SetMove(float4{ 0, 1.0f });
		}

		// 계단 올라가기
		while (RGB(0, 0, 0) == Color &&
			TopRightColor != RGB(0, 0, 0) && TopLeftColor != RGB(0, 0, 0))
		{
			CheckPos.y -= 1.0f;
			Color = MapColImage_->GetImagePixel(CheckPos);
			SetMove(float4{ 0, -1.0f });
		}


		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			SetMove(float4{ MoveDir.x,0 } *GameEngineTime::GetDeltaTime() * Speed_);
		}

	}

}

void Player::MapCollisionCheckMoveAir()
{

	{
		// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
		float4 NextPos = GetPosition() + (float4{ 0,MoveDir.y } *GameEngineTime::GetDeltaTime());
		float4 CheckPos = NextPos + float4{ 0,0 };	// 미래 위치의 발기준 색상
		float4 CheckPosTopRight = NextPos + float4{ 18,-80 };	// 미래 위치의 머리기준 색상
		float4 CheckPosTopLeft = NextPos + float4{ -18,-80 };	// 미래 위치의 머리기준 색상

		int Color = MapColImage_->GetImagePixel(CheckPos);
		int TopRightColor = MapColImage_->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = MapColImage_->GetImagePixel(CheckPosTopLeft);


		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			SetMove(float4{ 0,MoveDir.y } *GameEngineTime::GetDeltaTime());
		}
	}

	{
		// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
		float4 NextPos = GetPosition() + (float4{ MoveDir.x,0 } *GameEngineTime::GetDeltaTime());
		float4 CheckPos = NextPos + float4{ 0,0 };	// 미래 위치의 발기준 색상
		float4 CheckPosTopRight = NextPos + float4{ 18,-80 };	// 미래 위치의 머리기준 색상
		float4 CheckPosTopLeft = NextPos + float4{ -18,-80 };	// 미래 위치의 머리기준 색상

		int Color = MapColImage_->GetImagePixel(CheckPos);
		int TopRightColor = MapColImage_->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = MapColImage_->GetImagePixel(CheckPosTopLeft);

		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			SetMove(float4{ MoveDir.x,0 } *GameEngineTime::GetDeltaTime());
		}
	}
}

