/*
 * fa_default.hpp
 *
 *  Created on: 2021/10/24
 *      Author: shimokawa
 */

#ifndef FA_DEFAULT_HPP_
#define FA_DEFAULT_HPP_

#include <vector>
#include <ctime>
#include <string>
#include<random>

namespace fa_default
{
	struct FaOptimizer
	{
		/*
		この中にoptimizeという関数
		・initialize(初期化)
		*/
	};
	
	struct FireFly
    {
    public:

        FireFly(std::vector<double>, double, std::vector<double>, std::vector<double>, double);
		virtual ~FireFly();

	    std::vector<double> pos;
	    double value;
	    std::vector<double> vel;

	    std::vector<double> best_pos;
	    double best_value;

		void update();
		void force_update();

		void transfer(FireFly&, double, FaParam&); // FireFly&...一個体の情報、double...dis(二個体間の距離)
    };

	struct FaParam
	{
	protected:

    	/* パラメータの定義 */
    	size_t t_max;        // 更新回数
    	size_t particles;    // 個体数
    	size_t dimensions;   // 次元数
    	double randomize; // ランダム性パラメータα
    	double attract;   // 発光地点における誘引度β
    	double absorb;    // 吸収係数γ
    	double init_pos_max;  // 初期位置のランダム生成(最大値)
    	double init_pos_min;  // 初期位置のランダム生成(最小値)
    	double ran_fly_max;  // ランダム移動の範囲(最大値)
    	double ran_fly_min;  // ランダム移動の範囲(最小値)
	
	public:

		FaParam(const int, const int, const int, const double, const double, const double,
				const double, const double, const double, const double)
		:t_max(10000), particles(100), dimensions(10), randomize(0.5), attract(1.0), absorb(0.5),
		 init_pos_max(1.5), init_pos_min(-1.5), ran_fly_max(0.5), ran_fly_min(-0.5)
		{}

		int get_t_max() const
    	{ return t_max; }
    	int get_particles() const
    	{ return particles; }
		double get_dimensions() const
		{ return dimensions; }
		double get_randomize() const
		{ return randomize; }
		double get_attract() const
		{ return attract; }
		double get_absorb() const
		{ return absorb; }
		double get_init_pos_max() const
		{ return init_pos_max; }
		double get_init_pos_min() const
		{ return init_pos_min; }
		double get_ran_fly_max() const
		{ return ran_fly_max; }
		double get_ran_fly_min() const
		{ return ran_fly_min; }

		FaParam& set_t_max(const size_t input)
		{
			t_max = input;
			return *this;
		}

		FaParam& set_particles(const size_t input)
		{
			particles = input;
			return *this;
		}

		FaParam& set_dimensions(const size_t input)
		{
			dimensions = input;
			return *this;
		}

		FaParam& set_randomize(const double input)
		{
			randomize = input;
			return *this;
		}

		FaParam& set_attract(const double input)
		{
			attract = input;
			return *this;
		}

		FaParam& set_absorb(const double input)
		{
			absorb = input;
			return *this;
		}

		FaParam& set_init_pos_max(const double input)
		{
			init_pos_max = input;
			return *this;
		}

		FaParam& set_init_pos_min(const double input)
		{
			init_pos_min = input;
			return *this;
		}

		FaParam& set_ran_fly_max(const double input)
		{
			ran_fly_max = input;
			return *this;
		}

		FaParam& set_ran_fly_min(const double input)
		{
			ran_fly_min = input;
			return *this;
		}
	};

	struct FaStrat
	{
		
	};

	struct FaResult
	{
	protected:

    	double value;                               	   // 最良評価値
    	std::vector<double> update_value;				   // 各更新時の最良評価値
    	std::vector<double> variable;                      // 最良評価値の時の変数
    	std::vector<double> init_variable;                 // 最適化開始時の最良評価値の変数
    	std::vector<std::vector<double>> update_variable;
    	double evals;                                      // 評価回数
    	clock_t start_time;                                // 1試行あたりの最適化の実行時間
    	size_t iter;

	public:

		FaResult& set_value(double input)
		{
			value = input;
			return *this; 
		}

		FaResult& set_update_value(std::vector<double> input)
		{ 
			update_value = input;
			return *this; 
		}

		FaResult& set_variable(std::vector<double> input)
		{ 
			variable = input;
			return *this; 
		}  

		FaResult& set_init_variable(std::vector<double> input)
		{ 
			init_variable = input;
			return *this; 
		}  

		FaResult& set_update_variable(std::vector<std::vector<double>> input)
		{ 
			update_variable = input;
			return *this; 
		}

		FaResult& set_evals(double input)
		{ 
			evals = input;
			return *this; 
		}

		FaResult& set_iter(size_t input)
		{ 
			iter = input;
			return *this; 
		}

		FaResult& set_time(clock_t input)
		{ 
			start_time = input;
			return *this; 
		}

		double get_value() const
		{ return value; }
		std::vector<double> get_update_value() const
		{ return update_value; }
		std::vector<double> get_variable() const
		{ return variable; }
		std::vector<double> get_init_variable() const
		{ return init_variable; }
		std::vector<std::vector<double>> get_update_variable() const
		{ return update_variable; }   
		double get_evals() const
		{ return evals; }
		size_t get_iter() const
		{ return iter; }
		clock_t get_time() const
		{ return start_time; }
	};
}

#endif /* FA_DEFAULT_HPP_ */
