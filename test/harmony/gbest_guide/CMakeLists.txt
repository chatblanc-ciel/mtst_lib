cmake_minimum_required(VERSION 3.16)


add_executable(harmony-gbest_guide-test harmony_gbest_guide_test.cpp)
	target_link_libraries(harmony-gbest_guide-test ${PROJECT_NAME})

add_test(
    NAME harmony-gbest_guide-HarmonyGbestGuideStrategy_constract
    COMMAND $<TARGET_FILE:harmony-gbest_guide-test> HarmonyGbestGuideStrategy_constract
    )
    set_property(
        TEST harmony-gbest_guide-HarmonyGbestGuideStrategy_constract
        PROPERTY LABELS lib harmony harmony_gbest_guide HarmonyGbestGuideStrategy_constract
        )