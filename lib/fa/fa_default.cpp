/*
 * fa_default.cpp
 *
 *  Created on: 2021/10/24
 *      Author: shimokawa
 */
#include "fa_default.hpp"

#include "thread_pool.hpp"

namespace mtst{
namespace firefly_algorithm
{
        FireFly::FireFly( std::vector< double > pos, double value, std::vector< double > vel, std::vector< double > best_pos, double best_value )
        {}

        void FireFly::update()    // 良い値に更新
        {
            if ( this->best_pos_ > this->pos_ )
            {
                this->best_pos_ = this->pos_;
                this->best_value_ = this->value_;
            }
        }

        void FireFly::force_update()    // 強制的に更新
        {
            this->best_pos_ = this->pos_;
            this->best_value_ = this->value_;
        }

        void FireFly::modify_vel( FireFly& refer, double dis, FaParam& param )    // FAの更新則
        {
            using std::uniform_real_distribution;

            thread_local std::random_device rnd;      // 非決定的な乱数生成器を生成
            thread_local std::mt19937 mt( rnd() );    // メルセンヌ・ツイスタの32ビット版、引数は初期シード値
            uniform_real_distribution<> init_pos( param.init_pos_min(), param.init_pos_max() );
            uniform_real_distribution<> ran_fly( param.ran_fly_min(), param.ran_fly_max() );

            double attract_ff = param.attract() * exp( -param.absorb() * dis );

            if ( this->value() > refer.value() )
            {
                CellTp::zip_for_each( [&]( double& pos, double& ref_pos, double& vel )
                                      { vel += attract_ff * ( ref_pos - pos ) + param.randomize() * ran_fly( mt ); },
                                      this->pos(), refer.pos(), this->vel() );
            }
            else
            {
                CellTp::zip_for_each( [&]( double& vel )
                                      { vel += param.randomize() * ran_fly( mt ); },
                                      this->vel() );
            }
        }

        void FireFly::transfer()
        {
            CellTp::zip_for_each( [&]( double& pos, double& vel )
                                  { pos += vel; },
                                  this->pos(), this->vel() );
        }

        void FaStrat::calc_dist()    // 全個体間の距離の計算と保存
        {
            this->dis_.clear();

            for ( unsigned int i = 0; i < this->fireflies_.size(); i++ )
            {
                for ( unsigned int j = i + 1; j < this->fireflies_.size(); j++ )
                {
                    this->dis_.emplace_back( dist_norm( this->fireflies_.at( i ).pos(), this->fireflies_.at( j ).pos() ) );
                }
            }
        }

        void FaStrat::all_fireflies_modify() // 全個体の速度更新
        {
            size_t index = 0;

            for ( unsigned int i = 0; i < this->fireflies_.size(); i++ )
            {
                for ( unsigned int j = i + 1; j < this->fireflies_.size(); j++ )
                {
                    this->fireflies_.at( i ).modify_vel( this->fireflies_.at( j ), this->dis_.at( index ), this->param_ );
                    this->fireflies_.at( j ).modify_vel( this->fireflies_.at( i ), this->dis_.at( index ), this->param_ );
                    index += 1;
                }
            }
        }

        void FaStrat::update()
        {
            for ( auto& x : fireflies_ )
            {
                x.update();
            }
        }
}    // namespace firefly_algorithm
}
