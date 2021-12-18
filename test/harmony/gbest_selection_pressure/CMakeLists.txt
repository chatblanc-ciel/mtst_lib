cmake_minimum_required(VERSION 3.16)


add_executable(harmony-selection-pressure-test harmony_selection_pressure_test.cpp)
	target_link_libraries(harmony-selection-pressure-test ${PROJECT_NAME})


add_test(
    NAME harmony-selection-pressure-test-HsGbestSelectionPressureStrategy_construct
    COMMAND $<TARGET_FILE:harmony-selection-pressure-test> HsGbestSelectionPressureStrategy_construct
    )
    set_property(
        TEST harmony-selection-pressure-test-HsGbestSelectionPressureStrategy_construct
        PROPERTY LABELS lib harmony harmony-selection-pressure HsGbestSelectionPressureStrategy_construct
        )

add_test(
    NAME harmony-selection-pressure-test-HsGbestSelectionPressureStrategy_tune_harmony
    COMMAND $<TARGET_FILE:harmony-selection-pressure-test> HsGbestSelectionPressureStrategy_tune_harmony
    )
    set_property(
        TEST harmony-selection-pressure-test-HsGbestSelectionPressureStrategy_tune_harmony
        PROPERTY LABELS lib harmony harmony-selection-pressure HsGbestSelectionPressureStrategy_tune_harmony
        )

add_test(
    NAME harmony-selection-pressure-test-HarmonyGbestSelectionPressureOptimizer_optimize
    COMMAND $<TARGET_FILE:harmony-selection-pressure-test> HarmonyGbestSelectionPressureOptimizer_optimize
    )
    set_property(
        TEST harmony-selection-pressure-test-HarmonyGbestSelectionPressureOptimizer_optimize
        PROPERTY LABELS lib harmony harmony-selection-pressure HarmonyGbestSelectionPressureOptimizer_optimize
        )
