#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineLevel.h> // ������ ���ؼ�
#include "Bullet.h"						// �Ѿ��� ����� �ʹ�.

Player::Player()
	: Speed_(300.0f), Gravity_(100.f), AccGravity_(0), CurState_(PlayerState::END), CurDir_(PlayerDir::END), MapColImage_(nullptr), PlayerCollision_(nullptr),
	PlayerAnimationRenderer(nullptr)
{
}

Player::~Player() 
{
}

void Player::ChangeState(PlayerState _State)
{
	if (_State != CurState_)	// ���°� �ٲ� �ѹ��� ��������ش�.
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
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
		case PlayerState::Move:
			MoveStart();
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
	case PlayerState::Attack:
		AttackUpdate();
		break;
	case PlayerState::Fall:
		FallUpdate();
		break;
	case PlayerState::Dodge:
		DodgeUpdate();
		break;
	case PlayerState::Move:
		MoveUpdate();
		break;
	case PlayerState::END:
		break;
	default:
		break;
	}

}


void Player::Start()
{
	SetScale({ 36,70 });		// Actor ũ��

	// �÷��̾� ��Ʈ�ڽ� �ݸ����� �����.
	PlayerCollision_ = CreateCollision("PlayerHitBox", { 36,70 });	// @@@ Leak �߻�, ���߿� ����

	PlayerAnimationRenderer = CreateRenderer();
	//// Render->SetIndex(0, {72, 70});	// ū�̹��� ���忡 ��� �ִϸ��̼��� 10��° �̹�����, Ư�� ũ��� ���

	// �ִϸ��̼��� �ϳ��� ����� �ִϸ��̼ǵ� ����ȴ�.
	PlayerAnimationRenderer->CreateAnimation("idle_Right.bmp", "Idle_Right", 0, 10, 0.1f, true);
	PlayerAnimationRenderer->CreateAnimation("idle_Left.bmp", "Idle_Left", 0, 10, 0.1f, true);
	PlayerAnimationRenderer->ChangeAnimation("Idle_Right");
	PlayerAnimationRenderer->SetTransColor(RGB(255,255,255));	// �̹������� ������ ��

	AnimationName_ = "Idle_";
	CurState_ = PlayerState::Idle;
	CurDir_ = PlayerDir::Right;

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Jump", VK_SPACE);	//virtual key (������ Ű)
		GameEngineInput::GetInst()->CreateKey("Dodge", VK_LSHIFT);
		// VK_LBUTTON ���콺 ��Ŭ��

		GameEngineInput::GetInst()->CreateKey("Fire", 'Q');
		GameEngineInput::GetInst()->CreateKey("DebugRender", VK_F1);


	}

}

void Player::Update()
{
	// ���� �Լ�
	// State ������Ʈ�� ���ư����Ѵ�.
	DirAnimationCheck();
	PlayerStateUpdate();

	// �ȼ��浹�� �̹���, GetPixel�� �浹�̹����� ���� ���� �̺�Ʈ ��������.
	MapColImage_ = GameEngineImageManager::GetInst()->Find("room_factory_2_ColMap.bmp");
	
	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�.");
	}

	// ī�޶� ��ġ�� �׻� �÷��̾� Pos - ȭ�� ũ�� Half
	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetScale().Half());

	// ���ȭ�� ������ �̵��� ī�޶� ��ġ Lock �ɱ�
	CameraLock();

}

void Player::Render()
{
	// ����׿�
	if (GetAsyncKeyState(VK_F1))	
	{
		DebugRectRender();
	}

	TCHAR szBuff[64] = "";
	sprintf_s(szBuff, "Player X: %d, Y: %d", GetPosition().ix(), GetPosition().iy());
	TextOut(GameEngine::GetInst().BackBufferDC(), GetCameraEffectPosition().ix(), GetCameraEffectPosition().iy() - 50, szBuff, strlen(szBuff));

	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("�̹��� ��ã��");
	//}

	//// ����ۿ� �̹����� �����Ѵ�.
	//GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());

}


void Player::CameraLock()
{
	float MapSizeX = 1800;
	float MapSizeY = 784;
	float CameraRectX = 1280;
	float CameraRectY = 720;

	if (0 > GetLevel()->GetCameraPos().x)	// ī�޶� x��ġ�� 0���� �۾����� ī�޶� ��ǥ�� 0���� ������Ų��.
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.x = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (0 > GetLevel()->GetCameraPos().y)		// ī�޶� y��ġ�� 0���� �۾�����
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (MapSizeX < GetLevel()->GetCameraPos().x + CameraRectX)		// ī�޶� x��ġ�� �� ũ�⺸�� Ŀ����
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.x = MapSizeX - CameraRectX;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (MapSizeY < GetLevel()->GetCameraPos().y + CameraRectY)		// ī�޶� y��ġ�� �� ũ�⺸�� Ŀ����
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = MapSizeY - CameraRectY;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

}

void Player::CollisionDeathCheck()
{
	// �浹ü üũ �� �ݸ��� ���ó��
	// ex. ���� �浹�� �� �ݸ��� ����
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
	// ���� �浹�ߴٸ�
	if (true == PlayerCollision_->CollisionCheck("Door", CollisionType::Rect, CollisionType::Rect))
	{
		GameEngine::GetInst().ChangeLevel("Stage2");
	}
}

// �ƹ�Ű�� ������ �ʾҴٸ� false
// �ƹ�Ű�� ���ȴٸ� true
bool Player::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsDown("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsDown("MoveRight") &&
		false == GameEngineInput::GetInst()->IsDown("MoveUp") &&
		false == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		return false;
	}
	return true;
}

void Player::DirAnimationCheck()
{
	PlayerDir CheckDir_ = CurDir_;
	std::string ChangeDirText = "Right";

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

