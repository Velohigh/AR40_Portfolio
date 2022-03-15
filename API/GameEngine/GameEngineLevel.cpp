#include "GameEngineLevel.h"
#include "GameEngineActor.h"

GameEngineLevel::GameEngineLevel() 
{
}

GameEngineLevel::~GameEngineLevel() 
{
	auto Groupiter = AllActor_.begin();

	for (; Groupiter != AllActor_.end(); ++Groupiter)
	{
		// map�� value�� ����ִ� list�� begin�� ����Ű�� iterator
		auto listiter = Groupiter->second.begin();

		for (; listiter != Groupiter->second.end(); ++listiter)
		{
			if (nullptr == (*listiter))	// null�̸� ���� �ʿ䰡����.
			{
				continue;
			}

			delete (*listiter);
			(*listiter) = nullptr;
		}
	}

}

void GameEngineLevel::ActorUpdate()
{
	auto Groupiter = AllActor_.begin();

	for (; Groupiter != AllActor_.end(); ++Groupiter)
	{
		// map�� value�� ����ִ� list�� begin�� ����Ű�� iterator
		auto listiter = Groupiter->second.begin();

		for (; listiter != Groupiter->second.end(); ++listiter)
		{
			(*listiter)->Update();
		}
	}
}

void GameEngineLevel::ActorRender()
{
	auto Groupiter = AllActor_.begin();

	for (; Groupiter != AllActor_.end(); ++Groupiter)
	{
		// map�� value�� ����ִ� list�� begin�� ����Ű�� iterator
		auto listiter = Groupiter->second.begin();

		for (; listiter != Groupiter->second.end(); ++listiter)
		{
			(*listiter)->Render();
		}
	}
}
