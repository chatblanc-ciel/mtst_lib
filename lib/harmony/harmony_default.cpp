/*
 * harmony_default.cpp
 *
 *  Created on: 2021/12/03
 *      Author: matsu
 */

#include "harmony/harmony_default.hpp"
namespace mtst
{
    namespace harmony_search
    {
        /* # HarmonySearchStrategy
         *
         * ハーモニーサーチのアルゴリズムをまとめている関数
         *
         */
        HarmonySearchStrategy::HarmonySearchStrategy(
            HarmonySearchParameter param,
            std::size_t dim,
            std::function< double( std::vector< double >& ) > obj_func,
            std::function< std::vector< double >( void ) > init_func,
            std::function< std::vector< double >( void ) > rng_func )
            : param_( param ), dim_( dim ), obj_func_( obj_func ),
              init_generate_func_( init_func ), rng_generate_func_( rng_func )
        {
            using std::size_t;

            this->harmonies_.reserve( this->param_.harmony_size() );

            for ( size_t i = 0, size = this->param_.harmony_size(); i < size; ++i )
            {
                harmonies_.emplace_back( this->generate_init_harmony() );
            }
        }

        HarmonySearchStrategy::HarmonySearchStrategy(
            HarmonySearchParameter param,
            std::size_t dim,
            std::function< double( std::vector< double >& ) > obj_func,
            std::function< std::vector< double >( void ) > init_func )
            : HarmonySearchStrategy( param, dim, obj_func, init_func, [dim]()
                                     { return HarmonySearchStrategy::gen_rng_vals( dim ); } )
        {}

        HarmonySearchStrategy::HarmonySearchStrategy(
            HarmonySearchParameter param,
            std::size_t dim,
            std::function< double( std::vector< double >& ) > obj_func )
            : HarmonySearchStrategy(
                param, dim, obj_func, [dim]()
                { return HarmonySearchStrategy::gen_rng_vals( dim ); },
                [dim]()
                { return HarmonySearchStrategy::gen_rng_vals( dim ); } )
        {}

        HarmonySearchStrategy::HarmonySearchStrategy(
            HarmonySearchParameter param,
            std::size_t dim,
            std::function< double( std::vector< double >& ) > obj_func,
            std::function< std::vector< double >( void ) > init_func,
            std::function< std::vector< double >( void ) > rng_func,
            std::vector< Harmony > harmonies )
            : param_( param ), dim_( dim ), obj_func_( obj_func ),
              init_generate_func_( init_func ), rng_generate_func_( rng_func ),
              harmonies_( harmonies )
        {}

        /* # best_harmony
         *
         * ハーモニーメモリ内の最良ハーモニーを見つける関数
         *
         */
        std::size_t HarmonySearchStrategy::best_harmony() const
        {
            auto minimam = std::min_element( this->harmonies_.begin(), this->harmonies_.end(), [this]( const Harmony& h1, const Harmony& h2 )
                                             { return h1.value() < h2.value(); } );
            return std::distance( this->harmonies_.begin(), minimam );
        }

        /* # worst_harmony
         *
         * ハーモニーメモリ内の最悪ハーモニーを見つける関数
         *
         */
        std::size_t HarmonySearchStrategy::worst_harmony() const
        {
            auto maximam = std::max_element( this->harmonies_.begin(), this->harmonies_.end(), [this]( const Harmony& h1, const Harmony& h2 )
                                             { return h1.value() < h2.value(); } );
            return std::distance( this->harmonies_.begin(), maximam );
        }

        /* # trade_harmony
         *
         * 新しく生成したハーモニーと最悪ハーモニーを比較して
         * 最悪ハーモニーより新しく生成したハーモニーが良い値だった時
         * 記憶するハーモニーを入れ替える関数
         */
        void HarmonySearchStrategy::trade_harmony( Harmony new_harmony )
        {
            std::size_t index = this->worst_harmony();

            if ( new_harmony.value() < this->harmonies_.at( index ).value() )
            {
                this->harmonies_.at( index ) = new_harmony;
            }
        }

