cmake_minimum_required(VERSION 3.19)
project(Data_Stractures_Wet_2)

set(CMAKE_CXX_STANDARD 11)

#Add the google test subdirectory
add_subdirectory(googletest-main)

#include googletest/include dir
include_directories(googletest-main/googletest/include)

#include the googlemock/include dir
include_directories(googletest-main/googlemock/include)

add_executable(Data_Stractures_Wet_2
        #TreeTest.cpp
        #GameTest.cpp
        #GroupTest.cpp
        main2.cpp
        Player.cpp Player.h
        Group.cpp Group.h
        Game.cpp Game.h
        LevelData.cpp LevelData.h
        HashTable.cpp HashTable.h
        UnionFind.cpp UnionFind.h
        LevelTree.h
        library2.cpp)

target_link_libraries(Data_Stractures_Wet_2 gtest gtest_main)
target_link_libraries(Data_Stractures_Wet_2 gmock gmock_main)


