// --------------------------------------------------------------------
//	Window表示テスト
// --------------------------------------------------------------------

#include "framework.h"

// --------------------------------------------------------------------
static HFONT hFont = NULL;
static HBRUSH hBgBrush = NULL;
static RECT rect;
static int blink_index;

// --------------------------------------------------------------------
//	Windowが生成されたとき (CreateWindowが呼ばれたとき)
static LRESULT onCreate( HWND hWnd, WPARAM wParam, LPARAM lParam ) {
	LOGFONT rLogfont;

	UNREFERENCED_PARAMETER( wParam );
	UNREFERENCED_PARAMETER( lParam );

	ZeroMemory( &rLogfont, sizeof(rLogfont) );
	rLogfont.lfHeight	= 40;
	rLogfont.lfHeight	= 30;
	rLogfont.lfWeight	= FW_BOLD;
	rLogfont.lfCharSet	= DEFAULT_CHARSET;
	rLogfont.lfQuality	= ANTIALIASED_QUALITY;
	_tcscpy( rLogfont.lfFaceName, TEXT("Tahoma") );

	RELEASE_GDIOBJ( hFont );
	hFont = CreateFontIndirect( &rLogfont );

	hBgBrush = CreateSolidBrush( RGB( 255, 200, 240 ) );

	//	ウィンドウ全体を更新
	InvalidateRect( hWnd, NULL, TRUE );

	//	タイマーをセット(ワンショット)
	SetTimer( hWnd, 10, 20 /* msec */, NULL );
	return 0;
}

// --------------------------------------------------------------------
//	Windowが生成されたとき (CreateWindowが呼ばれたとき)
static LRESULT onSize( HWND hWnd, WPARAM wParam, LPARAM lParam ) {
	UNREFERENCED_PARAMETER( wParam );
	UNREFERENCED_PARAMETER( lParam );

	GetClientRect( hWnd, &rect );
	return 0;
}

// --------------------------------------------------------------------
//	画面をタッチされたイベント(マウスの左ボタンを押したイベント)
static LRESULT onLButtonDown( HWND hWnd, WPARAM wParam, LPARAM lParam ) {
	UNREFERENCED_PARAMETER( wParam );
	UNREFERENCED_PARAMETER( lParam );

	//	メインウィンドウを削除する
	DestroyWindow( hWnd );
	return 0;
}

// --------------------------------------------------------------------
//	[×] がクリックされたイベント
static LRESULT onClose( HWND hWnd, WPARAM wParam, LPARAM lParam ) {
	UNREFERENCED_PARAMETER( wParam );
	UNREFERENCED_PARAMETER( lParam );

	//	メインウィンドウを削除する
	DestroyWindow( hWnd );
	return 0;
}

// --------------------------------------------------------------------
//	ウィンドウ一部、または全部の更新処理
static LRESULT onPaint( HWND hWnd, WPARAM wParam, LPARAM lParam ) {
	UNREFERENCED_PARAMETER( wParam );
	UNREFERENCED_PARAMETER( lParam );
	PAINTSTRUCT ps;

	//	ウィンドウ部分をロックして、その部分のデバイスコンテキストを得る
	HDC hdc = BeginPaint( hWnd, &ps );

	FillRect( hdc, &rect, hBgBrush );
	SetBkMode( hdc, TRANSPARENT );
	SetTextColor( hdc, RGB(255, 0, 0) );
	SelectObject( hdc, hFont );
	DrawText( hdc, 
		TEXT("Hello, World!!!"), 
		-1, 
		&rect,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	//	ロックを解放する
	EndPaint( hWnd, &ps );
	return 0;
}

// --------------------------------------------------------------------
//	ウィンドウの削除が要求されたとき (DestroyWindow が呼ばれて消える直前にくる)
static LRESULT onDestroy( HWND hWnd, WPARAM wParam, LPARAM lParam ) {
	UNREFERENCED_PARAMETER( hWnd );
	UNREFERENCED_PARAMETER( wParam );
	UNREFERENCED_PARAMETER( lParam );

	//	GDIオブジェクト解放
	RELEASE_GDIOBJ( hFont );
	RELEASE_GDIOBJ( hBgBrush );
	//	メッセージキューの終了要求
	PostQuitMessage( 0 );
	return 0;
}

// --------------------------------------------------------------------
//	タイマー
static LRESULT onTimer( HWND hWnd, WPARAM wParam, LPARAM lParam ) {
	int r, g, b, light;

	UNREFERENCED_PARAMETER( wParam );
	UNREFERENCED_PARAMETER( lParam );

	RELEASE_GDIOBJ( hBgBrush );

	//	blink_index は 0～511 の範囲で単純にインクリメントしている。0～255 はそのまま明るさ。256～511 は 255～0 に対応しする明るさ。
	if( blink_index >= 256 ) {
		light = 511 - blink_index;
	}
	else {
		light = blink_index;
	}
	//	背景色を計算
	r = (255 * light) >> 8;
	g = (200 * light) >> 8;
	b = (240 * light) >> 8;
	//	背景用ブラシを作り直し
	RELEASE_GDIOBJ( hBgBrush );
	hBgBrush = CreateSolidBrush( RGB( r, g, b ) );
	//	次のタイマーをセット
	SetTimer( hWnd, 10, 20, NULL );
	//	全体表示更新を予約
	InvalidateRect( hWnd, NULL, TRUE );
	//	Blink を変化させる
	blink_index = (blink_index + 1) & 511;
	return 0;
}

// --------------------------------------------------------------------
//	ウィンドウプロシージャ
LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {

	switch (uMsg) {
	ACTIVATE( WM_CREATE				, onCreate					);
	ACTIVATE( WM_SIZE				, onSize					);
	ACTIVATE( WM_LBUTTONDOWN		, onLButtonDown				);
	ACTIVATE( WM_CLOSE				, onClose					);
	ACTIVATE( WM_PAINT				, onPaint					);
	ACTIVATE( WM_TIMER				, onTimer					);
	ACTIVATE( WM_DESTROY			, onDestroy					);
	default:
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}
	return 0;
}

// --------------------------------------------------------------------
//	エントリーポイント
// --------------------------------------------------------------------
int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd ) {
	WNDCLASS wcl;

	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );
	UNREFERENCED_PARAMETER( nShowCmd );

	//	WindowClass を生成する
	wcl.hInstance		= hInstance;
	wcl.lpszClassName	= _T("SampleApp");
	wcl.lpfnWndProc		= WindowProc;
	wcl.style			= 0;
	wcl.hIcon			= NULL;
	wcl.hCursor			= NULL;
	wcl.lpszMenuName	= NULL;
	wcl.cbClsExtra		= 0;
	wcl.cbWndExtra		= 0;
	wcl.hbrBackground	= NULL;
	if (!RegisterClass(&wcl)) return FALSE;

	//	上記WindowClass に基づいて Windowを生成する
	HWND hWnd = CreateWindowEx( 
		0, 
		wcl.lpszClassName, 
		TEXT("Test App"), 
		WS_THICKFRAME,
		0, 
		0, 
		480, 
		320, 
		NULL, 
		NULL, 
		hInstance, 
		NULL
	);
	if( !hWnd ) {
		return FALSE;
	}
	//	生成したWindowを表示・最大化して、表示内容を更新
	ShowWindow(hWnd, SW_SHOW | SW_MAXIMIZE);
	UpdateWindow( hWnd );

	MSG msg;
	while( GetMessage( &msg, NULL, 0, 0 ) ) {
		DispatchMessage( &msg );
	}
	return (int)msg.wParam;
}
