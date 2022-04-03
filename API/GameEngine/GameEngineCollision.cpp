#include "GameEngineCollision.h"
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>

// 함수 포인터
// 반환타입 변수이름 매개변수
// bool (*fp[3][3])(int*, int*)
bool (*CollisionCheckArray[static_cast<int>(CollisionType::Max)][static_cast<int>(CollisionType::Max)])(GameEngineCollision*, GameEngineCollision*);

bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	if (nullptr == _Left || nullptr == _Right)
	{
		return false;
	}

	GameEngineRect LeftRc = _Left->GetRect();
	GameEngineRect RightRc = _Right->GetRect();

	return LeftRc.OverLap(RightRc);
}

// 전역 함수포인터에 RectToRect 주소를 자동으로 넣어주기 위해
// 클래스를 만들고 생성자에서 호출하게 해둔다.
class CollisionInit
{
public:
	CollisionInit()
	{
		CollisionCheckArray[static_cast<int>(CollisionType::Rect)][static_cast<int>(CollisionType::Rect)] = RectToRect;
	}
};
// 전역 변수 이므로, 프로그램 실행시 데이터 영역에 저장되고, 자동으로 생성자를 실행하게 된다.
CollisionInit InitInst = CollisionInit();



GameEngineCollision::GameEngineCollision()
	: Pivot_(float4::ZERO),
	Scale_(float4::ZERO)
{
	// 콜리전 생성시 기본값 RectToRect함수로 함수포인터에 설정한다.
}

GameEngineCollision::~GameEngineCollision()
{
}

bool GameEngineCollision::CollisionCheck(
	const std::string& _TargetGroup,
	CollisionType _This /*= CollisionType::Circle*/,
	CollisionType _Target /*= CollisionType::Rect*/)
{
	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(_TargetGroup);

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		// MsgBoxAssert("존재하지 않는 충돌 그룹과 충돌하려고 했습니다.");

		return false;
	}

	if (nullptr == CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)])
	{
		MsgBoxAssert("처리할 수 없는 충돌체크 조합입니다.");
		return false;
	}

	// 레벨이 들고 있는 list<콜리전그룹>을 받아온다.
	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;

	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))	// *StartIter는 Collision이다.
		{
			return true;
		}
	}

	return false;
}

void GameEngineCollision::DebugRender()
{
	GameEngineRect DebugRect(GetActor()->GetCameraEffectPosition() + Pivot_, Scale_);

	Rectangle(
		GameEngine::BackBufferDC(),
		DebugRect.CenterLeft(),
		DebugRect.CenterTop(),
		DebugRect.CenterRight(),
		DebugRect.CenterBot()
	);
}

bool GameEngineCollision::CollisionResult(const std::string& _TargetGroup, std::vector<GameEngineCollision*> _ColResult, CollisionType _This, CollisionType _Target)
{

	size_t StartSize = _ColResult.size();

	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(_TargetGroup);

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		// MsgBoxAssert("존재하지 않는 충돌 그룹과 충돌하려고 했습니다.");

		return false;
	}

	if (nullptr == CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)])
	{
		MsgBoxAssert("처리할 수 없는 충돌체크 조합입니다.");
		return false;
	}

	// 레벨이 들고 있는 list<콜리전그룹>을 받아온다.
	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;

	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))	// *StartIter는 Collision이다.
		{
			_ColResult.push_back(*StartIter);
		}
	}

	// 처음 들어올떄 size 와 비교해서 달라졌으면 추가했다는 의미이므로 True 리턴, 그대로라면 false 리턴
	return StartSize != _ColResult.size();
}
