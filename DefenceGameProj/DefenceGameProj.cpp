// DefenceGameProj.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "DefenceGameProj.h"
#include "GameManager.h"
#include "Gdi.h"



#define MAX_LOADSTRING 100

#define timer_ID_1 1

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


//전역변수
RECT rectView;
int handle;
GDI gdi;
POINT StartPos[7] = { {300,900},{320,900},{340,860},{360,900},{380,900},{380,940},{300,940} };
BOOL Clear = false;
BOOL GameOver = false;
int Score;
int KillCnt;
//함수
BOOL CALLBACK EndDialog(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void RestartProgram();


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_DEFENCEGAMEPROJ, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFENCEGAMEPROJ));

	MSG msg;

	gdi.Gdi_Init();
	// 기본 메시지 루프입니다:
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//기타 처리
		}
	}
	gdi.Gdi_End();
	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFENCEGAMEPROJ));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEFENCEGAMEPROJ);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, 768, 1024, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static GameManager gm(StartPos);
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:
	{
		/*if (AllocConsole())
		{
			freopen("CONIN$", "rb", stdin);
			freopen("CONOUT$", "wb", stdout);
			freopen("CONOUT$", "wb", stderr);
		}*/
		SetTimer(hWnd, timer_ID_1, 10, NULL);
		GetClientRect(hWnd, &rectView);
		gm.InitGameObjects(rectView);
	}
	break;
	case WM_TIMER:
	{
		if (!GameOver && !Clear) 
		{
			gm.UpdateGameObjects(handle);
			InvalidateRgn(hWnd, NULL, FALSE);
			if (gm.GetGameClear())
			{
				Clear = true;

				Score = gm.GetScore();
				KillCnt = gm.GetKillCnt();
				printf("score : %d killcnt : %d", Score, KillCnt);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, EndDialog);
			}
			if (gm.GetGameOver())
			{
				GameOver = true;

				Score = gm.GetScore();
				KillCnt = gm.GetKillCnt();
				printf("score : %d killcnt : %d", Score, KillCnt);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, EndDialog);
			}
		}
		
	}
	break;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_SPACE:
			gm.InstantiateBullet(false);
			InvalidateRgn(hWnd, NULL, FALSE);
			break;
		case VK_LEFT:
			handle = -1;
			break;
		case VK_RIGHT:
			handle = 1;
			break;
		}
	}
	break;
	case WM_KEYUP:
	{
		handle = 0;
		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		static HDC MemDC, tmpDC;
		static HBITMAP BackBit, oldBackBit;
		hdc = BeginPaint(hWnd, &ps);

		MemDC = CreateCompatibleDC(hdc);
		BackBit = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
		oldBackBit = (HBITMAP)SelectObject(MemDC, BackBit);
		PatBlt(MemDC, 0, 0, rectView.right, rectView.bottom, BLACKNESS);
		tmpDC = hdc;
		hdc = MemDC;
		MemDC = tmpDC;

		// TODO: 여기에 그리기 코드를 추가합니다.
		gm.DrawGameObjects(hdc);
		gdi.Gdi_Draw(hdc, gm.GetScore());

		tmpDC = hdc;
		hdc = MemDC;
		MemDC = tmpDC;
		BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, MemDC, 0, 0, SRCCOPY);
		SelectObject(MemDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(MemDC);
		EndPaint(hWnd, &ps);
		break;
	}
	break;
	case WM_DESTROY:
		//FreeConsole();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL CALLBACK EndDialog(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	std::wstring ScoreText = std::to_wstring(Score);
	std::wstring KillCntText = std::to_wstring(KillCnt);

	switch (iMsg)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(hWnd, ID_VALUE_SCORE,ScoreText.c_str());
		SetDlgItemText(hWnd, ID_VALUE_KILLCNT, KillCntText.c_str());
		if (Clear)
		{
			SetDlgItemText(hWnd, ID_SENTENCE, _T("CLEAR!"));
		}
		if (GameOver)
		{
			SetDlgItemText(hWnd, ID_SENTENCE, _T("GAME OVER!"));
		}
	}
	return 1;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_BUTTON_EXIT:
			PostQuitMessage(0);
			break;
		case ID_BUTTON_REPLAY:
			RestartProgram();
			break;
		}
	}
	break;
	}
	return 0;
}

void RestartProgram()
{
	// 현재 실행 파일 경로 가져오기
	TCHAR szFilePath[MAX_PATH];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);

	// 새로운 프로세스 시작
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi;
	CreateProcess(szFilePath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	// 핸들 해제
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	// 현재 프로세스 종료
	ExitProcess(0);
}