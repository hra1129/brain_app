// --------------------------------------------------------------------
//	基本的なヘッダ定義
// --------------------------------------------------------------------

#ifndef _UNICODE
#define _UNICODE
#endif
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <tchar.h>

#ifndef WS_OVERLAPPEDWINDOW
#define WS_OVERLAPPEDWINDOW \
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
#endif

#ifdef UNDER_CE
	#undef SW_MAXIMIZE
	#define SW_MAXIMIZE 12

	#undef SW_MINIMIZE
	#define SW_MINIMIZE 6

	#undef WS_MINIMIZEBOX
	#define WS_MINIMIZEBOX 0x00010000L

	#undef WS_MAXIMIZEBOX
	#define WS_MAXIMIZEBOX 0x00020000L

	#ifndef _tWinMain
		#define _tWinMain WinMain
	#endif
#endif
