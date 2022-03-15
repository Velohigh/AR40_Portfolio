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
		// map의 value에 들어있는 list의 begin을 가리키는 iterator
		auto listiter = Groupiter->second.begin();

		for (; listiter != Groupiter->second.end(); ++listiter)
		{
			if (nullptr == (*listiter))	// null이면 지울 필요가없다.
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
		// map의 value에 들어있는 list의 begin을 가리키는 iterator
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
		// map의 value에 들어있는 list의 begin을 가리키는 iterator
		auto listiter = Groupiter->second.begin();

		for (; listiter != Groupiter->second.end(); ++listiter)
		{
			(*listiter)->Render();
		}
	}
}
