/*
 * fa_default.hpp
 *
 *  Created on: 2021/10/24
 *      Author: shimokawa
 */

#ifndef FA_DEFAULT_HPP_
#define FA_DEFAULT_HPP_

#include "common.hpp"

#include <algorithm>
#include <chrono>
#include <functional>
#include <random>
#include <string>
#include <vector>
namespace mtst{
    namespace firefly_algorithm
    {

        double dist_norm( const std::vector< double >&, const std::vector< double >& );    // 距離の計算(プロトタイプ宣言)

        template< typename... Args >
        std::string format( const std::string& fmt, Args... args )
        {
            std::size_t len = static_cast< std::size_t >( snprintf( nullptr, 0, fmt.c_str(), args... ) );
            std::vector< char > buf( len + 1 );
            snprintf( &buf[0], len + 1, fmt.c_str(), args... );
            return std::string( &buf[0], &buf[0] + len );
        }

        struct FireFly
        {
        protected:

            std::vector< double > pos_;
            double value_;
            std::vector< double > vel_;

            std::vector< double > best_pos_;
            double best_value_;

        public:

            FireFly( std::vector< double >, double, std::vector< double >, std::vector< double >, double );
            virtual ~FireFly();

            std::vector< double > pos() const
            {
                return pos_;
            }
            double value() const
            {
                return value_;
            }
            std::vector< double > vel() const
            {
                return vel_;
            }
            std::vector< double > best_pos() const
            {
                return best_pos_;
            }
            double best_value() const
            {
                return best_value_;
            }

            FireFly& set_pos( std::vector< double > input )
            {
                pos_ = input;
                return *this;
            }
            FireFly& set_value( double input )
            {
                value_ = input;
                return *this;
            }
            FireFly& set_vel( std::vector< double > input )
            {
                vel_ = input;
                return *this;
            }
            FireFly& set_best_pos( std::vector< double > input )
            {
                best_pos_ = input;
                return *this;
            }
            FireFly& set_best_value( double input )
            {
                best_value_ = input;
                return *this;
            }

            void update();    // 良い値に更新
            void force_update();    // 強制的に更新

            void transfer();
            void modify_vel( FireFly&, double, FaParam& );    // FireFly&...一個体の情報、double...dis(二個体間の距離)
        };

        struct FaParam
        {
        protected:

            /* パラメータの定義 */
            std::size_t t_max_;         // 更新回数
            std::size_t particles_;     // 個体数
            double randomize_;          // ランダム性パラメータα
            double attract_;            // 発光地点における誘引度β
            double absorb_;             // 吸収係数γ
            double init_pos_max_;       // 初期位置のランダム生成(最大値)
            double init_pos_min_;       // 初期位置のランダム生成(最小値)
            double ran_fly_max_;        // ランダム移動の範囲(最大値)
            double ran_fly_min_;        // ランダム移動の範囲(最小値)

        public:

            FaParam()
                : t_max_( 10000 ), particles_( 100 ),
                  randomize_( 0.5 ), attract_( 1.0 ), absorb_( 0.5 ),
                  init_pos_max_( 1.5 ), init_pos_min_( -1.5 ), ran_fly_max_( 0.5 ), ran_fly_min_( -0.5 )
            {}

            std::size_t t_max() const
            {
                return this->t_max_;
            }
            std::size_t particles() const
            {
                return this->particles_;
            }
            double randomize() const
            {
                return this->randomize_;
            }
            double attract() const
            {
                return this->attract_;
            }
            double absorb() const
            {
                return this->absorb_;
            }
            double init_pos_max() const
            {
                return this->init_pos_max_;
            }
            double init_pos_min() const
            {
                return this->init_pos_min_;
            }
            double ran_fly_max() const
            {
                return this->ran_fly_max_;
            }
            double ran_fly_min() const
            {
                return this->ran_fly_min_;
            }

            FaParam& set_t_max( std::size_t input )
            {
                t_max_ = input;
                return *this;
            }

