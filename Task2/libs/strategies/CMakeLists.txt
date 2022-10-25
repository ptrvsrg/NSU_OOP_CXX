set(STRATEGIES
        always_cooperate
        always_defect
        grim_trigger
        pavlov
        random
        tit_for_tat
        tit_for_tat_with_forgiveness
        CACHE STRING "Strategies name" FORCE)

add_subdirectory(strategy_interface)

foreach(STRATEGY ${STRATEGIES})
    add_subdirectory(${STRATEGY})
endforeach(STRATEGY)

add_subdirectory(strategy_creator)