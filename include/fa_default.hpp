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
namespace mtst{
namespace firefly_algorithm
{

        double dist_norm( const std::vector< double >&, const std::vector< double >& );    // 距離の計算(プロトタイプ宣言)

        struct FaParam
        {
        protected:

            /* パラメータの定義 */
            std::size_t t_max_;         // 更新回数
            std::size_t particles_;     // 個体数
            std::size_t dimensions_;    // 次元数
            double randomize_;          // ランダム性パラメータα
            double attract_;            // 発光地点における誘引度β
            double absorb_;             // 吸収係数γ
            double init_pos_max_;       // 初期位置のランダム生成(最大値)
            double init_pos_min_;       // 初期位置のランダム生成(最小値)
            double ran_fly_max_;        // ランダム移動の範囲(最大値)
            double ran_fly_min_;        // ランダム移動の範囲(最小値)

        public:

            FaParam()
                : t_max_( 10000 ), particles_( 100 ), dimensions_( 10 ),
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
            std::size_t dimensions() const
            {
                return this->dimensions_;
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

            FaParam& set_dimensions( std::size_t input )
            {
                dimensions_ = input;
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

        struct FaStrat
        {
        protected:

            FaParam param_;
            std::vector< double > dis_;

            // 内部パラメータ
            std::vector< FireFly > fireflies_;

        public:

            void calc_dist();    // calc_dist(void)...引数は省略可能
            void all_fireflies_modify(); // 全個体の速度更新
            void update();    // 群のアップデート
        };

        struct FaResult
        {
        protected:

            double value_;                                            // 最良評価値
            std::vector< double > update_value_;                      // 更新曲線
            std::vector< double > variable_;                          // 最良評価値の時の変数
            std::vector< double > init_variable_;                     // 最適化開始時の最良評価値の変数
            std::vector< std::vector< double > > update_variable_;    // 変数の更新履歴
            std::size_t evals_;                                       // 評価回数
            std::clock_t start_time_;                                 // 1試行あたりの最適化の実行時間
            std::size_t iter_;                                        // 更新回数

        public:

            FaResult() {}

            FaResult& set_value( double input )
            {
                value_ = input;
                return *this;
            }

            FaResult& set_update_value( std::vector< double > input )
            {
                update_value_ = input;
                return *this;
            }

            FaResult& set_variable( std::vector< double > input )
            {
                variable_ = input;
                return *this;
            }

            FaResult& set_init_variable( std::vector< double > input )
            {
                init_variable_ = input;
                return *this;
            }

            FaResult& set_update_variable( std::vector< std::vector< double > > input )
            {
                update_variable_ = input;
                return *this;
            }

            FaResult& set_evals( std::size_t input )
            {
                evals_ = input;
                return *this;
            }

            FaResult& set_iter( std::size_t input )
            {
                iter_ = input;
                return *this;
            }

            FaResult& set_time( std::clock_t input )
            {
                start_time_ = input;
                return *this;
            }

            FaResult& set_time( double input )
            {
                start_time_ = static_cast< std::clock_t >( input );
                return *this;
            }

            double value() const
            {
                return value_;
            }
            std::vector< double > update_value() const
            {
                return update_value_;
            }
            std::vector< double > variable() const
            {
                return variable_;
            }
            std::vector< double > init_variable() const
            {
                return init_variable_;
            }
            std::vector< std::vector< double > > update_variable() const
            {
                return update_variable_;
            }
            std::size_t evals() const
            {
                return evals_;
            }
            std::size_t iter() const
            {
                return iter_;
            }
            std::clock_t time() const
            {
                return start_time_;
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
}    // namespace firefly_algorithm
}

#endif /* FA_DEFAULT_HPP_ */
