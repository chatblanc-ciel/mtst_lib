/*
 * fa_default.hpp
 *
 *  Created on: 2021/10/24
 *      Author: shimokawa
 */

#ifndef FA_DEFAULT_HPP_
#define FA_DEFAULT_HPP_

#include <algorithm>
#include <chrono>
#include <functional>
#include <random>
#include <string>
#include <vector>

namespace firefly_algorithm
{
    namespace fa_default
    {
        double dist_norm( const std::vector< double >&, const std::vector< double >& );    // 距離の計算(プロトタイプ宣言)

        struct FaParam
        {
        protected:

            /* パラメータの定義 */
            std::size_t t_max;         // 更新回数
            std::size_t particles;     // 個体数
            std::size_t dimensions;    // 次元数
            double randomize;          // ランダム性パラメータα
            double attract;            // 発光地点における誘引度β
            double absorb;             // 吸収係数γ
            double init_pos_max;       // 初期位置のランダム生成(最大値)
            double init_pos_min;       // 初期位置のランダム生成(最小値)
            double ran_fly_max;        // ランダム移動の範囲(最大値)
            double ran_fly_min;        // ランダム移動の範囲(最小値)

        public:

            FaParam()
                : t_max( 10000 ), particles( 100 ), dimensions( 10 ), randomize( 0.5 ), attract( 1.0 ), absorb( 0.5 ),
                  init_pos_max( 1.5 ), init_pos_min( -1.5 ), ran_fly_max( 0.5 ), ran_fly_min( -0.5 )
            {}

            std::size_t get_t_max() const
            {
                return this->t_max;
            }
            std::size_t get_particles() const
            {
                return this->particles;
            }
            std::size_t get_dimensions() const
            {
                return this->dimensions;
            }
            double get_randomize() const
            {
                return this->randomize;
            }
            double get_attract() const
            {
                return this->attract;
            }
            double get_absorb() const
            {
                return this->absorb;
            }
            double get_init_pos_max() const
            {
                return this->init_pos_max;
            }
            double get_init_pos_min() const
            {
                return this->init_pos_min;
            }
            double get_ran_fly_max() const
            {
                return this->ran_fly_max;
            }
            double get_ran_fly_min() const
            {
                return this->ran_fly_min;
            }

            FaParam& set_t_max( std::size_t input )
            {
                t_max = input;
                return *this;
            }

            FaParam& set_particles( std::size_t input )
            {
                particles = input;
                return *this;
            }

            FaParam& set_dimensions( std::size_t input )
            {
                dimensions = input;
                return *this;
            }

            FaParam& set_randomize( double input )
            {
                randomize = input;
                return *this;
            }

            FaParam& set_attract( double input )
            {
                attract = input;
                return *this;
            }

            FaParam& set_absorb( double input )
            {
                absorb = input;
                return *this;
            }

            FaParam& set_init_pos_max( double input )
            {
                init_pos_max = input;
                return *this;
            }

            FaParam& set_init_pos_min( double input )
            {
                init_pos_min = input;
                return *this;
            }

            FaParam& set_ran_fly_max( double input )
            {
                ran_fly_max = input;
                return *this;
            }

            FaParam& set_ran_fly_min( double input )
            {
                ran_fly_min = input;
                return *this;
            }
        };
        struct FaParam
        {
        protected:

            /* パラメータの定義 */
            std::size_t t_max;         // 更新回数
            std::size_t particles;     // 個体数
            std::size_t dimensions;    // 次元数
            double randomize;          // ランダム性パラメータα
            double attract;            // 発光地点における誘引度β
            double absorb;             // 吸収係数γ
            double init_pos_max;       // 初期位置のランダム生成(最大値)
            double init_pos_min;       // 初期位置のランダム生成(最小値)
            double ran_fly_max;        // ランダム移動の範囲(最大値)
            double ran_fly_min;        // ランダム移動の範囲(最小値)

        public:

            FaParam()
                : t_max( 10000 ), particles( 100 ), dimensions( 10 ), randomize( 0.5 ), attract( 1.0 ), absorb( 0.5 ),
                  init_pos_max( 1.5 ), init_pos_min( -1.5 ), ran_fly_max( 0.5 ), ran_fly_min( -0.5 )
            {}

