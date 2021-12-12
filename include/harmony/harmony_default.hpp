/*
 * harmony_default.hpp
 *
 *  Created on: 2021/12/03
 *      Author: matsu
 */

#ifndef INCLUDE_HARMONY_DEFAULT_HPP_
#define INCLUDE_HARMONY_DEFAULT_HPP_

#include "common.hpp"

#include <algorithm>
#include <chrono>
#include <functional>
#include <random>
#include <string>
#include <vector>

namespace mtst
{
    namespace harmony_search
    {

        /* # String format function
         *
         */
        template< typename... Args >
        std::string format( const std::string& fmt, Args... args )
        {
            std::size_t len = static_cast< std::size_t >( snprintf( nullptr, 0, fmt.c_str(), args... ) );
            std::vector< char > buf( len + 1 );
            snprintf( &buf[0], len + 1, fmt.c_str(), args... );
            return std::string( &buf[0], &buf[0] + len );
        }

        struct Harmony
        {
        protected:

            double value_;
            std::vector< double > harmony_;

        public:

            Harmony( double value, std::vector< double > vals )
                : value_( value ), harmony_( vals )
            {}

            std::vector< double > harmony() const
            {
                return harmony_;
            }
            double value() const
            {
                return value_;
            }
            Harmony& set_harmony( std::vector< double > input )
            {
                harmony_ = input;
                return *this;
            }
            Harmony& value( double input )
            {
                value_ = input;
                return *this;
            }
        };

        struct HarmonySearchParameter
        {
        protected:

            std::size_t m_evals_;         //更新回数
            std::size_t harmony_size_;    //ハーモニーメモリのサイズ
            double band_width_;           //バンド幅
            double selecttion_ratio_;     // = Ra = 選択比率(大きければ大きい程、ハーモニーメモリ内が使われる)
            double adjustment_ratio_;     // = Rp = 値調整比率(大きければ大きい程、値を調整する確率が上がる)

        public:

            HarmonySearchParameter()
                : m_evals_( 9999990 ), harmony_size_( 10 ), band_width_( 0.1 ),
                  selecttion_ratio_( 0.9 ), adjustment_ratio_( 0.1 )
            {}

            std::size_t max_evals() const
            {
                return this->m_evals_;
            }
            size_t harmony_size() const
            {
                return this->harmony_size_;
            }
            double band_width() const
            {
                return this->band_width_;
            }
            double selecttion_ratio() const
            {
                return this->selecttion_ratio_;
            }
            double adjustment_ratio() const
            {
                return this->adjustment_ratio_;
            }

            HarmonySearchParameter& set_max_evals( std::size_t input )
            {
                m_evals_ = input;
                return *this;
            }
            HarmonySearchParameter& set_harmony_size( std::size_t input )
            {
                harmony_size_ = input;
                return *this;
            }
            HarmonySearchParameter& set_band_width( double input )
            {
                band_width_ = input;
                return *this;
            }
            HarmonySearchParameter& set_selecttion_ratio( double input )
            {
                selecttion_ratio_ = input;
                return *this;
            }
            HarmonySearchParameter& set_adjustment_ratio( double input )
            {
                adjustment_ratio_ = input;
                return *this;
            }
        };

        struct HarmonySearchStrategy
        {
        protected:

            HarmonySearchParameter param_;
            std::size_t dim_;
            std::function< double( std::vector< double >& ) > obj_func_;
            std::function< std::vector< double >( void ) > init_generate_func_;
            std::function< std::vector< double >( void ) > rng_generate_func_;

            // 内部パラメータ
            std::vector< Harmony > harmonies_;

        public:

            HarmonySearchStrategy( HarmonySearchParameter, std::size_t, std::function< double( std::vector< double >& ) > );
            HarmonySearchStrategy(
                HarmonySearchParameter,
                std::size_t,
                std::function< double( std::vector< double >& ) >,
                std::function< std::vector< double >( void ) > );
            HarmonySearchStrategy(
                HarmonySearchParameter,
                std::size_t,
                std::function< double( std::vector< double >& ) >,
                std::function< std::vector< double >( void ) >,
                std::function< std::vector< double >( void ) > );
            // for test
            HarmonySearchStrategy(
                HarmonySearchParameter,
                std::size_t,
                std::function< double( std::vector< double >& ) >,
                std::function< std::vector< double >( void ) >,
                std::function< std::vector< double >( void ) >,
                std::vector< Harmony > );
            virtual ~HarmonySearchStrategy() {}

