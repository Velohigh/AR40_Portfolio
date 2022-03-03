#include "GameEngineWindow.h"

// �޽��� ó�� �Լ��� �޽����� �߻��� �� ���α׷��� ������ ó���ϴ� ���� �Ѵ�.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// �̱��� ����
GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

// ������
GameEngineWindow::GameEngineWindow() 
{
}

// �Ҹ���
GameEngineWindow::~GameEngineWindow() 
{
}

// ������ Ŭ������ ����� ���� �������� ���Ѵ�.
// �����츦 ������� ������ Ŭ������ ���� ����� �� CreateWindow �Լ��� ȣ���ؾ� �Ѵ�.
void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst)
{
    WNDCLASSEXW wcex;

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
    wcex.lpszClassName = L"GameEngineWindowClass";
    wcex.hIconSm = nullptr;

    RegisterClassExW(&wcex);                // ������ Ŭ������ ������ �� RegisterClass �Լ��� ȣ���Ͽ� ������ Ŭ������ ����Ѵ�.

    // �����츦 ����鼭 �ڵ� ������ ���� ���Ѵ�..
    hWnd_ = CreateWindowW(L"GameEngineWindowClass", L"packman", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    if (!hWnd_)
    {
        return;
    }
}

// ���� �����츦 ȭ�鿡 ����.
void GameEngineWindow::ShowGameWindow() 
{
    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}