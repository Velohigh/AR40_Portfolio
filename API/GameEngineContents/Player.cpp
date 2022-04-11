#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서
#include "Bullet.h"						// 총알을 만들고 싶다.
#include <GameEngineContents/ContentsEnums.h>
#include "Mouse.h"

Player::Player()
	: CurState_(PlayerState::END), CurDir_(PlayerDir::END), MapColImage_(nullptr), PlayerCollision_(nullptr),
	PlayerAnimationRenderer(nullptr)
{
}

Player::~Player() 
{
}

void Player::ChangeState(PlayerState _State)
{
	if (_State != CurState_)	// 상태가 바뀔때 한번만 실행시켜준다.
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::IdleToRun:
			IdleToRunStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::RunToIdle:
			RunToIdleStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Landing:
			LandingStart();
			break;
		case PlayerState::Attack:
			AttackStart();
			break;
		case PlayerState::Fall:
			FallStart();
			break;
		case PlayerState::Dodge:
			DodgeStart();
			break;
		case PlayerState::END:
			break;
		default:
			break;
		}
	}
	CurState_ = _State;
}

void Player::PlayerStateUpdate()
{
	switch (CurState_)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::IdleToRun:
		IdleToRunUpdate();
		break;
	case PlayerState::Run:
		RunUpdate();
		break;
	case PlayerState::RunToIdle:
		RunToIdleUpdate();
		break;
	case PlayerState::Jump:
		JumpUpdate();
		break;
	case PlayerState::Landing:
		LandingUpdate();
		break;
	case PlayerState::Attack:
		AttackUpdate();
		break;
	case PlayerState::Fall:
		FallUpdate();
		break;
	case PlayerState::Dodge:
		DodgeUpdate();
		break;
	case PlayerState::END:
		break;
	default:
		break;
	}

}


void Player::Start()
{
	SetScale({ 36,70 });		// Actor 크기

	// 플레이어 히트박스 콜리전을 만든다.
	PlayerCollision_ = CreateCollision("PlayerHitBox", { 36,70 }, { 0,-35 });

	PlayerAnimationRenderer = CreateRenderer();
	//// Render->SetIndex(0, {72, 70});	// 큰이미지 한장에 담긴 애니메이션중 10번째 이미지를, 특정 크기로 출력

	//// 애니메이션을 하나라도 만들면 애니메이션도 재생된다.
	//PlayerAnimationRenderer->CreateAnimation("idle_Right.bmp", "Idle_Right", 0, 10, 0.1f, true);
	//PlayerAnimationRenderer->CreateAnimation("idle_Left.bmp", "Idle_Left", 0, 10, 0.1f, true);
	
	PlayerAnimationRenderer->CreateFolderAnimation("spr_idle_left", "Idle_Left", 0, 10, 0.1f, true);
	PlayerAnimationRenderer->CreateFolderAnimation("spr_idle_right", "Idle_Right", 0, 10, 0.1f, true);

	PlayerAnimationRenderer->CreateFolderAnimation("spr_idle_to_run_left", "Idle_To_Run_Left", 0, 3, 0.04f, true);
	PlayerAnimationRenderer->CreateFolderAnimation("spr_idle_to_run_right", "Idle_To_Run_Right", 0, 3, 0.04f, true);

	PlayerAnimationRenderer->CreateFolderAnimation("spr_run_left", "Run_Left", 0, 9, 0.07f, true);
	PlayerAnimationRenderer->CreateFolderAnimation("spr_run_right", "Run_Right", 0, 9, 0.07f, true);

	PlayerAnimationRenderer->CreateFolderAnimation("spr_run_to_idle_left", "Run_To_Idle_Left", 0, 4, 0.07f, true);
	PlayerAnimationRenderer->CreateFolderAnimation("spr_run_to_idle_right", "Run_To_Idle_Right", 0, 4, 0.07f, true);

	PlayerAnimationRenderer->CreateFolderAnimation("spr_jump_left", "Jump_Left", 0, 3, 0.07f, true);
	PlayerAnimationRenderer->CreateFolderAnimation("spr_jump_right", "Jump_Right", 0, 3, 0.07f, true);

	PlayerAnimationRenderer->CreateFolderAnimation("spr_fall_left", "Fall_Left", 0, 3, 0.07f, true);
	PlayerAnimationRenderer->CreateFolderAnimation("spr_fall_right", "Fall_Right", 0, 3, 0.07f, true);

	PlayerAnimationRenderer->CreateFolderAnimation("spr_attack_left", "Attack_Left", 0, 6, 0.028f, true);
	PlayerAnimationRenderer->CreateFolderAnimation("spr_attack_right", "Attack_Right", 0, 6, 0.028f, true);

	PlayerAnimationRenderer->CreateFolderAnimation("spr_landing_left", "Landing_Left", 0, 4, 0.06f, true);
	PlayerAnimationRenderer->CreateFolderAnimation("spr_landing_right", "Landing_Right", 0, 4, 0.06f, true);

	PlayerAnimationRenderer->CreateFolderAnimation("spr_roll_left", "Dodge_Left", 0, 6, 0.045f, true);
	PlayerAnimationRenderer->CreateFolderAnimation("spr_roll_right", "Dodge_Right", 0, 6, 0.045f, true);


	PlayerAnimationRenderer->ChangeAnimation("Idle_Right");
	PlayerAnimationRenderer->SetTransColor(RGB(255, 255, 255));	// 이미지에서 제외할 색


	AnimationName_ = "Idle_";
	CurState_ = PlayerState::Idle;
	CurDir_ = PlayerDir::Right;

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Jump", VK_SPACE);	//virtual key (윈도우 키)
		GameEngineInput::GetInst()->CreateKey("Dodge", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("Attack", VK_LBUTTON);	// VK_LBUTTON 마우스 좌클릭

		GameEngineInput::GetInst()->CreateKey("Fire", 'Q');
		GameEngineInput::GetInst()->CreateKey("DebugRender", VK_F1);


	}

	PlayerAnimationRenderer->SetPivotType(RenderPivot::BOT);

	// 픽셀충돌용 이미지, GetPixel로 충돌이미지의 색상에 따른 이벤트 구현가능.
	MapColImage_ = GameEngineImageManager::GetInst()->Find("room_factory_2_ColMap.bmp");
	
	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}

	{	// 마우스 액터
		Mouse_ = GetLevel()->CreateActor<Mouse>((int)ORDER::UI);
	}
}