        /* # generate_tuning_harmony
         *
         * 既存ハーモニーを用いる場合の
         * 新しいハーモニーを生成する関数
         *
         */
        Harmony HarmonySearchStrategy::generate_tuning_harmony( const std::size_t index ) const
        {
            using std::uniform_real_distribution;

            thread_local std::random_device rnd;                       // 非決定的な乱数生成器を生成
            thread_local std::mt19937 mt( rnd() );                     // メルセンヌ・ツイスタの32ビット版、引数は初期シード値
            uniform_real_distribution<> rng_real( 0.0, 1.0 );          // [0, 1] 範囲の一様乱数
            uniform_real_distribution<> rng_real_abs1( -1.0, 1.0 );    // [-1, 1] 範囲の一様乱数

            std::vector< double > new_harmony_vals;
            new_harmony_vals.reserve( this->dim_ );

            for ( std::size_t i = 0, dim = this->dim_; i < dim; i++ )
            {
                if ( rng_real( mt ) < this->param_.adjustment_ratio() )
                {
                    //値を調整して代入する
                    new_harmony_vals.emplace_back( this->harmonies_.at( index ).harmony().at( i ) + this->param_.band_width() * rng_real_abs1( mt ) );
                }
                else
                {
                    //複製して代入する
                    new_harmony_vals.emplace_back( this->harmonies_.at( index ).harmony().at( i ) );
                }
            }

            return Harmony( this->obj_func_( new_harmony_vals ), new_harmony_vals );
        }

        /* # generate_harmony
         *
         * 選択比率Raを用いて
         * 新しいハーモニーを生成する関数
         *
         */
        Harmony HarmonySearchStrategy::generate_harmony() const
        {
            using std::uniform_real_distribution;

            thread_local std::random_device rnd;                 // 非決定的な乱数生成器を生成
            thread_local std::mt19937 mt( rnd() );               // メルセンヌ・ツイスタの32ビット版、引数は初期シード値
            uniform_real_distribution<> rng_real( 0.0, 1.0 );    // [0, 1] 範囲の一様乱数

            //ランダム選択したハーモニーメモリの番号
            std::size_t index = this->select_tune_harmony();

            //新しいハーモニーの生成
            if ( rng_real( mt ) < this->param_.selecttion_ratio() )
            {
                return this->generate_tuning_harmony( index );
            }
            else
            {
                return this->generate_rng_harmony();
            }
        }

        /* # select_tune_harmony
         *
         * 新しいハーモニーを生成する際に利用する
         * 既存ハーモニーの番号をランダムに決定する関数
         *
         */
        std::size_t HarmonySearchStrategy::select_tune_harmony() const
        {
            thread_local std::random_device rnd;      // 非決定的な乱数生成器を生成
            thread_local std::mt19937 mt( rnd() );    //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
            std::uniform_int_distribution<>
                select_range( 0, static_cast< int >( this->param_.harmony_size() ) - 1 );    // [0, Harmony_size - 1] 範囲の一様乱数
            return select_range( mt );
        }

        /* # gen_rng_vals
         *
         * -3から3の間の一様乱数を作る関数
         * rangeを追加した場合、rangeの絶対値の範囲内で一様乱数を生成する
         *
         */
        std::vector< double > HarmonySearchStrategy::gen_rng_vals( std::size_t dim )
        {
            return HarmonySearchStrategy::gen_rng_vals( dim, 3.0 );
        }

        std::vector< double > HarmonySearchStrategy::gen_rng_vals( std::size_t dim, double range )
        {
            thread_local std::random_device rnd;                                                   // 非決定的な乱数生成器を生成
            thread_local std::mt19937 mt( rnd() );                                                 // メルセンヌ・ツイスタの32ビット版、引数は初期シード値
            std::uniform_real_distribution<> rng_real( -std::abs( range ), std::abs( range ) );    // 一様乱数

            std::vector< double > vals( dim );
            std::generate( vals.begin(), vals.end(), [&]() mutable
                           { return rng_real( mt ); } );
            return vals;
        }

        // Explicit Instantiation
        // テンプレート組み合わせ宣言
        template struct HarmonyOptimizer< HarmonySearchParameter, HarmonySearchStrategy, HarmonyResult >;
    }    // namespace harmony_search
}    // namespace mtst
