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


	//// 중력 가속도에 따른 낙하 속도.
	//{
	//	// 내포지션에서 원하는 위치의 픽셀의 색상을 구할 수 있다.
	//	int Color = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,35 });

	//	AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;
	//	if (RGB(0,0,0) == Color)
	//	{
	//		AccGravity_ = 0.0f;
	//	}
	//	SetMove(float4::DOWN * AccGravity_ * GameEngineTime::GetDeltaTime());
	//}

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
	float4 CheckPos;	// ? 안쓰는듯
	float4 MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir = float4::UP;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir = float4::DOWN;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Jump"))		// @@@ 점프 추가.
	{
	}

	if (true == GameEngineInput::GetInst()->IsDown("Dodge"))	// @@@ 회피 추가.
	{
	}

	if (0.5f <= GameEngineInput::GetInst()->GetTime("Fire"))	// @@@ 0.5초 이상 누를시 총알쏘기 -> 게이지 관련 추가
	{
		Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
		Ptr->SetPosition(GetPosition());
	}

	{
		// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4{ 0,35 };	// 미래 위치의 발기준 색상

		int Color = MapColImage_->GetImagePixel(CheckPos);

		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}

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

