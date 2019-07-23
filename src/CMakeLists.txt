# add global dependencies
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../labRemote/src/libCom )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../labRemote/src/libPs )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../labRemote/src/libUtils )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../labRemote/src/libMeter )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../labRemote/src/libLoad )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../labRemote/src/libDevCom )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../labRemote/src/libGalil )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../labRemote/src/libZaber )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../labRemote/src/libWaferProb )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../labRemote/src/libScope )

# add executables
link_directories( ${CMAKE_BINARY_DIR}/lib )
add_library(PID PID.cpp)
add_executable(peltier_cooling peltier_cooling.cpp)
target_link_libraries(peltier_cooling -lCOM -lPS -lMETER -lLOAD -lDevCom -lPID)
add_dependencies(peltier_cooling COM PS METER LOAD DevCom PID)

add_executable(bk_test bk_test.cpp)
target_link_libraries(bk_test -lCOM -lPS -lMETER -lLOAD -lDevCom -lPID)
add_dependencies(bk_test COM PS METER LOAD DevCom PID)
