#include "harmony/harmony_gbest_guide.hpp"

#include <cassert>
#include <cstdio>
#include <string>
#include <vector>


using namespace std;

void run_HarmonyGbestGuideStrategy_constract();

int main( int argc, char** argv )
{
    vector< string > args( argv, argv + argc );

    if ( args.at( 1 ) == string( "HarmonyGbestGuideStrategy_constract" ) )
    {
        run_HarmonyGbestGuideStrategy_constract();
    }
    else
    {
        fprintf( stderr, "Matching test is not exist.\n" );
        exit( -1 );
    }

    return 0;
}

// ベンチマーク関数 Sphere
double sphere( const vector< double >& x )
{
    double value = 0.0;

    for ( auto& v : x )
    {
        value += v * v;
    }

    return value;
}

void run_HarmonyGbestGuideStrategy_constract()
{
    using namespace harmony_search::hs_gbest_guide;

    // generate HarmonyStrategy
    auto strat = HarmonyGbestGuideStrategy(
        HarmonySearchParameter().set_max_evals( 3000 ),
        3,
        sphere );
}
