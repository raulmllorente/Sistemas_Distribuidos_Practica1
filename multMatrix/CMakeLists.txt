#Raul Martinez Llorente

cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (multMatrix)
add_executable (multMatrix main_multMatrix.cpp multmatrix.cpp multmatrix.h)
target_link_libraries(multMatrix pthread)

project(multMatrixClient LANGUAGES CXX)
add_executable(multMatrixClient multmatrixMainClient.cpp multmatrix.h multmatrix.cpp multmatrix_stub.h multmatrix_stub.cpp utils.h utils.cpp)
target_link_libraries(multMatrixClient pthread)

project(multMatrixServer LANGUAGES CXX)
add_executable(multMatrixServer multmatrixMainServer.cpp multmatrix.h multmatrix.cpp multmatrix_imp.h multmatrix_imp.cpp utils.h utils.cpp)
target_link_libraries(multMatrixServer pthread)
