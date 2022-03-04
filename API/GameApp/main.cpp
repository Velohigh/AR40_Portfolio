#include <Windows.h>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

// �Ӽ�-��Ŀ-�ý���-�����ý��� ���� Window �� �����ҽ�, �������� WinMain�� �ȴ�.
int __stdcall WinMain(_In_ HINSTANCE hInstance,     // hInstance       == ���α׷��� �ڵ�
    _In_opt_ HINSTANCE hPrevInstance,               // hPrevInstance   == �ٷ� �տ� ����� ���� ���α׷��� hInstance, ������� �ʴ´�.
    _In_ char*    lpCmdLine,                        // ��������� �Էµ� ���α׷� �μ�, ������ argv�μ��� �ش��Ѵ�. ���� ��� ���Ѵ�.
    _In_ int       nCmdShow)                        // nCmdShow        == ���α׷��� ����� ����, ��� ���Ѵ�.
{
    // ����� �߰��� GameEngineBase�� cpp���� �˱��� ����. ���� ������ �߰� ���ش�.
    // ������Ʈ �ϴ� ���� ��Ŭ��-���� �߰�-GameEngineBase üũ-Ȯ��

    GameEngineDebug::LeakCheckOn();
    GameEngineWindow::GetInst().CreateGameWindow(hInstance, "GameWindow");
    GameEngineWindow::GetInst().ShowGameWindow();

    DWORD dwTime = GetTickCount64();
    while (true)
    {
        // �޼����ڽ���
        // ������ ���ư���.
        if (dwTime + 5000 < GetTickCount64())
            break;
    }

    GameEngineWindow::Destroy();

}