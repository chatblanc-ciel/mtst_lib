/*
 * fa_default.hpp
 *
 *  Created on: 2021/10/24
 *      Author: shimokawa
 */

#ifndef FA_DEFAULT_HPP_
#define FA_DEFAULT_HPP_

#include <vector>

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
		:T_Max(10000), Particles(100), Dimensions(100), Randomize(0.5), Attract(1.0), Absorb(0.5),
		 Ran1_Max(1.5), Ran1_Min(-1.5), Ran2_Max(1.5), Ran2_Min(-1.5)
		{}
		
		/* パラメータの定義 */
    	int T_Max;        // 更新回数
    	int Particles;    // 個体数
    	int Dimensions;   // 次元数
    	double Randomize; // ランダム性パラメータα
    	double Attract;   // 発光地点における誘引度β
    	double Absorb;    // 吸収係数γ
    	double Ran1_Max;  // 初期位置のランダム生成(最大値)
    	double Ran1_Min;  // 初期位置のランダム生成(最小値)
    	double Ran2_Max;  // ランダム移動の範囲(最大値)
    	double Ran2_Min;  // ランダム移動の範囲(最小値)
	};
}

#endif /* FA_DEFAULT_HPP_ */
