#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "BackGround.h"
#include <GameEngineBase/GameEngineInput.h>
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>
#include "Define.h"
#include "TitleAnimation.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	// Actor를 만들자!
	BackGround* Back = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Back->GetRenderer()->SetImage("TitleBackGround.bmp");	// 파일 이름

	TitleAnimation* TitleAnimationActor = CreateActor<TitleAnimation>((int)ORDER::UI);






}

void TitleLevel::Update()
{
	// 레벨 체인지
	if (true == GameEngineInput::GetInst()->IsDown("Stage1"))
	{
	GameEngine::GetInst().ChangeLevel("Stage1");
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Stage2"))
	{
		GameEngine::GetInst().ChangeLevel("Stage2");
	}

}

void TitleLevel::LevelChangeStart()
{
	BgmPlayer = GameEngineSound::SoundPlayControl("song_rainonbrick.ogg", 9999);
	RainSound = GameEngineSound::SoundPlayControl("sound_ambience_rain_title_01.wav", 9999);
	RainSound.Volume(0.4f);
	
	

}

void TitleLevel::LevelChangeEnd()
{
	BgmPlayer.Stop();
	RainSound.Stop();
}

