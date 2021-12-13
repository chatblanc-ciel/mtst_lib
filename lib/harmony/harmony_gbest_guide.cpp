/*
 * harmony_gbest_guide.cpp
 *
 *  Created on: 2021/12/12
 *      Author: hommyo
 */

#include "harmony/harmony_gbest_guide.hpp"

namespace harmony_search
{
    namespace hs_default
    {    // Explicit Instantiation
        // テンプレート組み合わせ宣言
        template struct HarmonyOptimizer< HarmonySearchParameter, hs_gbest_guide::HarmonyGbestGuideStrategy >;
    }    // namespace hs_default

    namespace hs_gbest_guide
    {
        using namespace hs_default;

        Harmony HarmonyGbestGuideStrategy::generate_tuning_harmony( const std::size_t index ) const
        {
            using std::uniform_real_distribution;

            thread_local std::random_device rnd;                       // 非決定的な乱数生成器を生成
            thread_local std::mt19937 mt( rnd() );                     // メルセンヌ・ツイスタの32ビット版、引数は初期シード値
            uniform_real_distribution<> rng_real( 0.0, 1.0 );          // [0, 1] 範囲の一様乱数
            uniform_real_distribution<> rng_real_abs1( -1.0, 1.0 );    // [-1, 1] 範囲の一様乱数

            std::vector< double > new_harmony_vals;
            new_harmony_vals.reserve( this->dim_ );
            std::size_t best_index = this->best_harmony();

            for ( std::size_t i = 0, dim = this->dim_; i < dim; i++ )
            {
                if ( rng_real( mt ) < this->param_.adjustment_ratio() )
                {
                    //最良値の変数を複製して代入する
                    new_harmony_vals.emplace_back( this->harmonies_.at( best_index ).harmony().at( i ) );
                }
                else
                {
                    //複製して代入する
                    new_harmony_vals.emplace_back( this->harmonies_.at( index ).harmony().at( i ) );
                }
            }

            return Harmony( this->obj_func_( new_harmony_vals ), new_harmony_vals );
        }

        // Explicit Instantiation
        // テンプレート組み合わせ宣言
        template struct HarmonyGbestGuideOptimizer< HarmonySearchParameter, HarmonyGbestGuideStrategy >;

    }    // namespace hs_gbest_guide
}    // namespace harmony_search
