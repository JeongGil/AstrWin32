#include "CGameManager.h"

#include "CTimer.h"
#include "resource.h"

bool CGameManager::Init(HINSTANCE hInstance)
{
	hInst = hInstance;

	InitRegisterClass();

	InitCreateWindow();

	hDC = GetDC(hWnd);

	return true;
}

int CGameManager::Run()
{
	MSG msg;

	while (bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);
		}
		else
		{
			GameLoop(CTimer::Update());
		}
	}

	return static_cast<int>(msg.wParam);
}

void CGameManager::GameLoop(const float DeltaTime)
{
	char Text[64] = {};
	sprintf_s(Text, "Delta Time : %.8f", DeltaTime);
	TextOutA(hDC, 50, 50, Text, lstrlenA(Text));

	float speed = 100.f;

	float dirX = 0.f;
	float dirY = 0.f;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		dirY -= 1.f;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		dirX -= 1.f;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		dirY += 1.f;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		dirX += 1.f;
	}

	float dx = dirX * speed * DeltaTime;
	float dy = dirY * speed * DeltaTime;

	static float posX = 200.f;
	static float posY = 200.f;

	posX += dx;
	posY += dy;

	// Spawn Bullet
	static std::list<FPoint> bullets;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		constexpr FPoint bulletOffset{ 100.f, 25.f };

		FPoint bullet;
		bullet.x = posX + bulletOffset.x;
		bullet.y = posY + bulletOffset.y;
		bullets.push_back(bullet);
	}

	// Update Bullets
	for (auto& bullet : bullets)
	{
		constexpr float BULLET_SPEED = 200.f;

		bullet.x += BULLET_SPEED * DeltaTime;
		Rectangle(hDC, static_cast<int>(bullet.x), static_cast<int>(bullet.y),
			static_cast<int>(bullet.x) + 50, static_cast<int>(bullet.y) + 50);
	}

	Ellipse(hDC, posX, posY, posX + 100.f, posY + 100.f);
}

void CGameManager::InitRegisterClass() const
{
	WNDCLASSEXW wc
	{
		.cbSize = sizeof(WNDCLASSEXW),
		.style = CS_HREDRAW | CS_VREDRAW,
		.lpfnWndProc = CGameManager::WndProc,
		.cbClsExtra = 0,
		.cbWndExtra = 0,
		.hInstance = hInst,
		.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		.hCursor = LoadCursor(nullptr, IDC_ARROW),
		.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
		.lpszMenuName = nullptr,
		.lpszClassName = WINDOW_CLASS_NAME,
		.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1))
	};

	RegisterClassExW(&wc);
}

bool CGameManager::InitCreateWindow()
{
	hWnd = CreateWindowW(WINDOW_CLASS_NAME, WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		nullptr, nullptr, hInst, nullptr);

	if (!hWnd)
	{
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return true;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
	{
		bLoop = false;
		PostQuitMessage(0);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}

CGameManager::~CGameManager()
{
	ReleaseDC(hWnd, hDC);
}
