/*
 * harmony_selection_pressure.cpp
 *
 *  Created on: 2021/12/18
 *      Author: matsu
 */

#include "harmony/harmony_selection_pressure.hpp"

namespace mtst
{
    namespace harmony_search
    {
        std::size_t HsGbestSelectionPressureStrategy::select_tune_harmony() const
        {
            thread_local std::random_device rnd;      // 非決定的な乱数生成器を生成
            thread_local std::mt19937 mt( rnd() );    //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値

            // weight array generation
            double max_value = this->harmonies_.at( this->worst_harmony() ).value();
            auto harmony_iter = this->harmonies_.begin();
            std::generate( this->harmony_serial_fvalue_.begin(), this->harmony_serial_fvalue_.end(),
                           [&harmony_iter, max_value]() mutable -> double
                           {
                               double value = 1.0 / harmony_iter->value();
                               harmony_iter += 1;
                               return value;
                           } );

            std::piecewise_constant_distribution< double > weighted_range(
                this->harmony_serial_index_.begin(), this->harmony_serial_index_.end(), this->harmony_serial_fvalue_.begin() );

            return static_cast< std::size_t >( std::floor( weighted_range( mt ) ) );
        }

        void HsGbestSelectionPressureStrategy::initialize()
        {
            // construct harmonies serial number index
            this->harmony_serial_index_.resize( this->param_.harmony_size() + 1, 0.0 );
            std::iota( this->harmony_serial_index_.begin(), this->harmony_serial_index_.end(), 0 );

            // reserve harmonies serial objective function value
            this->harmony_serial_fvalue_.resize( this->param_.harmony_size(), 0.0 );
        }

        // Explicit Instantiation
        // テンプレート組み合わせ宣言
        template struct HarmonyGbestSelectionPressureOptimizer< HarmonySearchParameter, HsGbestSelectionPressureStrategy, HarmonyResult >;

    }    // namespace harmony_search
}    // namespace mtst