            FaParam& set_particles( std::size_t input )
            {
                particles_ = input;
                return *this;
            }

            FaParam& set_randomize( double input )
            {
                randomize_ = input;
                return *this;
            }

            FaParam& set_attract( double input )
            {
                attract_ = input;
                return *this;
            }

            FaParam& set_absorb( double input )
            {
                absorb_ = input;
                return *this;
            }

            FaParam& set_init_pos_max( double input )
            {
                init_pos_max_ = input;
                return *this;
            }

            FaParam& set_init_pos_min( double input )
            {
                init_pos_min_ = input;
                return *this;
            }

            FaParam& set_ran_fly_max( double input )
            {
                ran_fly_max_ = input;
                return *this;
            }

            FaParam& set_ran_fly_min( double input )
            {
                ran_fly_min_ = input;
                return *this;
            }
        };


        struct FaStrat
        {
        protected:

            FaParam param_;
            std::size_t dim_;    // 次元数
            std::function< double( std::vector< double >& ) > obj_func_;
            std::vector< double > dis_;

            // 内部パラメータ
            std::vector< FireFly > fireflies_;

        public:

            void calc_dist();    // calc_dist(void)...引数は省略可能
            void all_fireflies_modify(); // 全個体の速度更新
            void all_fireflies_transfer(); // 全個体の位置更新
            void swarm_update();    // 群のアップデート

            virtual std::size_t best_firefly() const;

            const std::vector< FireFly >& fireflies_ref()
            {
                return std::ref( this->fireflies_ );
            }

            const FaParam& param_ref()
            {
                return std::ref( this->param_ );
            }
        };

        struct FaResult: mtst_common::result::TraitResult
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

            FaResult() {}

            std::string csv_header() const override
            {
                return std::string( "Value,Evals,Iter,Time[ms]" );
            }

            std::string csv_data() const override
            {
                return format( "%.15f,%lu,%lu,%.15f", this->value_, static_cast< long unsigned int >( this->evals_ ), static_cast< long unsigned int >( this->iter_ ), static_cast< double >( this->time_ ) );
            }
        };

        template< class P = FaParam, class S = FaStrat, class R = FaResult >
        struct FaOptimizer: mtst_common::optimizer::TraitOptimizer< R >
        {
        protected:

            P param_;

        public:

            FaOptimizer() {}
            FaOptimizer( P param ): param_( param ) {}
            virtual ~FaOptimizer() {}

            virtual R optimize( std::size_t, std::function< double( std::vector< double >& ) > ) override;

            virtual void initialize() override {}
            virtual void pre_act() override {}
            virtual void post_act() override {}
            virtual void finalize() override {}
        };

        template< class P, class S, class R >
        R FaOptimizer< P, S, R >::optimize( std::size_t dim, std::function< double( std::vector< double >& ) > obj_func )
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
            update_curve.reserve( strat.param_ref().t_max() );

            for ( std::size_t t = 0, m_evals = strat.param_ref().t_max(); t < m_evals; ++t )
            {
                // 更新前アクション
                this->pre_act();

                auto new_fireflies_dis = strat.calc_dist();

                auto new_fireflies = strat.all_fireflies_modify(new_fireflies_dis);

                strat.all_fireflies_transfer(new_fireflies);

                strat.update(new_fireflies);

                std::size_t best_index = strat.best_firefly();
                update_curve.emplace_back( strat.fireflies_ref().at( best_index ).value() );

                // 更新後アクション
                this->post_act();
            }

            this->finalize();

            // 実行時間計測終了
            clock_t end = clock();

            R result;

            std::size_t best_index = strat.best_firefly();
            result
                .set_value( strat.fireflies_ref().at( best_index ).value() )
                .set_variable( strat.fireflies_ref().at( best_index ).best_pos() )
                .set_time( end - start )
                .set_update_value( update_curve )
                .set_evals( strat.param_ref().t_max() * strat.param_ref().particles() );

            return result;
        }
    }    // namespace firefly_algorithm
}

#endif /* FA_DEFAULT_HPP_ */
