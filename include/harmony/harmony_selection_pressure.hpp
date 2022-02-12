/*
 * harmony_selection_pressure.hpp
 *
 *  Created on: 2021/12/18
 *      Author: matsu
 */

#ifndef INCLUDE_HARMONY_HARMONY_SELECTION_PRESSURE_HPP_
#define INCLUDE_HARMONY_HARMONY_SELECTION_PRESSURE_HPP_

#include "harmony_default.hpp"
namespace mtst
{
    namespace harmony_search
    {


        struct HsGbestSelectionPressureStrategy: HarmonySearchStrategy
        {
        protected:

            std::vector< std::size_t > harmony_serial_index_;
            mutable std::vector< double > harmony_serial_fvalue_;

        public:

            using HarmonySearchStrategy::HarmonySearchStrategy;

            void initialize() override;
            std::size_t select_tune_harmony() const override;
        };

        template< class P = HarmonySearchParameter, class S = HsGbestSelectionPressureStrategy, class R = HarmonyResult >
        struct HarmonyGbestSelectionPressureOptimizer: HarmonyOptimizer< P, S, R >
        {
        protected:

        public:

            using HarmonyOptimizer< P, S, R >::HarmonyOptimizer;
        };
    }    // namespace harmony_search
}    // namespace mtst


#endif /* INCLUDE_HARMONY_HARMONY_SELECTION_PRESSURE_HPP_ */
