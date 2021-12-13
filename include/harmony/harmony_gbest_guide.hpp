/*
 * harmony_gbest_guide.hpp
 *
 *  Created on: 2021/12/12
 *      Author: hommyo
 */

#ifndef INCLUDE_HARMONY_GBEST_GUIDE_HPP_
#define INCLUDE_HARMONY_GBEST_GUIDE_HPP_

#include "harmony_default.hpp"

namespace harmony_search
{
    namespace hs_gbest_guide
    {
        using namespace hs_default;

        struct HarmonyGbestGuideStrategy: HarmonySearchStrategy
        {
        protected:


        public:

            using HarmonySearchStrategy::HarmonySearchStrategy;

            virtual Harmony
            generate_tuning_harmony( const std::size_t ) const override;
        };

        template< class P = HarmonySearchParameter, class S = HarmonyGbestGuideStrategy, class R = HarmonyResult >
        struct HarmonyGbestGuideOptimizer: HarmonyOptimizer< P, S, R >
        {
        protected:

        public:

            using HarmonyOptimizer< P, S, R >::HarmonyOptimizer;
        };
    }    // namespace hs_gbest_guide
}    // namespace harmony_search


#endif /* INCLUDE_HARMONY_GBEST_GUIDE_HPP_ */
