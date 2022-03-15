#include "KatanaZero.h"
#include "TitleLevel.h"
#include "StageLevel.h"
#include "EndingLevel.h"

KatanaZero::KatanaZero() 
{
}

KatanaZero::~KatanaZero() 
{
}

void KatanaZero::GameInit()
{
	CreateLevel<TitleLevel>("Title");
	CreateLevel<StageLevel>("Stage");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Title");

}

void KatanaZero::GameLoop()
{
}

void KatanaZero::GameEnd()
{
}

