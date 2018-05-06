#include "../MainApplication.h"


// ==========================================================================
// メニュー項目の選択イベント
void lycee::MainApplication::event_command(WORD menuId) {
	switch (menuId) {
	case IDM_CXT_RESET:
		nodeList.clear();
		roadInfoList.clear();
		toggleMenu(IDM_CXT_MODE_VIEWER);
		break;
	case IDM_CXT_MODE_VIEWER:
	case IDM_CXT_MODE_NODE:
	case IDM_CXT_MODE_ANCHOR:
	case IDM_CXT_MODE_ACO:
		toggleMenu(menuId);
		break;
	case IDM_CXT_ADD_NODE:
		add_node(eventHandler->clickedPt);
		break;
	}
	refresh();
}

// ==========================================================================
// メニュー項目のトグル処理
void lycee::MainApplication::toggleMenu(WORD menuId) {
	CheckMenuRadioItem(hContextMenu, IDM_CXT_MODE_START, IDM_CXT_MODE_END, menuId, MF_BYCOMMAND);
	EnableMenuItem(hContextMenu, IDM_CXT_ADD_NODE,
		(menuId == IDM_CXT_MODE_NODE ? MF_ENABLED : MF_DISABLED)
	);
	// listenerをメニューに応じて切り替え
	switch (menuId) {
	case IDM_CXT_MODE_NODE:
		eventHandler = nodeEventHandler;
		break;
	case IDM_CXT_MODE_ANCHOR:
		eventHandler = anchorEventHandler;
		break;
	case IDM_CXT_MODE_ACO:
		eventHandler = acoEventHandler;
		break;
	case IDM_CXT_MODE_VIEWER:
	default:
		eventHandler = defaultEventHandler;
		break;
	}
	eventHandler->reset();
	
}


void lycee::MainApplication::showContextMenu(long x, long y) {
	POINT pt = { x, y };
	ClientToScreen(this->hWnd, &pt);
	TrackPopupMenu(this->hContextMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, NULL);
}


// ==========================================================================
// ACORoadInfoの追加
void lycee::MainApplication::add_node(const POINT &pt) {
	this->nodeList.push_back(pt);
	int size = (int)nodeList.size();
	if (size >= 2) {
		ACORoadInfo info(size - 2, size - 1,
			nodeList[size - 2],
			nodeList[size - 1]
		);
		roadInfoList.push_back(info);
	}
}