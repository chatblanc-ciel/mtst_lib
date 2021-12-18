#include "harmony/harmony_selection_pressure.hpp"

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>


using namespace std;

void run_HsGbestSelectionPressureStrategy_construct();
void run_HsGbestSelectionPressureStrategy_tune_harmony();
void run_HarmonyGbestSelectionPressureOptimizer_optimize();

int main( int argc, char** argv )
{
    vector< string > args( argv, argv + argc );

    if ( args.at( 1 ) == string( "HsGbestSelectionPressureStrategy_construct" ) )
    {
        run_HsGbestSelectionPressureStrategy_construct();
    }
    else if ( args.at( 1 ) == string( "HsGbestSelectionPressureStrategy_tune_harmony" ) )
    {
        run_HsGbestSelectionPressureStrategy_tune_harmony();
    }
    else if ( args.at( 1 ) == string( "HarmonyGbestSelectionPressureOptimizer_optimize" ) )
    {
        run_HarmonyGbestSelectionPressureOptimizer_optimize();
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

/* # HsGbestSelectionPressureStrategy_construct
 *
 * インスタンス化できるかテスト
 */
void run_HsGbestSelectionPressureStrategy_construct()
{
    using namespace harmony_search::hs_selection_pressure;

    // generate HarmonyStrategy
    auto strat = HsGbestSelectionPressureStrategy(
        HarmonySearchParameter().set_max_evals( 3000 ),
        3,
        sphere,
        []()
        { return HarmonySearchStrategy::gen_rng_vals( 3 ); },
        []()
        { return HarmonySearchStrategy::gen_rng_vals( 3 ); } );

    strat.initialize();
}

/* # HsGbestSelectionPressureStrategy_tune_harmony
 *
 * ルーレット選択によるGbestへの選択圧を加えた
 * 更新ハーモニー選択の確認
 */
void run_HsGbestSelectionPressureStrategy_tune_harmony()
{
    using std::vector;
    using namespace harmony_search::hs_selection_pressure;

    // genereate defintive hamonies
    vector< Harmony > harmonies {
        Harmony( 0.7, vector< double > { 0.0, 0.0, 0.0 } ),
        Harmony( 7.1, vector< double > { 0.0, 0.0, 0.0 } ),
        Harmony( 1.6, vector< double > { 0.0, 0.0, 0.0 } ),
        Harmony( 2.4, vector< double > { 0.0, 0.0, 0.0 } ),
        Harmony( 0.9, vector< double > { 0.0, 0.0, 0.0 } ),
        Harmony( 0.5, vector< double > { 0.0, 0.0, 0.0 } ),
        Harmony( 6.6, vector< double > { 0.0, 0.0, 0.0 } ),
        Harmony( 3.6, vector< double > { 0.0, 0.0, 0.0 } ),
        Harmony( 4.4, vector< double > { 0.0, 0.0, 0.0 } ),
        Harmony( 5.9, vector< double > { 0.0, 0.0, 0.0 } ),
    };

    // generate HarmonyStrategy
    auto strat = HsGbestSelectionPressureStrategy(
        HarmonySearchParameter().set_max_evals( 3000 ),
        3,
        sphere,
        []()
        { return HarmonySearchStrategy::gen_rng_vals( 3 ); },
        []()
        { return HarmonySearchStrategy::gen_rng_vals( 3 ); },
        harmonies );

    strat.initialize();
    strat.select_tune_harmony();

    map< std::size_t, int > hist;
    for ( int n = 0; n < 10000; ++n )
    {
        ++hist[strat.select_tune_harmony()];
    }
    for ( auto p : hist )
    {
        std::cout << p.first << ' '
                  << std::string( p.second / 100, '*' ) << '\n';
    }
}

/* # HarmonyGbestSelectionPressureOptimizer
 *
 * ミニマルな条件で最適化が実行できるか
 */
void run_HarmonyGbestSelectionPressureOptimizer_optimize()
{
    using namespace harmony_search::hs_selection_pressure;

    HarmonyGbestSelectionPressureOptimizer<> optimizer( HarmonySearchParameter().set_max_evals( 3000 ) );
    auto result = optimizer.optimize( 10, sphere );

    printf( "value %.15f\n", result.value() );
    printf( "evals %lu\n", static_cast< long unsigned int >( result.evals() ) );
    printf( "time %.15f\n", static_cast< double >( result.time() ) );
}