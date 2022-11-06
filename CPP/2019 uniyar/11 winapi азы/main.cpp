#include <windows.h>

#define ID_BUTTON_1 3000
#define ID_MENU_1_1 1001
#define ID_MENU_1_2 1002


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// CALLBACK - для вызова функции при параметризации других (передача кода как такового)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hMainWnd; // создали дескриптор главного окна
	WNDCLASSEX wc; // для окна - класс окна

	////////////////// ОПРЕДЕЛИМ КЛАСС wc /////////////////
	TCHAR Mainclass[] = L"MYCLASS";
	wc.cbSize = sizeof(wc);                                         // размер структуры (в байтах)
	wc.style = CS_HREDRAW | CS_VREDRAW;                             // стиль класса окошка
	wc.lpfnWndProc = WndProc;                                       // указатель на функцию обработок (пользовательскую)
	wc.lpszMenuName = NULL;                                     // указатель на имя меню (нынешнее заглавное окно - без меню) 
	wc.lpszClassName = Mainclass;                                   // класс для определения
	wc.cbWndExtra = NULL;                                       // число освобождаемых байтов в конце структуры
	wc.cbClsExtra = NULL;                                       // число освобождаемых байтов при создании экземпляра приложения
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);                         // декриптор пиктограммы (картинки)
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);                       // дескриптор маленькой пиктограммы (в трэе)
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);                       // дескриптор курсора
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);     // дескриптор кисти для закраски фона окна
	wc.hInstance = hInstance;                                   // указатель на строку, содержащую имя меню, применяемого для класса

	///////////////////////////////////////////////////////

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Не получилось зарегистрировать MYCLASS!", L"ОШИБКА", MB_OK); return NULL;
	}

	///////////////////////////////////////////////////////

	HMENU hMenu = CreateMenu();
	HMENU hPopMenuFile = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hPopMenuFile, L"это");
	AppendMenu(hPopMenuFile, MF_STRING | MF_CHECKED, ID_MENU_1_1, L"менюшка!");
	AppendMenu(hPopMenuFile, MF_SEPARATOR, 0, L"");
	AppendMenu(hPopMenuFile, MF_STRING, ID_MENU_1_2, L"афигеть");
	///////////////////////////////////////////////////////


	hMainWnd = CreateWindow(
		Mainclass,                                      // имя класса
		L"Полноценная оконная процедура",               // имя окна
		WS_OVERLAPPEDWINDOW,               // режимы отображения окошка
		1,                                  // позиция окошка по оси х
		1,                                           // позиция окошка по оси у (раз дефолт в х, то писать не нужно)
		380,                                  // ширина окошка
		170,				                               // высота окошка (раз дефолт в ширине, то писать не нужно)
		(HWND)NULL,                                     // дескриптор родительского окна
		hMenu,                                                   // дескриптор меню
		HINSTANCE(hInstance),                           // дескриптор экземпляра приложения
		NULL                                                    // ничего не передаём из WndProc
	);



	///////////////////////////////////////////////////////

	if (!hMainWnd) {
		MessageBox(NULL, L"Не получилось создать окно!", L"Ошибка", MB_OK); return NULL;
	}

	///////////////////////////////////////////////////////

	HWND hbutton;
	hbutton = CreateWindow(L"BUTTON", L"кнопочка", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		70, 45, 240, 20, hMainWnd, HMENU(ID_BUTTON_1), hInstance, NULL
	);

	if (!hbutton) {
		MessageBox(NULL, L"Не получилось создать кноночбку!", L"Ошибка", MB_OK | MB_ICONSTOP); return NULL;
	}

	///////////////////////////////////////////////////////

	MSG msg;    // для обработки сообщений от ОС

	ShowWindow(hMainWnd, nCmdShow);             // отображает окно
	UpdateWindow(hMainWnd);                     // обновляет окно

	while (GetMessage(&msg, NULL, NULL, NULL)) {      // извлекаем сообщения из очереди, посылаемые фу-циями, ОС
		TranslateMessage(&msg);                       // интерпретируем сообщения
		DispatchMessage(&msg);                        // передаём сообщения обратно ОС
	}
	return msg.wParam; // возвращаем код выхода из приложения
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)    // функция обрабатывает процессы, посылаемые ОС
{
	HDC hDC; // создаём дескриптор ориентации текста на экране

	TCHAR mainMessage[] = L"Смотрите, кнопочка!"; // строка с сообщением
	COLORREF colormainMessage = RGB(74, 38, 44); // задаём цвет текста

	PAINTSTRUCT ps; // структура, сод-щая информацию о клиентской области (размеры, цвет и тп)
	RECT rect; // стр-ра, определяющая размер клиентской области

	int INS = 0;
	switch (uMsg) {
	case WM_PAINT: // если нужно нарисовать, то:
		hDC = BeginPaint(hWnd, &ps); // инициализируем контекст устройства
		GetClientRect(hWnd, &rect); // получаем ширину и высоту области для рисования

		rect.left = 120;				// X
		rect.top = 10;				// Y
		rect.right = 120 + 200;			// X + ширина
		rect.bottom = 10 + 20;			// Y + высота

		SetTextColor(hDC, colormainMessage); // устанавливаем цвет контекстного устройства
		DrawText(hDC, mainMessage, -1, &rect, NULL); // рисуем текст
		EndPaint(hWnd, &ps); // заканчиваем рисовать
		break;
	case WM_DESTROY: // если окошко закрылось, то:
		PostQuitMessage(NULL); // отправляем WinMain() сообщение WM_QUIT
		break;
	case WM_COMMAND:
		switch (wParam) {
		case ID_BUTTON_1:
			INS = MessageBox(NULL, L"Был ли смысл в -4?", L"Так-с", MB_YESNOCANCEL | MB_ICONQUESTION);
			switch (INS) {
			case IDYES: MessageBox(NULL, L"Да, наверное, да", L"??", MB_OK); SetWindowText(HWND(lParam), L"кнопочка согласия"); break;
			case IDNO: MessageBox(NULL, L"Но зачем?", L"??", MB_OK); SetWindowText(HWND(lParam), L"кнопочка несогласия"); break;
			case IDCANCEL: SetWindowText(HWND(lParam), L"кнопочка сомнения");
			default: break;
			}
			break;
		case ID_MENU_1_1:
			INS = MessageBox(NULL, L"и вправду менюшка", L"Вау!", MB_OK); switch (INS) {}
			break;
		case ID_MENU_1_2:
			INS = MessageBox(NULL, L"афигеть", L"действительно", MB_OK); switch (INS) {}
			break;
		default: MessageBox(NULL, L"Что-то пошло не так", L"Ошибка", MB_OK | MB_ICONSTOP); break;

		}
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return NULL;
}