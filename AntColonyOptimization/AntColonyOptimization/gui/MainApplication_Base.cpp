#include "../MainApplication.h"



// ---------------------------------------------------------------
//
// �f�X�g���N�^
//
lycee::MainApplication::~MainApplication()
{
	DeleteObject(hBackScreenBitmap);
	DeleteDC(hBackScreenDC);
	DestroyMenu(hCxtBaseMenu);
	UnregisterClass(MAKEINTATOM(this->atom), hInstance);
}

// ---------------------------------------------------------------
//
// �R���X�g���N�^
//
lycee::MainApplication::MainApplication(HINSTANCE _hInst) :
	// �A�v���P�[�V����
	appName()
	, title()
	, hInstance(_hInst)
	, atom(INVALID_ATOM)
	, hWnd(NULL)
	, hAccelTable(NULL)
	// �R���e�L�X�g���j���[
	, hCxtBaseMenu(NULL)
	, hContextMenu(NULL)
	// �_�u���o�b�t�@�����O�p
	, hBackScreenDC(NULL)
	, hBackScreenBitmap(NULL)
	// �}�E�X�C�x���g�I�u�W�F�N�g
	, eventHandler(NULL)
	, defaultEventHandler(NULL)
	, nodeEventHandler(NULL)
	, anchorEventHandler(NULL)
	, acoEventHandler(NULL)
	// ACO���
	, currentMode(WAIT)
	, nodeList()
	, roadInfoList()
	, activeRoad(NULL)
	, draggedPtIndex(NO_DRAGGING)
	, hitType(NoHit)
{
	;
}

// ---------------------------------------------------------------
//
// �R�[���o�b�N
//
LRESULT lycee::MainApplication::Callback(UINT uMsg, WPARAM wp, LPARAM lp) {
	switch(uMsg) {
	// ========================================================================
	// �}�E�X�֘A�̃C�x���g
	//
	case WM_MOUSEMOVE:
		this->eventHandler->move(lycee::MouseInfo(MouseKey::MK_None, lp));
		return 0;

	case WM_MOUSELEAVE:
		this->eventHandler->leave();
		return 0;

	case WM_LBUTTONDOWN:
		this->eventHandler->down(lycee::MouseInfo(MouseKey::MK_Left, lp));
		return 0;

	case WM_LBUTTONUP:
		this->eventHandler->up(lycee::MouseInfo(MouseKey::MK_Left, lp));
		return 0;

	case WM_RBUTTONDOWN:
		this->eventHandler->down(lycee::MouseInfo(MouseKey::MK_Right, lp));
		return 0;

	case WM_RBUTTONUP:
		this->eventHandler->up(lycee::MouseInfo(MouseKey::MK_Right, lp));
		return 0;
	
	// ========================================================================
	// ���j���[�C�x���g
	//
	case WM_COMMAND:
		event_command(LOWORD(wp));
		return 0;
	// ========================================================================
	// �L�[�{�[�h�֘A�̃C�x���g
	//
	case WM_KEYDOWN:
		eventHandler->keydown((UINT)wp);
		return 0;

	// ========================================================================
	// �ĕ`��C�x���g
	//
	case WM_PAINT:
		event_paint();
		return 0;

	// ========================================================================
	// �E�B���h�E�j���C�x���g
	//
	case WM_DESTROY:
		lycee::WindowProcedure::release(this);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wp, lp);
}

// ---------------------------------------------------------------
//
// ������
//
BOOL lycee::MainApplication::initialize() {
	// ���\�[�X���̎擾
	title = lycee::utils::Resources::loadString(IDS_APP_TITLE, RESOURCE_STRING_MAX_LEN);
	appName = lycee::utils::Resources::loadString(IDC_LYCEETOOLS, RESOURCE_STRING_MAX_LEN);

	// ATOM�̐���
	atom = registerClass();
	
	if (INVALID_ATOM == atom) {
		return FALSE;
	}

	// �����\���p�ɍ��W�̌v�Z
	DWORD dwStyle = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX;
	RECT windowRect = {0, 0, CLIENT_WIDTH, CLIENT_HEIGHT};
	
	AdjustWindowRectEx(&windowRect, dwStyle, TRUE, WS_EX_COMPOSITED);
	
	int displayWidth = GetSystemMetrics(SM_CXSCREEN);
	int displayHeight = GetSystemMetrics(SM_CYSCREEN);
	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;
	int left = (displayWidth - windowWidth) / 2;
	int top = (displayHeight - windowHeight) / 2;

	// �}�E�X�C�x���g�̓o�^
	defaultEventHandler = new lycee::EventHandler(this);
	nodeEventHandler = new lycee::NodeEventHandler(this);
	anchorEventHandler = new lycee::AnchorEventHandler(this);
	acoEventHandler = new lycee::ACOEventHandler(this);

	// �E�B���h�E�̐���
	hWnd = CreateWindowEx(WS_EX_COMPOSITED, MAKEINTRESOURCE(atom),
		title.c_str(), dwStyle,
		left, top, windowWidth, windowHeight,
		NULL, NULL, hInstance, NULL);

	if ( !IsWindow(hWnd) ) {
		return FALSE;
	}

	// �A�N�Z�����[�^�̏���
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LYCEETOOLS));
	
	// �R���e�L�X�g���j���[�̏���
	hCxtBaseMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_CXT_ACOMENU));
	hContextMenu = GetSubMenu(hCxtBaseMenu, 0);

	// ���ʃv���V�[�W���ɓo�^
	lycee::WindowProcedure::entry(this);

	// �_�u���o�b�t�@�����O�p�I�t�X�N���[��
	HDC hWndDC = GetDC(hWnd);
	hBackScreenDC = CreateCompatibleDC(NULL);
	hBackScreenBitmap = CreateCompatibleBitmap(hWndDC, CLIENT_WIDTH, CLIENT_HEIGHT);
	ReleaseDC(hWnd, hWndDC);

	return TRUE;
}

// ---------------------------------------------------------------
//
// ���s
//
int lycee::MainApplication::run(int nCmdShow) {

	// ���s�����̓r���[���[�h�ɐݒ�
	this->toggleMenu(IDM_CXT_MODE_VIEWER);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0U, 0U) > 0) {
		if (!TranslateAccelerator(msg.hwnd, this->hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

// ---------------------------------------------------------------
// �N���X�̓o�^
ATOM lycee::MainApplication::registerClass() {
	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(wcex);
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	
	wcex.hInstance = hInstance;
	wcex.hbrBackground = GetStockBrush(WHITE_BRUSH);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LYCEETOOLS));
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));

	wcex.lpfnWndProc = lycee::WindowProcedure::WndProc;
	wcex.lpszClassName = appName.c_str();
	wcex.lpszMenuName = NULL;
	
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	return RegisterClassEx(&wcex);
}

// ==========================================================================
// �`��X�V�̃C�x���g���s
void lycee::MainApplication::refresh(BOOL bErase) {
	InvalidateRect(hWnd, NULL, bErase);
}
