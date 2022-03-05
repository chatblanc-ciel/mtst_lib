
#ifndef LIB_HARMONY_SEARCH_HPP_
#define LIB_HARMONY_SEARCH_HPP_

#define _USE_MATH_DEFINES

#include "./filter_param.hpp"
#include "./opt_helper.hpp"

#include <complex>
#include <fstream>
#include <iostream>
#include <math.h>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

//ハーモニーサーチの流れを理解しやすくするための実行文べた貼りコード

struct Harmony_Search_Strategy {
public:
    Harmony_Search_Strategy(FilterParam input)
        : fparam(input)
        , Time_Max(9999990)
        , Harmony_size(10)
        , Bandwidth(0.1)
        , R_a(0.9)
        , R_p(0.5)
    {
    }

    //ハーモニーサーチのパラメータ
    int Time_Max; //更新回数
    int Harmony_size; //ハーモニーメモリのサイズ
    double Bandwidth; //バンド幅
    double R_a; //選択比率(大きければ大きい程、ハーモニーメモリ内が使われる)
    double R_p; //値調整比率(大きければ大きい程、値を調整する確率が上がる)
    double Rp_max = 0.3;
    double Rp_min = 0.3;
    double Bw_max = 0.1;
    double Bw_min = 0.001;

    Result optimize();
    FilterParam fparam;
};

Result Harmony_Search_Strategy::optimize() // void型でも可
{
    using namespace std;
    clock_t start = clock();

    double objective_function_value; //目的関数値

    //結果記録用
    Result result;
    vector<double> update_curve;
    vector<double> best_variable;

    const int Dimension = fparam.opt_order(); // n次元

    vector<vector<double>> Harmony_memory; //ハーモニーメモリ
    Harmony_memory.reserve(Harmony_size);

    vector<double> Harmony_new; //生成する新しいハーモニー
    Harmony_new.resize(Dimension);

    vector<double> Harmony_value; //ハーモニーメモリ内の評価値
    Harmony_value.reserve(Harmony_size);

    int r; //ランダムで選ばれるハーモニーの番号
    int worst_memory = 0; //最悪ハーモニーの番号
    double worst_value = -1000; //最悪ハーモニーの評価値
    int best_memory = 0; //最良ハーモニーの番号
    double best_value = 1000; //最良ハーモニーの評価値

    thread_local random_device rnd; // 非決定的な乱数生成器を生成
    thread_local mt19937 mt(rnd()); //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
    uniform_real_distribution<> rand_0_1(0, 1); // [0, 99] 範囲の一様乱数
    uniform_int_distribution<> rand_0_100000(0, 100000); // [0, 100000] 範囲の一様乱数
    uniform_real_distribution<> rand_around(-1, 1); // [-1, 1] 範囲の一様乱数

    //ループ用
    unsigned int i;
    unsigned int j;
    unsigned int t;

    //ハーモニーメモリの初期値設定
    for (i = 0; i < Harmony_size; i++) {
        //ハーモニーメモリの初期値を設定する
        Harmony_memory.emplace_back(fparam.init_stable_coef(0.5, 3.0));

        //目的関数値
        objective_function_value = fparam.evaluate(Harmony_memory.at(i));
        Harmony_value.emplace_back(objective_function_value);
    }

    //ハーモニーメモリ内の評価値を比較して最良ハーモニーを決定する
    for (i = 0; i < Harmony_size; i++) {
        if (Harmony_value.at(i) < best_value) {
            best_memory = i;
            best_value = Harmony_value.at(i);
        }
    }

    //ハーモニーメモリを用いた探索
    for (t = 0; t < Time_Max; t++) {
        worst_value = -1000;
        worst_memory = 0;

        R_p = Rp_min + ((Rp_max - Rp_min) / (Time_Max)) * t;

        //ランダム選択したハーモニーメモリの番号
        r = rand_0_100000(mt) % Harmony_size;

        //新しいハーモニーの生成
        if (rand_0_1(mt) < R_a) {
            for (j = 0; j < Dimension; j++) {
                if (rand_0_1(mt) < R_p) {
                    //最良値の変数を複製して代入する
                    Harmony_new.at(j) = Harmony_memory.at(best_memory).at(j);
                } else {
                    //複製して代入する
                    Harmony_new.at(j) = Harmony_memory.at(r).at(j);
                }
            }
        } else {
            //ランダムな値を代入する
            Harmony_new = fparam.init_stable_coef(0.5, 3.0);
        }

        //目標関数値
        objective_function_value = fparam.evaluate(Harmony_new);

        //ハーモニーメモリ内の評価値を比較して最悪ハーモニーを決定する
        for (i = 0; i < Harmony_size; i++) {
            if (Harmony_value.at(i) > worst_value) {
                worst_memory = i;
                worst_value = Harmony_value.at(i);
            }
        }

        //ハーモニーメモリ内の評価値と比較して最悪ハーモニーより良ければハーモニーを入れ替える
        if (objective_function_value < worst_value) {
            Harmony_value.at(worst_memory) = objective_function_value;

            Harmony_memory.at(worst_memory) = Harmony_new;
        }

        //以前の最良ハーモニーと比較して、より値が良ければ置換を行う

        if (Harmony_value.at(worst_memory) < best_value) {
            best_memory = worst_memory;
            best_value = Harmony_value.at(worst_memory);
            best_variable = Harmony_new;
        }

        update_curve.emplace_back(best_value);
    }
    clock_t end = clock();
    printf("%f\n", best_value);
    result.set_value(best_value).set_update_value(update_curve).set_variable(best_variable).set_evals(Time_Max + Harmony_size).set_time(end - start).set_iter(Time_Max);

    return (result);
}

#endif /* LIB_HARMONY_SEARCH_HPP_ */