/*
 * harmony_gbest_guide.hpp
 *
 *  Created on: 2021/12/12
 *      Author: hommyo
 */

#ifndef INCLUDE_HARMONY_GBEST_GUIDE_HPP_
#define INCLUDE_HARMONY_GBEST_GUIDE_HPP_

#include "harmony_default.hpp"
namespace mtst
{
    namespace harmony_search
    {
        struct HarmonyGbestGuideStrategy: HarmonySearchStrategy
        {
        protected:


        public:

            using HarmonySearchStrategy::HarmonySearchStrategy;

            virtual Harmony
            generate_tuning_harmony( const std::size_t ) const override;
        };

        template< class P = HarmonySearchParameter, class S = HarmonyGbestGuideStrategy >
        struct HarmonyGbestGuideOptimizer: HarmonyOptimizer< P, S >
        {
        protected:

        public:

            using HarmonyOptimizer< P, S >::HarmonyOptimizer;
        };
    }    // namespace harmony_search
}    // namespace mtst


#endif /* INCLUDE_HARMONY_GBEST_GUIDE_HPP_ */
