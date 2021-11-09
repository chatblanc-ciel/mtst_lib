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

namespace fa_default
{
	
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
    };

	struct FaParam
	{
	public:

		FaParam(const int, const int, const int, const double, const double, const double,
				 const double, const double, const double, const double)
		:t_max(10000), particles(100), dimensions(100), randomize(0.5), attract(1.0), absorb(0.5),
		 ran1_Max(1.5), ran1_Min(-1.5), ran2_Max(1.5), ran2_Min(-1.5)
		{}
		
		/* パラメータの定義 */
    	int t_max;        // 更新回数
    	int particles;    // 個体数
    	int dimensions;   // 次元数
    	double randomize; // ランダム性パラメータα
    	double attract;   // 発光地点における誘引度β
    	double absorb;    // 吸収係数γ
    	double ran1_Max;  // 初期位置のランダム生成(最大値)
    	double ran1_Min;  // 初期位置のランダム生成(最小値)
    	double ran2_Max;  // ランダム移動の範囲(最大値)
    	double ran2_Min;  // ランダム移動の範囲(最小値)
	};

	struct FaStrat
	{
	protected:

    	double value;                               	   // 最良評価値
    	std::vector<double> update_value;				   // 各更新時の最良評価値
    	std::vector<double> variable;                      // 最良評価値の時の変数
    	std::vector<double> init_variable;                 // 最適化開始時の最良評価値の変数
    	std::vector<std::vector<double>> update_variable;
    	double evals;                                      // 評価回数
    	clock_t start_time;                                      // 1試行あたりの最適化の実行時間
    	size_t iter;                                       // 更新回数

	public:

    	FaStrat(){}

		FaStrat& set_value(double input)
		{
			value = input;
			return *this; 
		}

		FaStrat& set_update_value(std::vector<double> input)
		{ 
			update_value = input;
			return *this; 
		}

		FaStrat& set_variable(std::vector<double> input)
		{ 
			variable = input;
			return *this; 
		}  

		FaStrat& set_init_variable(std::vector<double> input)
		{ 
			init_variable = input;
			return *this; 
		}  

		FaStrat& set_update_variable(std::vector<std::vector<double>> input)
		{ 
			update_variable = input;
			return *this; 
		}

		FaStrat& set_evals(double input)
		{ 
			evals = input;
			return *this; 
		}

		FaStrat& set_iter(size_t input)
		{ 
			iter = input;
			return *this; 
		}

		FaStrat& set_time(clock_t input)
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
