#ifndef __LYCEE__RESOURCE_HEADER__
#define __LYCEE__RESOURCE_HEADER__

#include <Windows.h>

#define RESOURCE_STRING_MAX_LEN		256

#define IDS_APP_TITLE			103

#define IDR_MAINFRAME			128
#define IDD_LYCEETOOLS_DIALOG	102
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105

#define IDI_LYCEETOOLS			107

#define IDI_SMALL				108
#define IDC_LYCEETOOLS			109

#define IDC_MYICON				2
#ifndef IDC_STATIC
#define IDC_STATIC				-1
#endif

// コンテキストメニュー
#define IDC_CXT_ACOMENU			0x1000
#define IDM_CXT_MODE_START		0x1100	// モードの始端
#define IDM_CXT_MODE_VIEWER		0x1101	// 表示モード
#define IDM_CXT_MODE_NODE		0x1102	// ノード設定
#define IDM_CXT_MODE_ANCHOR		0x1103	// アンカー制御
#define IDM_CXT_MODE_ACO		0x1104	// ACO実行
#define IDM_CXT_MODE_END		0x11FF	// モードの終端

#define	IDM_CXT_ADD_NODE		0x1201	// ノードの追加
#define IDM_CXT_RESET			0x1301	// リセット




#endif	// __LYCEE__RESOURCE_HEADER__
