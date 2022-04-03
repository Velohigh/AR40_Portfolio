#include "GameEngineCollision.h"
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>

// �Լ� ������
// ��ȯŸ�� �����̸� �Ű�����
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

// ���� �Լ������Ϳ� RectToRect �ּҸ� �ڵ����� �־��ֱ� ����
// Ŭ������ ����� �����ڿ��� ȣ���ϰ� �صд�.
class CollisionInit
{
public:
	CollisionInit()
	{
		CollisionCheckArray[static_cast<int>(CollisionType::Rect)][static_cast<int>(CollisionType::Rect)] = RectToRect;
	}
};
// ���� ���� �̹Ƿ�, ���α׷� ����� ������ ������ ����ǰ�, �ڵ����� �����ڸ� �����ϰ� �ȴ�.
CollisionInit InitInst = CollisionInit();



GameEngineCollision::GameEngineCollision()
	: Pivot_(float4::ZERO),
	Scale_(float4::ZERO)
{
	// �ݸ��� ������ �⺻�� RectToRect�Լ��� �Լ������Ϳ� �����Ѵ�.
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
		// MsgBoxAssert("�������� �ʴ� �浹 �׷�� �浹�Ϸ��� �߽��ϴ�.");

		return false;
	}

	if (nullptr == CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)])
	{
		MsgBoxAssert("ó���� �� ���� �浹üũ �����Դϴ�.");
		return false;
	}

	// ������ ��� �ִ� list<�ݸ����׷�>�� �޾ƿ´�.
	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;

	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))	// *StartIter�� Collision�̴�.
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
		// MsgBoxAssert("�������� �ʴ� �浹 �׷�� �浹�Ϸ��� �߽��ϴ�.");

		return false;
	}

	if (nullptr == CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)])
	{
		MsgBoxAssert("ó���� �� ���� �浹üũ �����Դϴ�.");
		return false;
	}

	// ������ ��� �ִ� list<�ݸ����׷�>�� �޾ƿ´�.
	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;

	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))	// *StartIter�� Collision�̴�.
		{
			_ColResult.push_back(*StartIter);
		}
	}

	// ó�� ���Ë� size �� ���ؼ� �޶������� �߰��ߴٴ� �ǹ��̹Ƿ� True ����, �״�ζ�� false ����
	return StartSize != _ColResult.size();
}
