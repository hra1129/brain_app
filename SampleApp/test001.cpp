// --------------------------------------------------------------------
//	Window表示テスト
// --------------------------------------------------------------------

#include "framework.h"

#define WND_CLASS_NAME TEXT("brain-main")

// --------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static HFONT hFont = NULL;
	static RECT rect;

	switch (uMsg) {
		case WM_CLOSE:	// 閉じるボタン
			DestroyWindow(hWnd);
			break;

		case WM_LBUTTONDOWN:
			DestroyWindow(hWnd);
			break;

		case WM_SIZE: {	 // ウィンドウサイズ変化時
			GetClientRect(hWnd, &rect);

			LOGFONT rLogfont;
			ZeroMemory(&rLogfont, sizeof(rLogfont));
			if (rect.right / 20 < rect.bottom / 4) {
				rLogfont.lfHeight = rect.right / 20;
			} else {
				rLogfont.lfHeight = rect.bottom / 4;
			}
			rLogfont.lfWeight = FW_BOLD;
			rLogfont.lfCharSet = DEFAULT_CHARSET;
			rLogfont.lfQuality = ANTIALIASED_QUALITY;
			_tcscpy(rLogfont.lfFaceName, TEXT("Tahoma"));
			if (hFont) DeleteObject(hFont);
			hFont = CreateFontIndirect(&rLogfont);

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}

		case WM_PAINT: {	// 再描画要求受領
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(255, 0, 0));
			SelectObject(hdc, hFont);
			DrawText(hdc, TEXT("Rabbit Adventure"), -1, &rect,
							 DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			EndPaint(hWnd, &ps);
			break;
		}

		case WM_DESTROY:	// 終了時
			PostQuitMessage(0);
			break;

		default:	// 無視するメッセージ
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

// --------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int /* nShowCmd */ ) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASS wcl;
	wcl.hInstance = hInstance;
	wcl.lpszClassName = WND_CLASS_NAME;
	wcl.lpfnWndProc = WindowProc;
	wcl.style = 0;
	wcl.hIcon = NULL;
	wcl.hCursor = NULL;
	wcl.lpszMenuName = NULL;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hbrBackground = CreateSolidBrush( RGB( 255, 174, 201 ) );
	if (!RegisterClass(&wcl)) return FALSE;

	HWND hWnd = CreateWindowEx( 0, WND_CLASS_NAME, TEXT("Test App"), WS_THICKFRAME,
			CW_USEDEFAULT, CW_USEDEFAULT, 480, 320, NULL, NULL, hInstance, NULL);
	if (!hWnd) return FALSE;

	ShowWindow(hWnd, SW_SHOW | SW_MAXIMIZE);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) DispatchMessage(&msg);
	return (int)msg.wParam;
}
