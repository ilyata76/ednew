#include <windows.h>

#define ID_BUTTON_1 3000
#define ID_MENU_1_1 1001
#define ID_MENU_1_2 1002


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// CALLBACK - ��� ������ ������� ��� �������������� ������ (�������� ���� ��� ��������)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hMainWnd; // ������� ���������� �������� ����
	WNDCLASSEX wc; // ��� ���� - ����� ����

	////////////////// ��������� ����� wc /////////////////
	TCHAR Mainclass[] = L"MYCLASS";
	wc.cbSize = sizeof(wc);                                         // ������ ��������� (� ������)
	wc.style = CS_HREDRAW | CS_VREDRAW;                             // ����� ������ ������
	wc.lpfnWndProc = WndProc;                                       // ��������� �� ������� ��������� (����������������)
	wc.lpszMenuName = NULL;                                     // ��������� �� ��� ���� (�������� ��������� ���� - ��� ����) 
	wc.lpszClassName = Mainclass;                                   // ����� ��� �����������
	wc.cbWndExtra = NULL;                                       // ����� ������������� ������ � ����� ���������
	wc.cbClsExtra = NULL;                                       // ����� ������������� ������ ��� �������� ���������� ����������
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);                         // ��������� ����������� (��������)
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);                       // ���������� ��������� ����������� (� ����)
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);                       // ���������� �������
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);     // ���������� ����� ��� �������� ���� ����
	wc.hInstance = hInstance;                                   // ��������� �� ������, ���������� ��� ����, ������������ ��� ������

	///////////////////////////////////////////////////////

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"�� ���������� ���������������� MYCLASS!", L"������", MB_OK); return NULL;
	}

	///////////////////////////////////////////////////////

	HMENU hMenu = CreateMenu();
	HMENU hPopMenuFile = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hPopMenuFile, L"���");
	AppendMenu(hPopMenuFile, MF_STRING | MF_CHECKED, ID_MENU_1_1, L"�������!");
	AppendMenu(hPopMenuFile, MF_SEPARATOR, 0, L"");
	AppendMenu(hPopMenuFile, MF_STRING, ID_MENU_1_2, L"�������");
	///////////////////////////////////////////////////////


	hMainWnd = CreateWindow(
		Mainclass,                                      // ��� ������
		L"����������� ������� ���������",               // ��� ����
		WS_OVERLAPPEDWINDOW,               // ������ ����������� ������
		1,                                  // ������� ������ �� ��� �
		1,                                           // ������� ������ �� ��� � (��� ������ � �, �� ������ �� �����)
		380,                                  // ������ ������
		170,				                               // ������ ������ (��� ������ � ������, �� ������ �� �����)
		(HWND)NULL,                                     // ���������� ������������� ����
		hMenu,                                                   // ���������� ����
		HINSTANCE(hInstance),                           // ���������� ���������� ����������
		NULL                                                    // ������ �� ������� �� WndProc
	);



	///////////////////////////////////////////////////////

	if (!hMainWnd) {
		MessageBox(NULL, L"�� ���������� ������� ����!", L"������", MB_OK); return NULL;
	}

	///////////////////////////////////////////////////////

	HWND hbutton;
	hbutton = CreateWindow(L"BUTTON", L"��������", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		70, 45, 240, 20, hMainWnd, HMENU(ID_BUTTON_1), hInstance, NULL
	);

	if (!hbutton) {
		MessageBox(NULL, L"�� ���������� ������� ���������!", L"������", MB_OK | MB_ICONSTOP); return NULL;
	}

	///////////////////////////////////////////////////////

	MSG msg;    // ��� ��������� ��������� �� ��

	ShowWindow(hMainWnd, nCmdShow);             // ���������� ����
	UpdateWindow(hMainWnd);                     // ��������� ����

	while (GetMessage(&msg, NULL, NULL, NULL)) {      // ��������� ��������� �� �������, ���������� ��-�����, ��
		TranslateMessage(&msg);                       // �������������� ���������
		DispatchMessage(&msg);                        // ������� ��������� ������� ��
	}
	return msg.wParam; // ���������� ��� ������ �� ����������
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)    // ������� ������������ ��������, ���������� ��
{
	HDC hDC; // ������ ���������� ���������� ������ �� ������

	TCHAR mainMessage[] = L"��������, ��������!"; // ������ � ����������
	COLORREF colormainMessage = RGB(74, 38, 44); // ����� ���� ������

	PAINTSTRUCT ps; // ���������, ���-��� ���������� � ���������� ������� (�������, ���� � ��)
	RECT rect; // ���-��, ������������ ������ ���������� �������

	int INS = 0;
	switch (uMsg) {
	case WM_PAINT: // ���� ����� ����������, ��:
		hDC = BeginPaint(hWnd, &ps); // �������������� �������� ����������
		GetClientRect(hWnd, &rect); // �������� ������ � ������ ������� ��� ���������

		rect.left = 120;				// X
		rect.top = 10;				// Y
		rect.right = 120 + 200;			// X + ������
		rect.bottom = 10 + 20;			// Y + ������

		SetTextColor(hDC, colormainMessage); // ������������� ���� ������������ ����������
		DrawText(hDC, mainMessage, -1, &rect, NULL); // ������ �����
		EndPaint(hWnd, &ps); // ����������� ��������
		break;
	case WM_DESTROY: // ���� ������ ���������, ��:
		PostQuitMessage(NULL); // ���������� WinMain() ��������� WM_QUIT
		break;
	case WM_COMMAND:
		switch (wParam) {
		case ID_BUTTON_1:
			INS = MessageBox(NULL, L"��� �� ����� � -4?", L"���-�", MB_YESNOCANCEL | MB_ICONQUESTION);
			switch (INS) {
			case IDYES: MessageBox(NULL, L"��, ��������, ��", L"??", MB_OK); SetWindowText(HWND(lParam), L"�������� ��������"); break;
			case IDNO: MessageBox(NULL, L"�� �����?", L"??", MB_OK); SetWindowText(HWND(lParam), L"�������� ����������"); break;
			case IDCANCEL: SetWindowText(HWND(lParam), L"�������� ��������");
			default: break;
			}
			break;
		case ID_MENU_1_1:
			INS = MessageBox(NULL, L"� ������� �������", L"���!", MB_OK); switch (INS) {}
			break;
		case ID_MENU_1_2:
			INS = MessageBox(NULL, L"�������", L"�������������", MB_OK); switch (INS) {}
			break;
		default: MessageBox(NULL, L"���-�� ����� �� ���", L"������", MB_OK | MB_ICONSTOP); break;

		}
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return NULL;
}