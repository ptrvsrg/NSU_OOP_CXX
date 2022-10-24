set(STRATEGIES
        always_cooperate
        always_defect
        random
        tit_for_tat
        grim_trigger
        pavlov
        CACHE STRING "Strategies name" FORCE)

add_subdirectory(strategy_interface)

foreach(STRATEGY ${STRATEGIES})
    add_subdirectory(${STRATEGY})
endforeach(STRATEGY)

add_subdirectory(strategy_creator)