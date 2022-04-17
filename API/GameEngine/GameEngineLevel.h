#pragma once
#include <list>
#include <map>
#include <vector>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>


class GameEngineActor;
struct ChangeOrderItem
{
	GameEngineActor* TargetObject;	// 이녀석의 Order를
	int ChangeOrder;				// 이렇게 바꿔라
};

// 설명 :
class GameEngine;
class GameEngineActor;
class GameEngineCollision;
class GameEngineRenderer;
class Level;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
	friend GameEngineActor;
	friend GameEngineCollision;
	friend GameEngineRenderer;
	friend Level;	// UserCustom

public:
	// constrcuter destructer
	GameEngineLevel();

	// 면접때 물어보면 알아야 합니다.
	// 이건 정말 중요하기 때문
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	// Actor는 Level 에서 만들고 관리한다!
	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0, const std::string& _Name = "")
	{
		ActorType* NewActor = new ActorType();
		GameEngineActor* StartActor = NewActor;	// friend인 EngineActor로 업캐스팅하여 Start()를 호출한다.
		NewActor->GameEngineUpdateObject::SetOrder(_Order);
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);	// 객체를 만들어주는 레벨(씬)을 넣어준다.
		StartActor->Start();		// 객체가 생성될때 딱 한번 호출됨.

		// 키가 있는지 찾아보고, 없으면 만들어준다. Find, insert 기능을 동시에 한다는 뜻.
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);
		
		return NewActor;
	}

	inline float4 GetCameraPos()
	{
		return CameraPos_;
	}

	inline void MoveCameraPos(const float4& _Value)
	{
		CameraPos_ += _Value;
	}

	inline void SetCameraPos(const float4& _Value)
	{
		CameraPos_ = _Value;
	}

	template<typename ConvertType>
	ConvertType* FindActor(const std::string& _Name)
	{
		return dynamic_cast<ConvertType*>(FindActor(_Name));
	}

	GameEngineActor* FindActor(const std::string& _Name);

	void RegistActor(const std::string& _Name, GameEngineActor* _Actor);

protected:
	// 시점함수
	// 만들어지면서 리소스나 액터를 만들때 써라
	virtual void Loading() = 0;
	// 이 레벨이 현재 레벨일때 해야할일을 실행한다.
	virtual void Update() = 0;
	// 액터수준에서 레벨이 시작할때 실행하는 함수
	void ActorLevelChangeStart();
	// Current레벨 => Next레벨로 이전할때 현재레벨이 실행하는 함수.
	virtual void LevelChangeStart() = 0;
	// 액터수준에서 레벨이 끝날때 실행하는 함수
	void ActorLevelChangeEnd();
	// Current레벨 => Next레벨로 이전할때 이전레벨이 실행하는 함수.
	virtual void LevelChangeEnd() = 0;


private:
	// std::vector로 관리하는게 더 좋다고 생각합니다.
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	// 사용자가 직접 레벨에 등록시킨 액터들
	std::map<std::string, GameEngineActor*> RegistActor_;

	std::vector<ChangeOrderItem> ChangeOrderList;

	float4 CameraPos_;

	void ActorUpdate();
	void ActorRender();
	void CollisionDebugRender();
	void ActorRelease();

private:
	std::map<int, std::list<GameEngineRenderer*>> AllRenderer_;
	void AddRenderer(GameEngineRenderer* _Renderer);
	
	void ChangeUpdateOrder(GameEngineActor* _Actor, int _NewOrder);

	void ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder);


public:


private:
	// Collision
	// 삭제는 액터가 하지만, 실제 사용은 Level
	// 여기서 함부로 GameEngineCollision*을 delete 하는 일이 있으면 안된다.
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName,GameEngineCollision* _Collision);

};

