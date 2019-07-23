cmake_minimum_required(VERSION 2.8)

project (peltier-cooling)

# The version number.
set (peltiercooling_VERSION_MAJOR 1)
set (peltiercooling_VERSION_MINOR 0)

# Nicer structure for binary files
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MACOSX_RPATH 1)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
    message(FATAL_ERROR "GCC version must be at least 4.8!")
  endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.2)
    message(FATAL_ERROR "Clang version must be at least 3.2!")
  endif()
else()
  message(WARNING "You are using an unsupported compiler! Compilation has only been tested with Clang and GCC.")
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
  add_compile_options(-g)
else()
  add_compile_options(-O2)
endif()
add_compile_options(-Wfatal-errors)
add_compile_options(-Wno-deprecated)
add_compile_options(-std=c++11)
add_compile_options(-Wall)
add_compile_options(-fPIC)
add_compile_options(-pthread)
add_compile_options(-m64)
add_compile_options(-I/usr/include/root)

set(ExternalProjectCMakeArgs
    -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}
    -DCMAKE_Fortran_COMPILER=${CMAKE_Fortran_COMPILER}
    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCBLAS_ROOT=${CBLAS_ROOT}
    -DEIGEN3_ROOT=${EIGEN3_ROOT}
    )

add_subdirectory(labRemote)
add_subdirectory(src)