void Player::Update()
{


	// 공통 함수
	// State 업데이트만 돌아가야한다.
	DirAnimationCheck();
	PlayerStateUpdate();


	// 카메라 위치는 항상 플레이어 Pos - 화면 크기 Half
	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetScale().Half());

	// 배경화면 끝까지 이동시 카메라 위치 Lock 걸기
	CameraLock();

}

void Player::Render()
{
	// 디버그용
	if (GetAsyncKeyState(VK_F1))	
	{
		DebugRectRender();
	}

	TCHAR szBuff[64] = "";
	TCHAR StateBuff[64] = {};

	{
		if (CurState_ == PlayerState::Idle)
			sprintf_s(StateBuff, "STATE : Idle");
		else if (CurState_ == PlayerState::Jump)
			sprintf_s(StateBuff, "STATE : Jump");
		else if (CurState_ == PlayerState::Landing)
			sprintf_s(StateBuff, "STATE : Landing");
		else if (CurState_ == PlayerState::IdleToRun)
			sprintf_s(StateBuff, "STATE : IdleToRun");
		else if (CurState_ == PlayerState::Run)
			sprintf_s(StateBuff, "STATE : Run");
		else if (CurState_ == PlayerState::RunToIdle)
			sprintf_s(StateBuff, "STATE : RunToIdle");
		else if (CurState_ == PlayerState::Attack)
			sprintf_s(StateBuff, "STATE : Attack");
		else if (CurState_ == PlayerState::Dodge)
			sprintf_s(StateBuff, "STATE : Dodge");
		else if (CurState_ == PlayerState::Fall)
			sprintf_s(StateBuff, "STATE : Fall");
	}

	sprintf_s(szBuff, "Player X: %d, Y: %d", GetPosition().ix(), GetPosition().iy());
	TextOut(GameEngine::GetInst().BackBufferDC(), GetCameraEffectPosition().ix(), GetCameraEffectPosition().iy() - 120, szBuff, static_cast<int>(strlen(szBuff)));
	TextOut(GameEngine::GetInst().BackBufferDC(), GetCameraEffectPosition().ix(), GetCameraEffectPosition().iy() - 100, StateBuff, static_cast<int>(strlen(StateBuff)));

	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("이미지 못찾음");
	//}

	//// 백버퍼에 이미지를 복사한다.
	//GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());

}


void Player::CameraLock()
{
	float MapSizeX = 1800;
	float MapSizeY = 784;
	float CameraRectX = 1280;
	float CameraRectY = 720;

	if (0 > GetLevel()->GetCameraPos().x)	// 카메라 x위치가 0보다 작아지면 카메라 좌표를 0으로 고정시킨다.
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.x = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (0 > GetLevel()->GetCameraPos().y)		// 카메라 y위치가 0보다 작아지면
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (MapSizeX < GetLevel()->GetCameraPos().x + CameraRectX)		// 카메라 x위치가 맵 크기보다 커지면
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.x = MapSizeX - CameraRectX;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (MapSizeY < GetLevel()->GetCameraPos().y + CameraRectY)		// 카메라 y위치가 맵 크기보다 커지면
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = MapSizeY - CameraRectY;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

}

void Player::CollisionDeathCheck()
{
	// 충돌체 체크 후 콜리전 사망처리
	// ex. 벽과 충돌시 벽 콜리전 삭제
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerCollision_->CollisionResult("Wall", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->Death();
		}
	}
}

void Player::CollisionCheck()
{
	// 문과 충돌했다면
	if (true == PlayerCollision_->CollisionCheck("Door", CollisionType::Rect, CollisionType::Rect))
	{
		GameEngine::GetInst().ChangeLevel("Stage2");
	}
}

// 아무키도 눌리지 않았다면 false
// 아무키든 눌렸다면 true
bool Player::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		return false;
	}
	return true;
}

void Player::DirAnimationCheck()
{
	PlayerDir CheckDir_ = CurDir_;

	if (CurDir_ == PlayerDir::Right)
	{
		ChangeDirText = "Right";
	}
	else if (CurDir_ == PlayerDir::Left)
	{
		ChangeDirText = "Left";
	}

	if (CurState_ != PlayerState::Attack && CurState_ != PlayerState::Dodge)
	{

		if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
		{
			CheckDir_ = PlayerDir::Right;
			ChangeDirText = "Right";
		}

		else if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
		{
			CheckDir_ = PlayerDir::Left;
			ChangeDirText = "Left";
		}

		if (CheckDir_ != CurDir_)
		{
			PlayerAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
			CurDir_ = CheckDir_;
		}
	}

}

