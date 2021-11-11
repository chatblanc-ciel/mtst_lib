/*
 * fa_default.cpp
 *
 *  Created on: 2021/10/24
 *      Author: shimokawa
 */
#include "fa_default.hpp"

namespace fa_default
{
    FireFly::FireFly(std::vector<double> pos, double value, std::vector<double> vel,
                     std::vector<double> best_pos, double best_value)
    {}
    
    void FireFly::update() // 更新
    {
        if(best_pos > pos)
        {
            best_pos = pos;
            best_value = value;
        }
    }
    
    void FireFly::force_update() // 強制更新
    {
        best_pos = pos;
        best_value = value;
    }

    void FireFly::transfer(FireFly&, double dis, FaParam& param) // FAの更新則
    {
        std::random_device rnd; // 非決定的な乱数生成器を生成
        std::mt19937 mt(rnd()); // メルセンヌ・ツイスタの32ビット版、引数は初期シード値
        std::uniform_real_distribution<> init_range(param.ran1_min, param.ran1_max);
        std::uniform_real_distribution<> ATTRACT_range(param.ran2_min, param.ran2_max);
    }
}
