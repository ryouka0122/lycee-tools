#include "includes.h"

#include "MainApplication.h"

#include "utils.h"
#include "aco.h"

LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wp, lp);
}

int  test(HINSTANCE hInstance ,int nCmdShow) {

	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(wcex);
	wcex.hbrBackground = GetStockBrush(WHITE_BRUSH);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.lpfnWndProc = wndProc;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = TEXT("TEST_APPLICATION_1.0.0");
	wcex.lpszMenuName = NULL;
	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;

	ATOM atom = RegisterClassEx(&wcex);
	if (INVALID_ATOM == atom) {
		return -1;
	}

	HWND hWnd = CreateWindowEx(0L, MAKEINTATOM(atom),
		TEXT("テスト アプリケーション"), WS_OVERLAPPEDWINDOW,
		0, 0, 400, 400, NULL, NULL, hInstance, NULL);

	if (IsWindow(hWnd)) {
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		MSG msg;
		while (0 < GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}
	UnregisterClass(MAKEINTATOM(atom), hInstance);

	return 0;
}


#ifdef UNICODE
int WINAPI wWinMain(
#else
int WINAPI WinMain(
#endif
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow
) {


	lycee::MainApplication *app = new lycee::MainApplication(hInstance);
	int res = 0;
	if (app->initialize()) {
		res = app->run(nCmdShow);
	}
	delete app;

	/* AntColonyOptimizationのサンプル
	int step = 10;
	int cost[2][10] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, },
		{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, }
	};

	lycee::aco::AntColonyOptimization aco(3, 0.8, 0.15, 50);

	aco.setCost(cost[0], cost[1], step);
	aco.optimize(10);
	
	double **result = new double*[2];
	result[0] = (double*)memset(new double[step], 0, sizeof(double)*step);
	result[1] = (double*)memset(new double[step], 0, sizeof(double)*step);
	
	aco.getPheromone(result, 10);

	for (int i = 0; i< 2; i++) {
		for (int j = 0; j < step; j++) {
			lycee::Log::debug("%4.2lf ", result[i][j]);
		}
		lycee::Log::debug("\n");
	}*/

	return 0;


	/*
	lycee::MainApplication *app = new lycee::MainApplication(hInstance);
	int res = 0;
	if ( app->initialize() ) {
		res = app->run(nCmdShow);
	}
	delete app;
	*/
}