            std::size_t get_t_max() const
            {
                return this->t_max;
            }
            std::size_t get_particles() const
            {
                return this->particles;
            }
            std::size_t get_dimensions() const
            {
                return this->dimensions;
            }
            double get_randomize() const
            {
                return this->randomize;
            }
            double get_attract() const
            {
                return this->attract;
            }
            double get_absorb() const
            {
                return this->absorb;
            }
            double get_init_pos_max() const
            {
                return this->init_pos_max;
            }
            double get_init_pos_min() const
            {
                return this->init_pos_min;
            }
            double get_ran_fly_max() const
            {
                return this->ran_fly_max;
            }
            double get_ran_fly_min() const
            {
                return this->ran_fly_min;
            }

            FaParam& set_t_max( std::size_t input )
            {
                t_max = input;
                return *this;
            }

            FaParam& set_particles( std::size_t input )
            {
                particles = input;
                return *this;
            }

            FaParam& set_dimensions( std::size_t input )
            {
                dimensions = input;
                return *this;
            }

            FaParam& set_randomize( double input )
            {
                randomize = input;
                return *this;
            }

            FaParam& set_attract( double input )
            {
                attract = input;
                return *this;
            }

            FaParam& set_absorb( double input )
            {
                absorb = input;
                return *this;
            }

            FaParam& set_init_pos_max( double input )
            {
                init_pos_max = input;
                return *this;
            }

            FaParam& set_init_pos_min( double input )
            {
                init_pos_min = input;
                return *this;
            }

            FaParam& set_ran_fly_max( double input )
            {
                ran_fly_max = input;
                return *this;
            }

            FaParam& set_ran_fly_min( double input )
            {
                ran_fly_min = input;
                return *this;
            }
        };
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

            void update();
            void force_update();

            void transfer();
            void modify_vel( FireFly&, double, FaParam& );    // FireFly&...一個体の情報、double...dis(二個体間の距離)
        };

        struct FaStrat
        {
        protected:

            std::vector< double > dis;
            FaParam param;

            // 内部パラメータ
            std::vector< FireFly > fireflies;

        public:

            void calc_dist();    // calc_dist(void)...引数は省略可能
            void all_fireflies_update();
        };

        struct FaResult
        {
        protected:

            double value;                           // 最良評価値
            std::vector< double > update_value;     // 各更新時の最良評価値
            std::vector< double > variable;         // 最良評価値の時の変数
            std::vector< double > init_variable;    // 最適化開始時の最良評価値の変数
            std::vector< std::vector< double > > update_variable;
            std::size_t evals;          // 評価回数
            std::clock_t start_time;    // 1試行あたりの最適化の実行時間
            std::size_t iter;

        public:

            FaResult() {}

            FaResult& set_value( double input )
            {
                value = input;
                return *this;
            }

            FaResult& set_update_value( std::vector< double > input )
            {
                update_value = input;
                return *this;
            }

            FaResult& set_variable( std::vector< double > input )
            {
                variable = input;
                return *this;
            }

            FaResult& set_init_variable( std::vector< double > input )
            {
                init_variable = input;
                return *this;
            }

            FaResult& set_update_variable( std::vector< std::vector< double > > input )
            {
                update_variable = input;
                return *this;
            }

            FaResult& set_evals( std::size_t input )
            {
                evals = input;
                return *this;
            }

            FaResult& set_iter( std::size_t input )
            {
                iter = input;
                return *this;
            }

            FaResult& set_time( std::clock_t input )
            {
                start_time = input;
                return *this;
            }

            FaResult& set_time( double input )
            {
                start_time = static_cast< std::clock_t >( input );
                return *this;
            }

            double get_value() const
            {
                return value;
            }
            std::vector< double > get_update_value() const
            {
                return update_value;
            }
            std::vector< double > get_variable() const
            {
                return variable;
            }
            std::vector< double > get_init_variable() const
            {
                return init_variable;
            }
            std::vector< std::vector< double > > get_update_variable() const
            {
                return update_variable;
            }
            std::size_t get_evals() const
            {
                return evals;
            }
            std::size_t get_iter() const
            {
                return iter;
            }
            std::clock_t get_time() const
            {
                return start_time;
            }
        };

        struct FaOptimizer
        {
        protected:

            FaParam param;

        public:

            FaOptimizer() {}
            FaOptimizer( FaParam parameter ): param( parameter ) {}
            virtual ~FaOptimizer() {}
        };
    }    // namespace fa_default
}    // namespace firefly_algorithm

#endif /* FA_DEFAULT_HPP_ */
