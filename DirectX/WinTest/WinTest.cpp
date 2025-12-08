// WinTest.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinTest.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// HINSTANCE: 이 프로그램의 식별번호.
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
    LoadStringW(hInstance, IDC_WINTEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINTEST));

    MSG msg;

    // 기본 메시지 루프입니다:
	// GetMessage: 메시지 큐에서 메시지를 꺼내 msg 구조체에 저장.
    // 메세지가 없을 경우 함수 내부에서 대기.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
			// 키보드 입력은 WM_KEYDOWN이 발생. 문자입력을 했다면 WM_CHAR 메시지로 변환. 키보드 관련이 아니면 건너뛴다.
            TranslateMessage(&msg);

			// msg 구조체에 저장된 메시지를 해당 윈도우 프로시저로 전달.
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // 운영체제에 등록할 창 정보를 지정하여 레지스터에 등록.
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    // 창의 가로, 세로 크기가 변경될 때마다 윈도우 전체를 다시 그리도록 설정.
    wcex.style          = CS_HREDRAW | CS_VREDRAW;

    // 창의 메시지를 처리할 함수를 지정.
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;

    // 이 프로그램의 인스턴스(식별번호)를 지정.
    wcex.hInstance      = hInstance;

    // 실행파일 아이콘.
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINTEST));

    // 마우스 커서.
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);

    // 배경 색상.
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);

    // 등록할 메뉴를 지정
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINTEST);

    // 레지스터에 등록할 윈도우 클래스 이름 지정.
	// TEXT("") 매크로는 유니코드 설정에 따라 ANSI 또는 유니코드 문자열로 변환.
	// 유니코드 설정이므로 L"" 접두사가 붙은 유니코드 문자열로 변환.
    wcex.lpszClassName  = szWindowClass;

    // 창 좌측 상단 아이콘.
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // 생성한 구조체 정보로 레지스터에 창 클래스 등록.
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

   // 창을 만들고 그 핸들을 반환.
   HWND hWnd = CreateWindowW(
	   szWindowClass,       // 창 클래스 이름
	   szTitle,             // 창 제목 표시줄 텍스트
	   WS_OVERLAPPEDWINDOW, // 창 스타일
	   CW_USEDEFAULT,       // 창의 초기 가로 위치
	   0,                   // 창의 초기 세로 위치
	   CW_USEDEFAULT,       // 창의 초기 가로 크기
	   0,                   // 창의 초기 세로 크기
	   nullptr,             // 부모 창 핸들
	   nullptr,             // 메뉴 핸들
	   hInstance,           // 인스턴스 핸들(식별번호)
	   nullptr              // 추가 매개변수(사용X)
   );

   if (!hWnd)
   {
      return FALSE;
   }

   // 창을 보여줄지 말지 설정.
   ShowWindow(hWnd, nCmdShow);

   // 창을 갱신하여 클라이언트 영역을 무효화하고 즉시 다시 그리도록 함.
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
// wParam과 lParam은 메시지에 대한 추가 정보를 제공합니다. 마우스 클릭 위치, 키보드 키 등.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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
