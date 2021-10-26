#Raul Martinez Llorente

cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (fileManager)
add_executable (fileManager main_fm.cpp filemanager.cpp filemanager.h)
target_link_libraries(fileManager pthread)

project(fileManagerClient LANGUAGES CXX)
add_executable(fileManagerClient filemanagerMainClient.cpp filemanager.h filemanager.cpp filemanager_stub.h filemanager_stub.cpp utils.h utils.cpp)
target_link_libraries(fileManagerClient pthread)

project(fileManagerServer LANGUAGES CXX)
add_executable(fileManagerServer filemanagerMainServer.cpp filemanager.h filemanager.cpp filemanager_imp.h filemanager_imp.cpp utils.h utils.cpp)
target_link_libraries(fileManagerServer pthread)
