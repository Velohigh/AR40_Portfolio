#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleLogo.h"
#include "BackGround.h"
#include <GameEngineBase/GameEngineInput.h>
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>
#include "Define.h"


TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	// Actor�� ������!
	BackGround* Back = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Back->GetRenderer()->SetImage("TitleBackGround.bmp");	// ���� �̸�







}

void TitleLevel::Update()
{
	// ���� ü����
	if (true == GameEngineInput::GetInst()->IsDown("Stage1"))
	{
	GameEngine::GetInst().ChangeLevel("Stage1");
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

