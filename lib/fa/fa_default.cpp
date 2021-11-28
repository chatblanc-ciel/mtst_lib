/*
 * fa_default.cpp
 *
 *  Created on: 2021/10/24
 *      Author: shimokawa
 */
#include "fa_default.hpp"
#include "thread_pool.hpp"

namespace fa_default
{
    FireFly::FireFly(std::vector<double> pos, double value, std::vector<double> vel,
                     std::vector<double> best_pos, double best_value)
    {}
    
    void FireFly::update() // 良い値に更新
    {
        if(best_pos > pos)
        {
            best_pos = pos;
            best_value = value;
        }
    }
    
    void FireFly::force_update() // 強制的に更新
    {
        best_pos = pos;
        best_value = value;
    }

    void FireFly::transfer(FireFly& refer, double dis, FaParam& param) // FAの更新則
    {
        using std::uniform_real_distribution;

        thread_local std::random_device rnd; // 非決定的な乱数生成器を生成
        thread_local std::mt19937 mt(rnd()); // メルセンヌ・ツイスタの32ビット版、引数は初期シード値
        uniform_real_distribution<> init_pos(param.get_init_pos_min(), param.get_init_pos_max());
        uniform_real_distribution<> ran_fly(param.get_ran_fly_min(), param.get_ran_fly_max());

        double attract_ff = param.get_attract()*exp(-param.get_absorb()*dis);

        if(this->value > refer.value)
        {
            CellTp::zip_for_each([&]
            (double& pos, double& ref_pos, double& vel_a)
            {
                vel_a += attract_ff*(ref_pos-pos) + param.get_randomize()*ran_fly(mt);  
            },
            this->pos, refer.pos, this->vel);
        }
        else
        {
            CellTp::zip_for_each([&]
            (double& vel_a)
            {
                vel_a += param.get_randomize()*ran_fly(mt);  
            },
            this->vel);
        }
    }

    void FaStrat::calc_dist() // 全個体間の距離の計算と保存
    {
        dis.clear();

        for(unsigned int i = 0; i < fireflies.size(); i++)
        {
            for(unsigned int j = i + 1; j <fireflies.size(); j++)
            {
                dis.emplace_back(dist_norm(fireflies.at(i).pos, fireflies.at(j).pos));
            }   
        }
    }
}
