cmake_minimum_required(VERSION 3.0.0)
project(SMC4 VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(.)
add_executable(SMC4 main.cc)

link_directories(.)
target_link_libraries(SMC4 smc4dll)
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
