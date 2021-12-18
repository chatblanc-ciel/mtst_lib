/*
 * harmony_improved.cpp
 *
 *  Created on: 2021/12/12
 *      Author: matsu
 */

#include "harmony/harmony_improved.hpp"

namespace harmony_search
{
    namespace hs_improved
    {
        using namespace hs_default;

        HarmonyImprovedParameter& HarmonyImprovedParameter::configure_update_ratio()
        {
            // initialize parameter
            this->band_width_ = this->band_width_0_;
            this->adjustment_ratio_ = this->adjustment_ratio_0_;

            // configure update ratio
            this->bw_update_ratio_ = ( this->band_width_t_ - this->band_width_0_ ) / static_cast< double >( this->m_evals_ );
            this->ar_update_ratio_ = ( this->adjustment_ratio_t_ - this->adjustment_ratio_0_ ) / static_cast< double >( this->m_evals_ );

            return *this;
        }

        void HarmonyImprovedParameter::update_parameter( std::size_t evals )
        {
            this->band_width_ = this->bw_update_ratio_ * static_cast< double >( evals );
            this->adjustment_ratio_ = this->bw_update_ratio_ * static_cast< double >( evals );
        }
    }    // namespace hs_improved
}    // namespace harmony_search
