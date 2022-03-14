#include "KatanaZero.h"
#include "LogoLevel.h"
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
	CreateLevel<LogoLevel>("Logo");
	CreateLevel<StageLevel>("Stage");
	CreateLevel<EndingLevel>("Ending");

}

void KatanaZero::GameLoop()
{
}

void KatanaZero::GameEnd()
{
}

