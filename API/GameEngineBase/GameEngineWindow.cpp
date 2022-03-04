#include "GameEngineWindow.h"
#include "GameEngineDebug.h"

// �޽��� ó�� �Լ��� �޽����� �߻��� �� ���α׷��� ������ ó���ϴ� ���� �Ѵ�.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// �̱��� ����
GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

// ������
GameEngineWindow::GameEngineWindow()
    : hInst_(nullptr)
    , hWnd_(nullptr)
{
}

// �Ҹ���
GameEngineWindow::~GameEngineWindow() 
{
}

void GameEngineWindow::RegClass(HINSTANCE _hInst)
{

    // ������ Ŭ���� ���
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;             // �޽��� ó���Լ�.
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;                // �� ������ Ŭ������ ����ϴ� ���α׷��� ��ȣ
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowClass";
    wcex.hIconSm = nullptr;
    RegisterClassExA(&wcex);                // ������ Ŭ������ ������ �� RegisterClass �Լ��� ȣ���Ͽ� ������ Ŭ������ ����Ѵ�.
}

// ������ Ŭ������ ����� ���� �������� ���Ѵ�.
// �����츦 ������� ������ Ŭ������ ���� ����� �� CreateWindow �Լ��� ȣ���ؾ� �Ѵ�.
void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string& _Title)
{
    
    // �ڵ� �ν��Ͻ��� ���� �ִ°��.
    // ��, �̹� �������� ���� ���, �ٽ� ������ �ʴ´�.
    if (nullptr != hInst_)
    {
        MsgBoxAssert("�����츦 �ι� ������ �߽��ϴ�.");
        return;
    }

    Title_ = _Title;
    hInst_ = _hInst;
    RegClass(_hInst);

    // �����츦 ����鼭 �ڵ� ������ ���� ���Ѵ�..
    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", "packman", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    if (!hWnd_)
    {
        return;
    }
}

// ���� �����츦 ȭ�鿡 ����.
void GameEngineWindow::ShowGameWindow() 
{
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("���� �����찡 ��������� �ʾҽ��ϴ�. ȭ�鿡 ����� �� �����ϴ�.");
        return;
    }

    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}