            const std::vector< Harmony >& harmonies_ref()
            {
                return std::ref( this->harmonies_ );
            }

            const HarmonySearchParameter& param_ref()
            {
                return std::ref( this->param_ );
            }

            virtual Harmony generate_init_harmony() const
            {
                std::vector< double > new_harmony_vals = this->init_generate_func_();
                return Harmony( this->obj_func_( new_harmony_vals ), new_harmony_vals );
            }
            virtual Harmony generate_rng_harmony() const
            {
                std::vector< double > new_harmony_vals = this->rng_generate_func_();
                return Harmony( this->obj_func_( new_harmony_vals ), new_harmony_vals );
            }
            virtual Harmony generate_tuning_harmony( const std::size_t ) const;
            virtual Harmony generate_harmony() const;
            virtual std::size_t best_harmony() const;
            virtual std::size_t worst_harmony() const;
            virtual void trade_harmony( Harmony );

            virtual std::size_t select_tune_harmony() const;

            static std::vector< double > gen_rng_vals( std::size_t );
            static std::vector< double > gen_rng_vals( std::size_t, double );
        };

        struct HarmonyResult: mtst_common::result::TraitResult
        {
        protected:

            // double value_;                                            // 最良評価値
            // std::vector< double > update_value_;                      // 更新曲線
            // std::vector< double > variable_;                          // 最良評価値の時の変数
            // std::vector< double > init_variable_;                     // 最適化開始時の最良評価値の変数
            // std::vector< std::vector< double > > update_variable_;    // 変数の更新履歴
            // std::size_t evals_;                                       // 評価回数
            // std::clock_t time_;                                       // 1試行あたりの最適化の実行時間
            // std::size_t iter_;                                        // 更新回数

        public:

            HarmonyResult() {}

            std::string csv_header() const override
            {
                return std::string( "Value,Evals,Iter,Time[ms]" );
            }

            std::string csv_data() const override
            {
                return format( "%.15f,%lu,%lu,%.15f", this->value_, static_cast< long unsigned int >( this->evals_ ), static_cast< long unsigned int >( this->iter_ ), static_cast< double >( this->time_ ) );
            }
        };

        template< class P = HarmonySearchParameter, class S = HarmonySearchStrategy, class R = HarmonyResult >
        struct HarmonyOptimizer: mtst_common::optimizer::TraitOptimizer< R >
        {
        protected:

            P param_;

        public:

            HarmonyOptimizer() {}
            HarmonyOptimizer( P param ): param_( param ) {}
            virtual ~HarmonyOptimizer() {}

            virtual R optimize( std::size_t, std::function< double( std::vector< double >& ) > ) override;

            virtual void initialize() override {}
            virtual void pre_act() override {}
            virtual void post_act() override {}
            virtual void finalize() override {}
        };

        template< class P, class S, class R >
        R HarmonyOptimizer< P, S, R >::optimize( std::size_t dim, std::function< double( std::vector< double >& ) > obj_func )
        {
            using std::clock_t;
            using std::vector;

            // 実行時間計測開始
            clock_t start = clock();

            // 初期化アクション
            this->initialize();
            S strat( this->param_, dim, obj_func );

            // 結果記録用
            vector< double > update_curve;
            update_curve.reserve( strat.param_ref().max_evals() );

            for ( std::size_t t = 0, m_evals = strat.param_ref().max_evals(); t < m_evals; ++t )
            {
                // 更新前アクション
                this->pre_act();

                // 新しいハーモニーの生成
                auto new_harmony = strat.generate_harmony();

                //ハーモニーメモリ内の評価値と比較して最悪ハーモニーより良ければハーモニーを入れ替える
                strat.trade_harmony( new_harmony );

                // 探索履歴の保存
                std::size_t best_index = strat.best_harmony();
                update_curve.emplace_back( strat.harmonies_ref().at( best_index ).value() );

                // 更新後アクション
                this->post_act();
            }

            this->finalize();

            // 実行時間計測終了
            clock_t end = clock();


            R result;

            std::size_t best_index = strat.best_harmony();
            result
                .set_value( strat.harmonies_ref().at( best_index ).value() )
                .set_variable( strat.harmonies_ref().at( best_index ).harmony() )
                .set_time( end - start )
                .set_update_value( update_curve )
                .set_evals( strat.param_ref().max_evals() + strat.param_ref().harmony_size() );

            return result;
        }
    }    // namespace harmony_search
}    // namespace mtst


#endif /* INCLUDE_HARMONY_DEFAULT_HPP_ */
