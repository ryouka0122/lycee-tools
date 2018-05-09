#include "includes.h"

#include "MainApplication.h"

#include "utils.h"
#include "aco.h"


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

	/* AntColonyOptimization‚ÌƒTƒ“ƒvƒ‹
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

	for (int i = 0; i< 2; ++i) {
		for (int j = 0; j < step; ++j) {
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

