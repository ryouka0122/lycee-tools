#include "AntColonyOptimization.h"

#include <cmath>
#include <ctime>

#include <memory>

lycee::aco::AntColonyOptimization::~AntColonyOptimization()
{
	release();
}

lycee::aco::AntColonyOptimization::AntColonyOptimization(int Q, double rho, double epsilon, int iterLimit)
	:
	K_Q(Q)
	, K_RHO(rho)
	, K_EPSILON(epsilon)
	, K_ITER_LIMIT(iterLimit)
	, step(0)
	, cost(0)
	, pheromone(0)
	, mstep(0)
	, numsAnt(0)
{
	;
}
void lycee::aco::AntColonyOptimization::release() {
	cost = release_array(cost, 2);
	pheromone = release_array(pheromone, 2);
	mstep = release_array(mstep, numsAnt);

}

void lycee::aco::AntColonyOptimization::setOptimizer(int Q, double rho, double epsilon, int iterLimit) {
	this->K_Q = Q;
	this->K_RHO = rho;
	this->K_EPSILON = epsilon;
	this->K_ITER_LIMIT = iterLimit;
}
void lycee::aco::AntColonyOptimization::setQ(int Q) {
	this->K_Q = Q;
}
void lycee::aco::AntColonyOptimization::setRho(double rho) {
	this->K_RHO = rho;
}
void lycee::aco::AntColonyOptimization::setEpsilon(double epsilon) {
	this->K_EPSILON = epsilon;
}
void lycee::aco::AntColonyOptimization::setIterLimit(int iterLimit) {
	this->K_ITER_LIMIT = iterLimit;
}


void lycee::aco::AntColonyOptimization::setCost(int *left, int *right, int _step) {
	release();
	
	step = _step;
	cost = new int*[2];
	cost[0] = new int[step];
	cost[1] = new int[step];
	for (int i = 0; i < step; i++) {
		cost[0][i] = left[i];
		cost[1][i] = right[i];
	}

	pheromone = new double*[2];
	pheromone[0] = (double*)memset(new double[step], 0, sizeof(double)*step);
	pheromone[1] = (double*)memset(new double[step], 0, sizeof(double)*step);
}

void lycee::aco::AntColonyOptimization::optimize(int ant) {
	mstep = release_array(mstep, numsAnt);

	numsAnt = ant;
	mstep = new int*[ant];
	for (int i = 0; i < ant; i++) {
		mstep[i] = new int[step];
		memset(mstep[i], 0, sizeof(int)*step);
	}
		
	// 乱数の初期化
	srand((unsigned int)time(NULL));
	//srand(32768);

	int cnt = 0;
	do {
		// 蟻を歩かせる
		walk();
		// フェロモンの更新
		update();
	} while (++cnt < K_ITER_LIMIT);
	return;
}

void lycee::aco::AntColonyOptimization::walk() {
	for (int ant = 0; ant < numsAnt; ant++) {
		for (int s = 0; s < step; s++) {
			// epsilon - greedy  method
			if ((rand1() < K_EPSILON)
				|| (abs(pheromone[0][s] - pheromone[1][s]) < 1.0e-9)
				) {
				mstep[ant][s] = rand01();
			}
			else {
				if (pheromone[0][s] > pheromone[1][s]) {
					mstep[ant][s] = 0;
				}else{
					mstep[ant][s] = 1;
				}
			}

		}
	}
	return;
}

void lycee::aco::AntColonyOptimization::update() {
	// フェロモンの蒸発
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < step; j++) {
			pheromone[i][j] *= K_RHO;
		}
	}
	int distTotal = 0;
	int distWalk;
	for (int ant = 0; ant < numsAnt; ant++) {
		// 移動距離の算出
		distWalk = 0;
		for (int i = 0; i < step; i++) {
			distWalk += cost[mstep[ant][i]][i];
		}
		// フェロモンの上塗り
		for (int i = 0; i < step; i++) {
			pheromone[mstep[ant][i]][i] += K_Q * (1.0/distWalk);
		}
		distTotal += distWalk;
	}
	return;
}

void lycee::aco::AntColonyOptimization::getPheromone(double **result, int step) {
	for (int i = 0; i < step; i++) {
		result[0][i] = pheromone[0][i];
		result[1][i] = pheromone[1][i];
	}
}

double lycee::aco::AntColonyOptimization::rand1() {
	return (double)rand() / RAND_MAX;
}

int lycee::aco::AntColonyOptimization::rand01() {
	int rnd;
	while ( (rnd=rand())==RAND_MAX) ;
	return (int) ( (double)rnd / RAND_MAX * 2) ;
}