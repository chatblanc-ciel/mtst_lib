/*
 * harmony_improved.hpp
 *
 *  Created on: 2021/12/12
 *      Author: matsu
 */

#ifndef INCLUDE_HARMONY_HARMONY_IMPROVED_HPP_
#define INCLUDE_HARMONY_HARMONY_IMPROVED_HPP_

#include "harmony_default.hpp"
namespace mtst
{
    namespace harmony_search
    {

        struct HarmonyImprovedParameter: HarmonySearchParameter
        {
        protected:

            double band_width_0_;
            double band_width_t_;
            double bw_update_ratio_;    // band width update ratio

            double adjustment_ratio_0_;
            double adjustment_ratio_t_;
            double ar_update_ratio_;    // adjustment ratio update ratio

        public:

            using HarmonySearchParameter::HarmonySearchParameter;

            HarmonyImprovedParameter()
                : HarmonySearchParameter(),
                  band_width_0_( 0.1 ), band_width_t_( 0.001 ), bw_update_ratio_( 0.0 ),
                  adjustment_ratio_0_( 0.99 ), adjustment_ratio_t_( 0.01 ), ar_update_ratio_( 0.0 )
            {
                this->configure_update_ratio();
            }

            double band_width_0() const
            {
                return this->band_width_0_;
            }
            double band_width_t() const
            {
                return this->band_width_t_;
            }
            double bw_update_ratio() const
            {
                return this->bw_update_ratio_;
            }
            double adjustment_ratio_0() const
            {
                return this->adjustment_ratio_0_;
            }
            double adjustment_ratio_t() const
            {
                return this->adjustment_ratio_t_;
            }
            double ar_update_ratio() const
            {
                return this->ar_update_ratio_;
            }

            HarmonyImprovedParameter& set_band_width_0( double input )
            {
                this->band_width_0_ = input;
                return *this;
            }
            HarmonyImprovedParameter& set_band_width_t( double input )
            {
                this->band_width_0_ = input;
                return *this;
            }
            HarmonyImprovedParameter& set_adjustment_ratio_0( double input )
            {
                this->adjustment_ratio_0_ = input;
                return *this;
            }
            HarmonyImprovedParameter& set_adjustment_ratio_t( double input )
            {
                this->adjustment_ratio_t_ = input;
                return *this;
            }

            virtual HarmonyImprovedParameter& configure_update_ratio();
            virtual void update_parameter( std::size_t evals );
        };
    }    // namespace harmony_search
}    // namespace mtst


#endif /* INCLUDE_HARMONY_HARMONY_IMPROVED_HPP_ */
