#include <Windows.h>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/KatanaZero.h>

// 속성-링커-시스템-하위시스템 설정 Window 로 설정할시, 진입점은 WinMain이 된다.
int __stdcall WinMain(_In_ HINSTANCE hInstance,     // hInstance       == 프로그램의 핸들
    _In_opt_ HINSTANCE hPrevInstance,               // hPrevInstance   == 바로 앞에 실행된 현재 프로그램의 hInstance, 사용하지 않는다.
    _In_ char*    lpCmdLine,                        // 명령행으로 입력된 프로그램 인수, 도스의 argv인수에 해당한다. 요즘엔 사용 안한다.
    _In_ int       nCmdShow)                        // nCmdShow        == 프로그램이 실행될 형태, 사용 안한다.
{
    // 헤더만 추가시 GameEngineBase의 cpp까지 알길이 없다. 따라서 참조로 추가 해준다.
    // 프로젝트 하단 참조 우클릭-참조 추가-GameEngineBase 체크-확인

    GameEngine::Start<KatanaZero>();
}

