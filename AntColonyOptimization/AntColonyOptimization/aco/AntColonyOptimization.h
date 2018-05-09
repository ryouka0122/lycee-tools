#ifndef __LYCEE__ANT_COLONY_OPTIMIZATION__HEADER__
#define __LYCEE__ANT_COLONY_OPTIMIZATION__HEADER__

namespace lycee {

namespace aco {

	class AntColonyOptimization {
	public:
		// ==================================================
		// デストラクタ
		//
		virtual ~AntColonyOptimization();
		
		// ==================================================
		// コンストラクタ
		//
		explicit AntColonyOptimization(double Q, double rho, double epsilon, int iterLimit = 50);

		// ==================================================
		// 最適化で使用する定数の設定
		//
		void setOptimizer(double Q, double rho, double epsilon, int iterLimit);

		void setQ(double Q);
		void setRho(double rho);
		void setEpsilon(double epsilon);
		void setIterLimit(int iterLimit);

	private:
		double K_Q;
		double K_RHO;
		double K_EPSILON;
		int K_ITER_LIMIT;

	public:
		// ==================================================
		// 経路の設定
		//
		void setCost(int *left, int *right, int step);

		// ==================================================
		// 最適化
		//
		void optimize(int ant);

		// ==================================================
		// 結果の取得
		//
		void getPheromone(double **result, int step);

	private:
		void walk();
		void update();

		void release();

		template<typename T>
		T** release_array(T **ary, int n) {
			if (ary) {
				for(int i=0 ; i<n ; ++i) {
					delete[] ary[i];
				}
				delete[] ary;
			}
			return 0;
		}

		template<typename T>
		T** new_2array(int n, int m) {
			T** res = new T*[n];
			for (int i = 0; i < n; ++i) {
				res[i] = (T*)memset(new T[m], 0, sizeof(T)*m);
			}
			return res;
		}

	private:
		int step;
		int numsAnt;
		int **cost;
		double **pheromone;
		int **mstep;


		double rand1();
		int rand01();

	};
	

}	// aco
	
}	// lycee
#endif	// __LYCEE__ANT_COLONY_OPTIMIZATION__HEADER__