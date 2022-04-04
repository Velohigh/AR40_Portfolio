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

Player::Player()
	: Speed_(300.0f), Gravity_(100.f)
{
}

Player::~Player() 
{
}

// 아무키도 눌리지 않았다면 false
// 아무키든 눌렸다면 true
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

void Player::ChangeState(PlayerState _State)
{
	if (_State != CurState_)	// 상태가 바뀔때 한번만 실행시켜준다.
	{
		switch (_State)
		{
		case Idle:
			IdleStart();
			break;
		case Attack:
			AttackStart();
			break;
		case Fall:
			FallStart();
			break;
		case Dodge:
			DodgeStart();
			break;
		case Move:
			MoveStart();
			break;
		case Max:
			break;
		default:
			break;
		}
	}
	CurState_ = _State;
}

void Player::StateUpdate()
{
	switch (CurState_)
	{
	case Idle:
		IdleUpdate();
		break;
	case Attack:
		AttackUpdate();
		break;
	case Fall:
		FallUpdate();
		break;
	case Dodge:
		DodgeUpdate();
		break;
	case Move:
		MoveUpdate();
		break;
	case Max:
		break;
	default:
		break;
	}

}


void Player::Start()
{
	SetScale({ 36,70 });		// Actor 크기

	// 플레이어 히트박스 콜리전을 만든다.
	PlayerCollision_ = CreateCollision("PlayerHitBox", { 36,70 });	// @@@ Leak 발생, 나중에 수정

	//// GameEngineRenderer* Render = CreateRendererToScale("Idle.bmp", { 300, 300 });
	GameEngineRenderer* Render = CreateRenderer();
	//// Render->SetIndex(0, {72, 70});	// 큰이미지 한장에 담긴 애니메이션중 10번째 이미지를, 특정 크기로 출력

	// TransParent를 이용한 이미지 크기 조정 함수
	// CreateRendererToScale("hpbar.bmp", float4(300.0f, 20.0f), RenderPivot::CENTER, float4(0.0f, -100.0f));

	// 애니메이션을 하나라도 만들면 애니메이션도 재생된다.
	Render->CreateAnimation("idle_Right.bmp", "Idle_Right", 0, 10, 0.1f, true);
	Render->ChangeAnimation("Idle_Right");
	Render->SetTransColor(RGB(255,255,255));	// 이미지에서 제외할 색

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Jump", VK_SPACE);	//virtual key (윈도우 키)
		GameEngineInput::GetInst()->CreateKey("Dodge", VK_LSHIFT);
		// VK_LBUTTON 마우스 좌클릭

		GameEngineInput::GetInst()->CreateKey("Fire", 'Q');
		GameEngineInput::GetInst()->CreateKey("DebugRender", VK_F1);


	}

}

void Player::Update()
{
	// 공통 함수
	// State 업데이트만 돌아가야한다.
	StateUpdate();

	// 픽셀충돌용 이미지, GetPixel로 충돌이미지의 색상에 따른 이벤트 구현가능.
	MapColImage_ = GameEngineImageManager::GetInst()->Find("room_factory_2_ColMap.bmp");
	
	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}

	// 키 입력시 이벤트
	KeyCheck();

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

	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("이미지 못찾음");
	//}

	//// 백버퍼에 이미지를 복사한다.
	//GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());

}

void Player::KeyCheck()
{




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


