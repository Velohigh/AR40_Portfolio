#include "GameEngineWindow.h"
#include "GameEngineDebug.h"

// 메시지 처리 함수란 메시지가 발생할 때 프로그램의 반응을 처리하는 일을 한다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        GameEngineWindow::GetInst().Off();
        return DefWindowProc(hWnd, message, wParam, lParam);
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // 여기에 hdc를 사용하는 그리기 코드를 추가
        EndPaint(hWnd, &ps);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    default:
        break;
    }

    // 위에서 따로 정의하지 않은 윈도우 메세지에 대해 기본 값으로 처리하겠다! 는뜻.
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// 싱글톤 구현
GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

// 생성자
GameEngineWindow::GameEngineWindow()
    : hInst_(nullptr)
    , hWnd_(nullptr)
    , WindowOn_(true)
    , HDC_(nullptr)
{
}

// 소멸자
GameEngineWindow::~GameEngineWindow() 
{
    if (nullptr != HDC_)
    {
        ReleaseDC(hWnd_, HDC_);
        HDC_ = nullptr;
    }

    if (nullptr != hWnd_)
    {
        DestroyWindow(hWnd_);
        hWnd_ = nullptr;
    }

}

void GameEngineWindow::Off()
{
    WindowOn_ = false;
}

void GameEngineWindow::RegClass(HINSTANCE _hInst)
{

    // 윈도우 클래스 등록
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;             // 메시지 처리함수.
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;                // 이 윈도우 클래스를 사용하는 프로그램의 번호
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowClass";
    wcex.hIconSm = nullptr;
    RegisterClassExA(&wcex);                // 윈도우 클래스를 정의한 후 RegisterClass 함수를 호출하여 윈도우 클래스를 등록한다.
}

// 윈도우 클래스를 만들고 세부 설정들을 정한다.
// 윈도우를 만드려면 윈도우 클래스를 먼저 등록한 후 CreateWindow 함수를 호출해야 한다.
void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string& _Title)
{
    // 핸들 인스턴스에 값이 있는경우.
    // 즉, 이미 만든적이 있을 경우, 다시 만들지 않는다.
    if (nullptr != hInst_)
    {
        MsgBoxAssert("윈도우를 두번 띄우려고 했습니다.");
        return;
    }

    Title_ = _Title;
    hInst_ = _hInst;
    RegClass(_hInst);

    // 윈도우를 만들면서 핸들 윈도우 값을 구한다..
    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", "packman", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    // 화면에 무언가를 그리기 위한 핸들
    HDC_ = GetDC(hWnd_);

    if (!hWnd_)
    {
        return;
    }
}

// 만든 윈도우를 화면에 띄운다.
void GameEngineWindow::ShowGameWindow() 
{
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("메인 윈도우가 만들어지지 않았습니다. 화면에 출력할 수 없습니다.");
        return;
    }

    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}

void GameEngineWindow::MessageLoop(void(*_LoopFunction)())
{
    MSG msg;

    while (WindowOn_)
    {
        if (PeekMessage(&msg, hWnd_, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // 함수 포인터가 nullptr일 경우 다시 반복
        if (nullptr == _LoopFunction)
        {
            continue;
        }

        // 함수포인터가 받아온 함수 실행
        _LoopFunction();
    }
}